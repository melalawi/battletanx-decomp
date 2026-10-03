"""Split proved compiler pools into independent ELF load sections."""

from __future__ import annotations

import struct
from copy import deepcopy
from itertools import pairwise
from typing import Any

from elf import Object
from literal_layout import replace, signed


def append_section(
    obj: Object,
    name: str,
    content: bytes,
    *,
    type_: int = 1,
    flags: int = 2,
    link: int = 0,
    info: int = 0,
    entsize: int = 0,
) -> int:
    names_index = struct.unpack_from(">H", obj.data, 50)[0]
    strings = obj.content(names_index)
    name_offset = len(strings)
    replace(obj, names_index, strings + name.encode() + b"\0")
    obj.data.extend(bytes(-len(obj.data) % 4))
    header = [name_offset, type_, flags, 0, len(obj.data), len(content), link, info, 1, entsize]
    obj.data.extend(content)
    index = len(obj.sections)
    obj.sections.append(header)
    obj.names.append(name)
    obj.data.extend(bytes(-len(obj.data) % 4))
    obj.table = len(obj.data)
    for row in obj.sections:
        obj.data.extend(struct.pack(">10I", *row))
    struct.pack_into(">I", obj.data, 32, obj.table)
    struct.pack_into(">H", obj.data, 48, len(obj.sections))
    return index


def split_pool(obj: Object, section: str, base: int, slices: list[dict[str, Any]]) -> list[str]:
    """Move paired text and table relocations with each exact private slice."""
    index, text = obj.section(section), obj.section(".text")
    if index is None or text is None:
        raise ValueError(f"layout.pool_span: {section}: constant or text section missing")
    source = obj.content(index)
    ordered = sorted(slices, key=lambda row: row["address"])
    if any(a["address"] + a["end"] - a["start"] > b["address"] for a, b in pairwise(ordered)):
        raise ValueError("layout.pool_span: overlapping private runtime slices")
    sections = []
    for row in ordered:
        offset, size = row["address"] - base, row["end"] - row["start"]
        if offset < 0 or offset + size > len(source):
            raise ValueError("layout.pool_span: compiler section misses private slice")
        name = f".unbake_pool_{row['address']:08X}"
        if obj.section(name) is not None:
            raise ValueError(f"layout.pool_span: duplicate ELF slice {name}")
        sections.append(append_section(obj, name, source[offset : offset + size]))

    def locate(offset: int) -> tuple[int, int]:
        for row, target in zip(ordered, sections, strict=True):
            start = row["address"] - base
            if start <= offset < start + row["end"] - row["start"]:
                return target, offset - start
        raise ValueError(f"layout.pool_owner: {section}: relocation outside private slices at 0x{offset:X}")

    # Exported storage labels move with their bytes. Original section symbols
    # stay on the now empty section; text relocations get independent symbols.
    original_symbols = deepcopy(obj.symbols)
    symbol_numbers: dict[tuple[int, int], int] = {}
    for sym_index, symbols in obj.symbols.items():
        packed = bytearray(obj.content(sym_index))
        for number, symbol in enumerate(symbols):
            if symbol["section"] == index and symbol["info"] & 15 != 3:
                target, value = locate(symbol["value"])
                symbol["section"], symbol["value"] = target, value
                struct.pack_into(">I", packed, number * 16 + 4, value)
                struct.pack_into(">H", packed, number * 16 + 14, target)
        # ELF requires all local symbols before the first nonlocal (sh_info).
        # An unnamed GLOBAL section symbol is exported as `no symbol` by ld,
        # colliding with every other published pool. Insert LOCAL section
        # symbols and shift all old relocation indices, including table and
        # external references, so anonymous entries retain their identity.
        first = obj.sections[sym_index][7]
        inserted = bytearray()
        for position, target in enumerate(sections, first):
            symbol_numbers[sym_index, target] = position
            inserted.extend(struct.pack(">IIIBBH", 0, 0, 0, 3, 0, target))
        packed[first * 16 : first * 16] = inserted
        original_symbols[sym_index][first:first] = [
            dict(table=sym_index, index=position, name="", value=0, size=0, info=3, section=target)
            for position, target in enumerate(sections, first)
        ]
        for position, symbol in enumerate(original_symbols[sym_index]):
            symbol["index"] = position
        obj.sections[sym_index][7] += len(sections)
        replace(obj, sym_index, packed)
        for rel_index, header in enumerate(obj.sections):
            if header[1] != 9 or header[6] != sym_index:
                continue
            data = bytearray(obj.content(rel_index))
            for pos in range(0, len(data), 8):
                info = struct.unpack_from(">I", data, pos + 4)[0]
                number = info >> 8
                if number >= first:
                    struct.pack_into(">I", data, pos + 4, (number + len(sections)) << 8 | info & 255)
            replace(obj, rel_index, data)

    code = bytearray(obj.content(text))
    for rel_index, header in list(enumerate(obj.sections)):
        if header[1] != 9:
            continue
        data = bytearray(obj.content(rel_index))
        if header[7] == index:
            divided: dict[int, bytearray] = {target: bytearray() for target in sections}
            for pos in range(0, len(data), 8):
                offset, info = struct.unpack_from(">II", data, pos)
                if info & 255 != 2:
                    raise ValueError(f"layout.pool_span: {section}: unsupported pool relocation")
                target, local = locate(offset)
                divided[target].extend(struct.pack(">II", local, info))
            replace(obj, rel_index, b"")
            for target, material in divided.items():
                if material:
                    append_section(
                        obj,
                        ".rel" + obj.names[target],
                        bytes(material),
                        type_=9,
                        flags=0,
                        link=header[6],
                        info=target,
                        entsize=8,
                    )
        elif header[7] == text:
            pending: dict[int, list[int]] = {}
            symbols = original_symbols[header[6]]
            for pos in range(0, len(data), 8):
                offset, info = struct.unpack_from(">II", data, pos)
                number, kind = info >> 8, info & 255
                symbol = symbols[number]
                # Pair against the original symbol values; exported labels have
                # already moved, while each reference needs its own slice.
                if symbol["section"] != index:
                    continue
                if kind == 5:
                    pending.setdefault(number, []).append(pos)
                elif kind == 6:
                    highs = pending.pop(number, [])
                    if not highs:
                        raise ValueError("layout.pool_span: missing HI16 for private slice")
                    low = struct.unpack_from(">I", code, offset)[0]
                    destinations = set()
                    for high_pos in highs:
                        at = struct.unpack_from(">I", data, high_pos)[0]
                        high = struct.unpack_from(">I", code, at)[0]
                        own = ((high & 65535) << 16) + signed(low) + symbol["value"]
                        target, local = locate(own)
                        destinations.add((target, local))
                        new_number = symbol_numbers[header[6], target]
                        struct.pack_into(">I", code, at, high & 0xFFFF0000 | ((local + 0x8000) >> 16) & 65535)
                        struct.pack_into(">I", data, high_pos + 4, new_number << 8 | 5)
                    if len(destinations) != 1:
                        raise ValueError("layout.pool_span: HI16 group crosses private slices")
                    target, local = destinations.pop()
                    struct.pack_into(">I", code, offset, low & 0xFFFF0000 | local & 65535)
                    struct.pack_into(">I", data, pos + 4, symbol_numbers[header[6], target] << 8 | 6)
                else:
                    raise ValueError("layout.pool_span: unsupported text pool relocation")
            if pending:
                raise ValueError("layout.pool_span: missing LO16 for private slice")
            replace(obj, rel_index, data)
    replace(obj, text, code)
    replace(obj, index, b"")
    temporary = obj.path.with_name(obj.path.name + ".partial")
    try:
        temporary.write_bytes(obj.data)
        temporary.replace(obj.path)
    finally:
        temporary.unlink(missing_ok=True)
    # Text relocations now reference inserted section symbols. Keep the parser's
    # symbol table in sync when another compiler section is split next.
    obj.symbols = Object(obj.path).symbols
    return [obj.names[index] for index in sections]
