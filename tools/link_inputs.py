"""Content-addressed ELF metadata and indexed linker input selectors."""

from __future__ import annotations

import hashlib
import json
import re
import sqlite3
from bisect import bisect_right
from collections import Counter
from collections.abc import Callable, Iterable
from concurrent.futures import Executor, ThreadPoolExecutor
from pathlib import Path
from typing import Any

from atomic import write
from elf import Object


def clone(obj: Object) -> Object:
    """Copy mutable ELF state without reading or parsing the object again."""
    result = Object.__new__(Object)
    result.path, result.table = obj.path, obj.table
    result.data = bytearray(obj.data)
    result.sections = [row.copy() for row in obj.sections]
    result.names = obj.names.copy()
    result.symbols = {index: [symbol.copy() for symbol in symbols] for index, symbols in obj.symbols.items()}
    return result


class Objects:
    """Cache only parsed input metadata; each caller owns its mutable object."""

    def __init__(
        self,
        path: Path,
        *,
        parse: Callable[..., Object] = Object,
        read: Callable[[Path], bytes] = Path.read_bytes,
        publish: Callable[[Path, bytes], None] = write,
        parser_identity: bytes | None = None,
    ) -> None:
        self.path, self.parse, self.read, self.publish = path, parse, read, publish
        self.identity = (
            parser_identity if parser_identity is not None else Path(__file__).with_name("elf.py").read_bytes()
        )
        self.identity = hashlib.sha256(b"elf-metadata-v1\0" + self.identity).digest()
        self.database = sqlite3.connect(":memory:")
        if path.is_file():
            try:
                self.database.deserialize(read(path))
                self.database.execute("SELECT digest, metadata FROM objects LIMIT 0")
            except (OSError, sqlite3.Error):
                self.database.close()
                self.database = sqlite3.connect(":memory:")
        self.database.execute("CREATE TABLE IF NOT EXISTS objects (digest BLOB PRIMARY KEY, metadata TEXT NOT NULL)")
        self.entries: dict[bytes, Object] = {}
        self.dirty = False
        self.pending: dict[Path, bytes | OSError] = {}

    def __enter__(self) -> Objects:
        return self

    def __exit__(self, *exc: object) -> None:
        try:
            if exc[0] is None and self.dirty:
                self.database.commit()
                self.publish(self.path, self.database.serialize())
        finally:
            self.database.close()

    def prefetch(
        self,
        paths: Iterable[Path],
        *,
        workers: int = 32,
        executor: Callable[..., Executor] = ThreadPoolExecutor,
    ) -> None:
        """Overlap small-file reads, keeping parser and database work on one thread."""

        def read(path: Path) -> tuple[Path, bytes | OSError]:
            try:
                return path, self.read(path)
            except OSError as error:
                return path, error

        queued = [path for path in dict.fromkeys(paths) if path not in self.pending]
        batches = [queued[start : start + 64] for start in range(0, len(queued), 64)]

        def read_batch(batch: list[Path]) -> list[tuple[Path, bytes | OSError]]:
            return [read(path) for path in batch]

        with executor(max_workers=workers) as pool:
            for batch in pool.map(read_batch, batches):
                self.pending.update(batch)

    def __call__(self, path: str | Path) -> Object:
        path = Path(path)
        data = self.pending.pop(path, None)
        if isinstance(data, OSError):
            raise data
        if data is None:
            data = self.read(path)
        digest = hashlib.sha256(self.identity + data).digest()
        if digest not in self.entries:
            row = self.database.execute("SELECT metadata FROM objects WHERE digest = ?", (digest,)).fetchone()
            obj = None
            if row is not None:
                try:
                    metadata: dict[str, Any] = json.loads(row[0])
                    obj = Object.__new__(Object)
                    obj.table = metadata["table"]
                    obj.sections, obj.names = metadata["sections"], metadata["names"]
                    obj.symbols = {int(index): symbols for index, symbols in metadata["symbols"].items()}
                except (ValueError, KeyError, TypeError):
                    obj = None
            if obj is None:
                obj = self.parse(path, data=data)
                metadata = dict(table=obj.table, sections=obj.sections, names=obj.names, symbols=obj.symbols)
                self.database.execute(
                    "INSERT OR REPLACE INTO objects VALUES (?, ?)",
                    (digest, json.dumps(metadata, separators=(",", ":"))),
                )
                self.dirty = True
            obj.path, obj.data = path, bytearray(data)
            self.entries[digest] = obj
        result = clone(self.entries[digest])
        result.path = path
        return result


class Selectors:
    """Scan a linker script once, then apply exact selector changes in one pass."""

    pattern = re.compile(r"(?P<object>obj/[^\s()]+)\s*\((?P<section>\.[^\s()]+)\)")

    def __init__(self, script: str) -> None:
        self.counts = Counter((match["object"], match["section"]) for match in self.pattern.finditer(script))
        self.entries = set(self.counts)
        self.changes: dict[tuple[str, str], str] = {}

    def contains(self, name: str, section: str) -> bool:
        return (name, section) in self.entries

    def replace(self, name: str, before: str, after: str) -> None:
        if (name, before) in self.entries:
            self.entries.remove((name, before))
            self.entries.add((name, after))
            self.changes[name, before] = name + "(" + after + ")"

    def substitute(self, name: str, section: str, replacement: str) -> None:
        self.changes[name, section] = replacement
        self.counts[name, section] = 0
        self.entries.discard((name, section))

    def apply(self, script: str) -> str:
        if not self.changes:
            return script
        return self.pattern.sub(lambda match: self.changes.get((match["object"], match["section"]), match[0]), script)


class Spans:
    """Index point lookups while preserving every overlapping row and its order."""

    def __init__(self, rows: list[dict[str, Any]]) -> None:
        self.rows = sorted(enumerate(rows), key=lambda entry: (entry[1]["address"], entry[0]))
        self.starts = [row["address"] for _, row in self.rows]
        self.ends = [row["address"] + row["end"] - row["start"] for _, row in self.rows]
        self.maximum: list[int] = []
        for end in self.ends:
            self.maximum.append(max(end, self.maximum[-1] if self.maximum else end))

    def containing(self, address: int) -> list[dict[str, Any]]:
        stop = bisect_right(self.starts, address)
        start = bisect_right(self.maximum, address, hi=stop)
        return [
            row
            for _, row in sorted(
                self.rows[position] for position in range(start, stop) if address < self.ends[position]
            )
        ]
