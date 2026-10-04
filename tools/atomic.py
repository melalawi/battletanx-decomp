#!/usr/bin/env python3
"""Publish build outputs without ever opening a shared destination for writing."""

from __future__ import annotations

import argparse
import subprocess
import tempfile
from collections.abc import Iterator
from contextlib import ExitStack, contextmanager
from pathlib import Path


@contextmanager
def staging(path: Path) -> Iterator[Path]:
    """Yield a nonexistent private path on the destination filesystem."""
    path.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix=".publish-", dir=path.parent) as directory:
        temporary = Path(directory) / path.name
        yield temporary
        temporary.replace(path)


def write(path: Path, content: bytes) -> None:
    with staging(path) as temporary:
        temporary.write_bytes(content)


def receipt(path: Path) -> None:
    """Advance a receipt's timestamp by replacing its inode, preserving bytes."""
    write(path, path.read_bytes() if path.exists() else b"")


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
