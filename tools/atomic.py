#!/usr/bin/env python3
"""Publish build outputs without ever opening a shared destination for writing."""

from __future__ import annotations

import argparse
import fcntl
import os
import shutil
import subprocess
import tempfile
from collections.abc import Iterator
from contextlib import ExitStack, contextmanager
from pathlib import Path
from typing import IO, Any


@contextmanager
def staging(path: Path, *, durable: bool = True) -> Iterator[Path]:
    """Yield a nonexistent private path on the destination filesystem."""
    path.parent.mkdir(parents=True, exist_ok=True)
    descriptor, name = tempfile.mkstemp(prefix=".publish-", suffix=path.suffix, dir=path.parent)
    os.close(descriptor)
    temporary = Path(name)
    temporary.unlink()
    try:
        yield temporary
        publish(temporary, path, durable=durable)
    finally:
        temporary.unlink(missing_ok=True)


def publish(temporary: Path, path: Path, *, durable: bool = True) -> None:
    """Sync a private file, then replace the destination directory entry."""
    if durable:
        with temporary.open("rb") as source:
            os.fsync(source.fileno())
    os.replace(temporary, path)


@contextmanager
def stream(
    path: Path,
    mode: str = "w",
    *,
    encoding: str | None = None,
    errors: str | None = None,
    newline: str | None = None,
    permissions: int | None = None,
) -> Iterator[IO[Any]]:
    """Write privately; append under a stable side lock and publish on success."""
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    with ExitStack() as stack:
        if "a" in mode or "+" in mode:
            lock = stack.enter_context(path.with_name("." + path.name + ".append.lock").open("a+b"))
            fcntl.flock(lock, fcntl.LOCK_EX)
        if permissions is None:
            permissions = path.stat().st_mode & 0o777 if path.exists() else 0o644
        with staging(path) as temporary:
            if ("a" in mode or "+" in mode) and path.exists():
                shutil.copyfile(path, temporary)
            with temporary.open(mode, encoding=encoding, errors=errors, newline=newline) as output:
                yield output
                output.flush()
                os.fsync(output.fileno())
            temporary.chmod(permissions)


def write(path: Path, content: bytes | bytearray, *, mode: int | None = None) -> None:
    with stream(path, "wb", permissions=mode) as output:
        output.write(content)


def text(
    path: Path, content: str, encoding: str | None = None, errors: str | None = None, newline: str | None = None
) -> int:
    with stream(path, encoding=encoding, errors=errors, newline=newline) as output:
        return int(output.write(content))


def copyfile(source: Path, destination: Path, *, follow_symlinks: bool = True) -> Path:
    with staging(destination) as temporary:
        shutil.copyfile(source, temporary, follow_symlinks=follow_symlinks)
    return destination


def copy2(source: Path, destination: Path, *, follow_symlinks: bool = True, durable: bool = True) -> Path:
    destination = Path(destination)
    if destination.is_dir():
        destination /= Path(source).name
    with staging(destination, durable=durable) as temporary:
        shutil.copy2(source, temporary, follow_symlinks=follow_symlinks)
    return destination


def copy(source: Path, destination: Path, *, follow_symlinks: bool = True) -> Path:
    destination = Path(destination)
    if destination.is_dir():
        destination /= Path(source).name
    with staging(destination) as temporary:
        shutil.copy(source, temporary, follow_symlinks=follow_symlinks)
    return destination


def copytree(source: Path, destination: Path, **kwargs: Any) -> Path:
    kwargs.setdefault("copy_function", copy2)
    if kwargs["copy_function"] not in (copy2, os.link):
        raise ValueError("tree copies require atomic publication or hardlinks")
    return Path(shutil.copytree(source, destination, **kwargs))


def receipt(path: Path) -> None:
    """Advance a receipt's timestamp by replacing its inode, preserving bytes."""
    # Proved outputs are durable already; this replacement advances only a timestamp.
    with staging(path, durable=False) as temporary:
        if path.exists():
            shutil.copyfile(path, temporary)
            temporary.chmod(path.stat().st_mode & 0o777)
        else:
            temporary.touch()


def command(outputs: list[Path], argv: list[str]) -> None:
    """Redirect exact output arguments to fresh files; publish only on success."""
    if not outputs or len(set(outputs)) != len(outputs):
        raise ValueError("expected distinct output paths")
    if any(argv.count(str(path)) != 1 for path in outputs):
        raise ValueError("each output must appear exactly once in the command")
    with ExitStack() as stack:
        names = {str(path): str(stack.enter_context(staging(path))) for path in outputs}
        subprocess.run([names.get(word, word) for word in argv], check=True)
        if any(not Path(name).is_file() for name in names.values()):
            raise ValueError("command did not produce every declared output")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--touch", type=Path)
    parser.add_argument("--output", type=Path, action="append", default=[])
    parser.add_argument("argv", nargs=argparse.REMAINDER)
    args = parser.parse_args()
    try:
        if args.touch is not None:
            if args.output or args.argv:
                raise ValueError("--touch cannot be combined with a command")
            receipt(args.touch)
        else:
            command(args.output, args.argv[1:] if args.argv[:1] == ["--"] else args.argv)
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        parser.exit(1, f"HELD(publish): {error}\n")


if __name__ == "__main__":
    main()
