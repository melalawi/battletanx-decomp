"""Content-keyed reuse: atomic file artifacts across projects, parsed inputs within a process."""

import hashlib
import json
import os
import re
import shutil
import stat
import tempfile
from collections import OrderedDict
from collections.abc import Callable, Hashable, Sequence
from pathlib import Path
from typing import Any, TypeVar

class Held(Exception):
    def __init__(self, phase, reason):
        super().__init__(f"HELD({phase}): {reason}")

T = TypeVar("T")
_parsed: dict[tuple[str, tuple[Path, ...], Hashable], tuple[tuple[bytes, ...], Any]] = {}


def parsed(
    kind: str, paths: Path | Sequence[Path], parse: Callable[[], T], *, extra: Hashable = None, share: bool = False
) -> T:
    """Parse project inputs once per process while their bytes are unchanged.

    Every call reads and digests the inputs, so an edit is always observed.
    Callers treat the returned value as read-only; it is shared.
    share opts path-independent results into reuse across byte-identical copies.
    """
    files = (Path(paths),) if isinstance(paths, (str, Path)) else tuple(Path(path) for path in paths)
    index = kind, tuple(path.absolute() for path in files), extra
    try:
        digests = tuple(hashlib.blake2b(path.read_bytes(), digest_size=20).digest() for path in files)
    except OSError:
        return parse()
    if share:
        return remembered("parsed." + kind, (digests, extra), parse, keep=16)
    cached = _parsed.get(index)
    if cached is not None and cached[0] == digests:
        return cached[1]  # type: ignore[no-any-return]
    value = parse()
    _parsed[index] = digests, value
    while len(_parsed) > 64:
        del _parsed[next(iter(_parsed))]
    return value


_remembered: dict[str, OrderedDict[Hashable, Any]] = {}


def remembered(kind: str, content: Hashable, compute: Callable[[], T], *, keep: int = 4) -> T:
    """Reuse a value derived from in-memory content; each kind keeps its latest few."""
    values = _remembered.setdefault(kind, OrderedDict())
    if content in values:
        values.move_to_end(content)
        return values[content]  # type: ignore[no-any-return]
    value = compute()
    values[content] = value
    while len(values) > keep:
        values.popitem(last=False)
    return value


def key(*parts: str | bytes | Path) -> str:
    digest = hashlib.sha256()
    for index, part in enumerate(parts):
        try:
            if isinstance(part, Path):
                with part.open("rb") as source:
                    digest.update(os.fstat(source.fileno()).st_size.to_bytes(8, "big"))
                    while block := source.read(1024 * 1024):
                        digest.update(block)
                continue
            if isinstance(part, str):
                part = part.encode("utf-8")
            if not isinstance(part, bytes):
                raise Held("cache", f"key part {index}: expected str, bytes or Path")
            digest.update(len(part).to_bytes(8, "big"))
            digest.update(part)
        except OSError as error:
            raise Held("cache", f"key part {index} {part!s}: {error}") from error
    return digest.hexdigest()


class Cache:
    def __init__(self, root: Path) -> None:
        self.root = Path(root).expanduser().absolute()

    def path(self, kind: str, content_key: str) -> Path:
        if not isinstance(kind, str) or not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9_-]*", kind):
            raise Held("cache", f"kind {kind!r}: expected a single cache kind")
        if not isinstance(content_key, str) or not re.fullmatch(r"[0-9a-f]{64}", content_key):
            raise Held("cache", f"key {content_key!r}: expected SHA-256")
        return self.root / kind / content_key[:2] / content_key

    def get(self, kind: str, key: str) -> Path | None:
        path = self.path(kind, key)
        # One observation: publication between is_file() and exists() used to
        # misclassify a newly renamed regular file as a corrupt cache entry.
        try:
            mode = path.stat().st_mode
        except FileNotFoundError:
            return None
        if stat.S_ISREG(mode):
            return path
        raise Held("cache", f"{path}: expected cached file")

    def _temporary(self, path: Path) -> Path:
        path.parent.mkdir(parents=True, exist_ok=True)
        descriptor, name = tempfile.mkstemp(prefix=".pending-", dir=path.parent)
        os.close(descriptor)
        return Path(name)

    def put(self, kind: str, key: str, src: Path) -> Path:
        path = self.path(kind, key)
        temporary = None
        try:
            if not src.is_file():
                raise Held("cache", f"src {src}: expected file")
            temporary = self._temporary(path)
            shutil.copyfile(src, temporary)
            os.replace(temporary, path)
            return path
        except OSError as error:
            raise Held("cache", f"{path} from src {src}: {error}") from error
        finally:
            if temporary is not None:
                temporary.unlink(missing_ok=True)

    def produce(self, kind: str, key: str, make: Callable[[Path], None]) -> Path:
        cached = self.get(kind, key)
        if cached is not None:
            return cached
        path = self.path(kind, key)
        temporary = None
        try:
            temporary = self._temporary(path)
            temporary.unlink()
            make(temporary)
            if not temporary.is_file():
                raise Held("cache", f"make output {temporary}: expected file")
            os.replace(temporary, path)
            return path
        except OSError as error:
            raise Held("cache", f"{path}: {error}") from error
        finally:
            if temporary is not None:
                temporary.unlink(missing_ok=True)


_serialized: dict[str, tuple[Any, bytes]] = {}


def serialized(kind: str, value: Any) -> bytes:
    """Encode a mutable JSON value only when it differs from the retained snapshot.

    Only bytes escape this cache. Decode the C encoder's bytes to retain an
    independent comparison snapshot without recursively copying Python objects.
    """
    previous = _serialized.get(kind)
    if previous is not None and previous[0] == value:
        return previous[1]
    content = json.dumps(value, sort_keys=True, separators=(",", ":")).encode()
    _serialized[kind] = json.loads(content), content
    return content
