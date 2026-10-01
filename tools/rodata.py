"""Relocation evidence and linker fragments for compiler constant sections."""

import re
import struct
from collections import Counter
from collections.abc import Iterable, Mapping
from dataclasses import dataclass

from elf import Object


@dataclass(frozen=True)
class Pool:
    section: str
    offset: int
    size: int


def pools(obj: Object, section: str, tables: bool) -> list[Pool]:
    """Partition a constant section into local-text pointer runs and literal bytes."""
    index = obj.section(section)
    if index is None:
        return []
    size = len(obj.content(index))
    text = obj.section(".text")
    entries = []
    for offset, kind, symbol in obj.relocations(index):
        if kind != 2 or text is None or symbol["section"] != text:
            raise ValueError(f"{section}.relocation[{offset}]: expected R_MIPS_32 against .text")
        if offset < 0 or offset % 4 or offset + 4 > size:
            raise ValueError(f"{section}.relocation[{offset}]: outside aligned section bytes")
        entries.append(offset)
    if len(set(entries)) != len(entries):
        raise ValueError(f"{section}.relocations: duplicate offsets")
    runs: list[tuple[int, int]] = []
    for offset in sorted(entries):
        if runs and runs[-1][1] == offset:
            runs[-1] = runs[-1][0], offset + 4
        else:
            runs.append((offset, offset + 4))
    if tables:
        return [Pool(section, start, end - start) for start, end in runs]
    result, cursor = [], 0
    for start, end in [*runs, (size, size)]:
        if start > cursor:
            result.append(Pool(section, cursor, start - cursor))
        cursor = end
    return result


def _word(data: bytes | bytearray, offset: int, label: str) -> int:
    if offset < 0 or offset % 4 or offset + 4 > len(data):
        raise ValueError(f"{label}[{offset}]: outside aligned word bytes")
    return int(struct.unpack_from(">I", data, offset)[0])


def _signed(word: int) -> int:
    value = word & 0xFFFF
    return value - 0x10000 if value & 0x8000 else value


def placement(obj: Object, section: str, target_words: Mapping[int, int | None]) -> tuple[int, int]:
    """Return the unique plurality base and dissent count from aligned text words.

    target_words maps candidate byte offsets to matched target instruction words.
    An explicit None denotes an insertion with no target counterpart.
    """
    index, text = obj.section(section), obj.section(".text")
    if index is None:
        raise ValueError(f"{section}: missing section")
    if text is None:
        raise ValueError(".text: missing section")
    code = obj.content(text)
    pending: dict[tuple[str, int, int], list[tuple[int, int | None]]] = {}
    votes: Counter[int] = Counter()
    for offset, kind, symbol in obj.relocations(text):
        if symbol["section"] != index:
            continue
        if offset not in target_words:
            raise ValueError(f"target_words[{offset}]: missing aligned instruction")
        word, target = _word(code, offset, ".text"), target_words[offset]
        key = symbol["name"], symbol["value"], symbol["section"]
        if kind == 5:
            pending.setdefault(key, []).append((word, target))
        elif kind == 6:
            highs = pending.pop(key, [])
            if not highs:
                raise ValueError(f"{section}.HI16[{offset}]: missing pair for {symbol['name']}")
            for high, original in highs:
                if target is None or original is None:
                    continue
                if high & 0xFFFF0000 != original & 0xFFFF0000 or word & 0xFFFF0000 != target & 0xFFFF0000:
                    continue
                own = ((high & 0xFFFF) << 16) + _signed(word) + symbol["value"]
                address = ((original & 0xFFFF) << 16) + _signed(target)
                votes[(address - own) & 0xFFFFFFFF] += 1
        else:
            raise ValueError(f"{section}.relocation[{offset}]: unsupported type {kind}")
    if pending:
        raise ValueError(f"{section}.LO16: missing pair for {next(iter(pending))[0]}")
    ranked = votes.most_common()
    if not ranked:
        raise ValueError(f"{section}.base: no relocated text reference")
    if len(ranked) > 1 and ranked[0][1] == ranked[1][1]:
        raise ValueError(f"{section}.base: tied relocation plurality")
    return ranked[0][0], sum(votes.values()) - ranked[0][1]


def relocated(obj: Object, section: str, text_address: int) -> bytes:
    """Materialize local jump-table pointers for comparison with resident bytes."""
    index, text = obj.section(section), obj.section(".text")
    if index is None:
        raise ValueError(f"{section}: missing section")
    result = bytearray(obj.content(index))
    for offset, kind, symbol in obj.relocations(index):
        if kind != 2 or text is None or symbol["section"] != text:
            raise ValueError(f"{section}.relocation[{offset}]: expected local text pointer")
        value = _word(result, offset, section) + text_address + symbol["value"]
        struct.pack_into(">I", result, offset, value & 0xFFFFFFFF)
    return bytes(result)


def fragment(rows: Iterable[Mapping[str, object]]) -> str:
    """Render proved shared-pool overlays from explicit split-row facts.

    Each row supplies object, section and address. Migrated local pools use the
    ordinary Splat selector; these overlays retain the resident ROM-producing row.
    """
    result = []
    for row in rows:
        for key in ("object", "section", "address"):
            if key not in row:
                raise ValueError(f"rodata.{key}: missing value")
        name, section, address = row["object"], row["section"], row["address"]
        if not isinstance(name, str) or not re.fullmatch(r"[\w./-]+\.o", name) or ".." in name.split("/"):
            raise ValueError("rodata.object: expected object path")
        if section not in (".rdata", ".rodata"):
            raise ValueError("rodata.section: expected .rdata or .rodata")
        if isinstance(address, bool) or not isinstance(address, int) or not 0 <= address <= 0xFFFFFFFF:
            raise ValueError("rodata.address: expected 32-bit address")
        result.append(f"  .resident_{address:08X} 0x{address:08X} (NOLOAD) : SUBALIGN(1) {{ {name}({section}) }}")
    return "\n".join(result)


def insert_fragment(script: str, sections: str) -> str:
    """Insert compiler selectors before the discard rule in a Splat script."""
    if not sections:
        return script
    marker = re.search(r"^\s*/DISCARD/\s*:", script, re.M)
    if marker is None:
        raise ValueError("linker script: /DISCARD/ missing")
    return script[: marker.start()] + sections + "\n" + script[marker.start() :]
