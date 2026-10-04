"""Split proved compiler pools into independent ELF load sections."""

from __future__ import annotations

import struct
from bisect import bisect_left
from collections.abc import Callable
from copy import deepcopy
from dataclasses import dataclass
from itertools import pairwise
from pathlib import Path
from typing import Any

from atomic import write
from elf import Object
from link_inputs import Selectors
from literal_layout import replace, signed
from rodata import relocated


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


def split_pool(
    obj: Object, section: str, base: int, slices: list[dict[str, Any]], *, persist: bool = True
) -> list[str]:
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
    if persist:
        write(obj.path, bytes(obj.data))
    # Text relocations now reference inserted section symbols. Keep the parser's
    # symbol table in sync when another compiler section is split next.
    obj.symbols = Object(obj.path, data=bytes(obj.data)).symbols
    return [obj.names[index] for index in sections]


@dataclass(frozen=True)
class Provider:
    """A proved compiler extent, independent of the pool's assembly owners."""

    object: str
    section: str
    address: int
    text_address: int


def absolute_pool(obj: Object, index: int, address: int) -> None:
    """Keep references valid when another equal provider supplies the ROM bytes."""
    for sym_index, symbols in obj.symbols.items():
        packed = bytearray(obj.content(sym_index))
        changed = False
        for number, symbol in enumerate(symbols):
            belongs = symbol["section"] == index
            old_absolute = (
                symbol["section"] == 0xFFF1
                and symbol["info"] & 15 == 3
                and address <= symbol["value"] <= address + obj.sections[index][5]
            )
            if belongs or old_absolute:
                changed = True
                symbol["section"] = 0xFFF1
                if belongs:
                    symbol["value"] += address
                # MIPS ld ignores st_value on STT_SECTION relocations. An
                # absolute ROM reference must be an ordinary local symbol.
                if symbol["info"] & 15 == 3:
                    symbol["info"] &= 0xF0
                    packed[number * 16 + 12] = symbol["info"]
                struct.pack_into(">I", packed, number * 16 + 4, symbol["value"])
                struct.pack_into(">H", packed, number * 16 + 14, 0xFFF1)
        if changed:
            replace(obj, sym_index, packed)


def piece(obj: Object, index: int, start: int, end: int, address: int) -> str:
    """Copy one load extent and its table relocations to a fresh section."""
    name = f".unbake_piece_{address:08X}_{end - start:X}"
    existing = obj.section(name)
    if existing is not None:
        expected = obj.content(index)[start:end]
        actual = obj.content(existing)
        if actual != expected:
            raise ValueError(f"layout.pool_bytes: {name}: existing provider disagrees at 0x{address:08X}")
        original_rels = [(at - start, kind, symbol) for at, kind, symbol in obj.relocations(index) if start <= at < end]
        if obj.relocations(existing) != original_rels:
            raise ValueError(f"layout.pool_bytes: {name}: existing provider relocations disagree at 0x{address:08X}")
        return name
    target = append_section(obj, name, obj.content(index)[start:end], flags=obj.sections[index][2])
    for rel_index, header in list(enumerate(obj.sections)):
        if header[1] != 9 or header[7] != index:
            continue
        data = bytearray()
        for offset, info in struct.iter_unpack(">II", obj.content(rel_index)):
            if offset < end and offset + 4 > start:
                if offset < start or offset + 4 > end:
                    raise ValueError(f"layout.pool_bytes: relocation cut at 0x{address:08X}")
                data.extend(struct.pack(">II", offset - start, info))
        if data:
            append_section(
                obj,
                ".rel" + name,
                bytes(data),
                type_=9,
                flags=0,
                link=header[6],
                info=target,
                entsize=8,
            )
    return name


def link_pools(
    build: Path,
    script: str,
    rows: list[dict[str, Any]],
    providers: list[Provider],
    image: bytes,
    *,
    load: Callable[[Path], Object] = Object,
) -> str:
    """Select one provider per ROM byte, retaining assembly for every other byte.

    All comparisons and selector validation precede atomic output publication.
    Original assembly objects are never changed; their remainder is emitted in
    sidecar objects. Equal overlapping C extents collapse in deterministic order.
    """
    objects: dict[str, Object] = {}
    originals: dict[str, bytes] = {}
    extents: list[tuple[Provider, int, bytes]] = []
    for provider in sorted(providers, key=lambda p: (p.object, p.address, p.section)):
        if provider.object not in objects:
            objects[provider.object] = load(build / provider.object)
            originals[provider.object] = bytes(objects[provider.object].data)
        obj = objects[provider.object]
        index = obj.section(provider.section)
        if index is None:
            raise ValueError(f"layout.pool_owner: missing {provider.object}({provider.section})")
        material = relocated(obj, provider.section, provider.text_address)
        extents.append((provider, index, material))
    by_address = sorted((p.address, number) for number, (p, _, _) in enumerate(extents))
    addresses = [address for address, _ in by_address]
    inputs = Selectors(script)
    touched: set[int] = set()
    for row in sorted(rows, key=lambda r: (r["address"], r["path"])):
        base, end = row["address"], row["address"] + row["end"] - row["start"]
        candidates = sorted(
            number for _, number in by_address[bisect_left(addresses, base) : bisect_left(addresses, end)]
        )
        owners = [
            extents[number]
            for number in candidates
            if base <= extents[number][0].address < extents[number][0].address + len(extents[number][2]) <= end
        ]
        if not owners:
            continue
        raw = image[row["start"] : row["end"]]
        if len(raw) != end - base:
            raise ValueError(f"layout.pool_bytes: {row['path']}: incomplete ROM at 0x{base:08X}")
        for provider, _, data in owners:
            touched.add(id(provider))
            offset = provider.address - base
            expected = raw[offset : offset + len(data)]
            if data != expected:
                at = next(i for i, (a, b) in enumerate(zip(data, expected, strict=True)) if a != b)
                raise ValueError(
                    f"layout.pool_bytes: {provider.object}({provider.section}) disagrees with ROM "
                    f"at 0x{provider.address + at:08X} (compiler {data[at]:02X}, ROM {expected[at]:02X})"
                )
        pool_section = row.get("section", ".rodata")
        pool = "obj/asm/data/" + row["path"] + pool_section + ".o"
        if inputs.counts[pool, pool_section] != 1:
            raise ValueError(f"layout.pool_span: {row['path']}: expected one load selector")
        assembly = load(build / pool)
        asm_index = assembly.section(pool_section)
        if asm_index is None or assembly.content(asm_index) != raw:
            raise ValueError(f"layout.pool_bytes: {pool}: assembly bytes disagree at 0x{base:08X}")
        remainder = pool.removesuffix(".o") + ".unbake-pool.o"
        boundaries = sorted(
            {base, end, *(p.address for p, _, _ in owners), *(p.address + len(d) for p, _, d in owners)}
        )
        runs: list[tuple[int, int, Provider | None, int]] = []
        for start, stop in pairwise(boundaries):
            owner = next(((p, i) for p, i, d in owners if p.address <= start < stop <= p.address + len(d)), None)
            chosen, index = owner if owner else (None, asm_index)
            if runs and runs[-1][2:] == (chosen, index):
                previous = runs.pop()
                runs.append((previous[0], stop, chosen, index))
            else:
                runs.append((start, stop, chosen, index))
        selectors = []
        for start, stop, selected, index in runs:
            obj = objects[selected.object] if selected else assembly
            origin = selected.address if selected else base
            name = piece(obj, index, start - origin, stop - origin, start)
            selectors.append((selected.object if selected else remainder) + "(" + name + ")")
        inputs.substitute(pool, pool_section, "; ".join(selectors))
        if any(p is None for _, _, p, _ in runs):
            absolute_pool(assembly, asm_index, base)
            objects[remainder] = assembly
    if len(touched) != len(providers):
        raise ValueError("layout.pool_owner: compiler extent is not in one structural ROM pool")
    for provider, index, _ in extents:
        absolute_pool(objects[provider.object], index, provider.address)
    for name, obj in sorted(objects.items()):
        material = bytes(obj.data)
        path = build / name
        before = originals.get(name)
        if before is None and path.is_file():
            before = path.read_bytes()
        if material != before:
            write(path, material)
    return inputs.apply(script)
