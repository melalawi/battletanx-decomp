"""Atomic file artifacts shared by content key across projects."""

from collections.abc import Callable
import hashlib
import os
from pathlib import Path
import re
import shutil
import tempfile

class Held(Exception):
    def __init__(self, phase, reason):
        super().__init__(f"HELD({phase}): {reason}")


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
            raise Held("cache", f"key part {index} {part}: {error}") from error
    return digest.hexdigest()


class Cache:
    def __init__(self, root: Path):
        self.root = Path(root).expanduser().absolute()

    def _path(self, kind: str, content_key: str) -> Path:
        if not isinstance(kind, str) or not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9_-]*", kind):
            raise Held("cache", f"kind {kind!r}: expected a single cache kind")
        if not isinstance(content_key, str) or not re.fullmatch(r"[0-9a-f]{64}", content_key):
            raise Held("cache", f"key {content_key!r}: expected SHA-256")
        return self.root / kind / content_key[:2] / content_key

    def get(self, kind: str, key: str) -> Path | None:
        path = self._path(kind, key)
        if path.is_file():
            return path
        if path.exists():
            raise Held("cache", f"{path}: expected cached file")
        return None

    def _temporary(self, path: Path) -> Path:
        path.parent.mkdir(parents=True, exist_ok=True)
        descriptor, name = tempfile.mkstemp(prefix=".pending-", dir=path.parent)
        os.close(descriptor)
        return Path(name)

    def put(self, kind: str, key: str, src: Path) -> Path:
        path = self._path(kind, key)
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
        path = self._path(kind, key)
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
