"""Reposition compiler pool words using paired instructions and resident identity."""

import re
import struct
from collections.abc import Callable, Mapping

from atomic import write
from elf import Object
from rodata import pools, relocated, table_pointer_bias

ANCHOR = re.compile(r"unbake_rodata_([0-9A-F]{8})_([0-9A-F]+)$")


def storage(obj: Object, section: int) -> list[tuple[int, int, int]]:
    """Read explicit C storage anchors (address and byte extent, not ELF padding).

    ASN64-compatible assemblers do not retain object sizes, so the complete
    extent is part of the emitted identifier. An anchor is still checked against
    ROM bytes before it is allowed to supply any placement evidence.
    """
    result = []
    for symbols in obj.symbols.values():
        for symbol in symbols:
            match = ANCHOR.fullmatch(symbol["name"])
            if match is not None and symbol["section"] == section:
                address, size = (int(value, 16) for value in match.groups())
                result.append((symbol["value"], address, size))
    return result


def arrange(
    obj: Object,
    section: str,
    target_words: Mapping[int, int | None],
    text_address: int,
    read_memory: Callable[[int, int], bytes],
    read_table: Callable[[int, int], bytes] | None = None,
    *,
    emit_resident: bool = False,
    slices: list[dict[str, int]] | None = None,
    provided: list[dict[str, int]] | None = None,
    persist: bool = True,
) -> int:
    """Expand shared literal uses and preserve resident gaps, proving each emitted word.

    Only relocated loads or local jump-table addresses supply placement evidence.
    Compiler alignment zeros have no runtime identity and are omitted. Every other
    emitted byte must belong to a proved reference. The resulting object remains
    an ordinary relocatable ELF with its original symbols and relocation kinds.
    """
    original_data = bytes(obj.data) if persist else None
    index, text = obj.section(section), obj.section(".text")
    if index is None or text is None:
        raise ValueError(f"{section}: missing constant or text section")
    code = bytearray(obj.content(text))
    source = bytearray(obj.content(index))
    material = relocated(obj, section, text_address)
    tables = pools(obj, section, True)
    pending: dict[tuple[int, int], list[tuple[int, int]]] = {}
    uses: list[tuple[int, int, int, int, int, int, bool]] = []
    normalized: set[int] = set()
    anchors = storage(obj, index)
    for own, address, size in anchors:
        if size <= 0 or own + size > len(source):
            raise ValueError(f"{section}: explicit storage outside section bytes")
        if material[own : own + size] != read_memory(address, size):
            raise ValueError(f"{section}.bytes: explicit storage disagrees at 0x{address:08X}")
    for offset, kind, symbol in obj.relocations(text):
        if symbol["section"] != index:
            continue
        key = symbol["table"], symbol["index"]
        word = int(struct.unpack_from(">I", code, offset)[0])
        if kind == 5:
            pending.setdefault(key, []).append((offset, word))
            continue
        if kind != 6:
            raise ValueError(f"{section}: unsupported text relocation {kind}")
        highs = pending.pop(key, [])
        if not highs:
            raise ValueError(f"{section}: missing HI16 pair")
        for at, high in highs:
            original, target = target_words.get(at), target_words.get(offset)
            own = ((high & 0xFFFF) << 16) + signed(word) + symbol["value"]
            table = next((pool for pool in tables if pool.offset == own), None)
            string = table is None and word >> 26 in (9, 13)
            if string:
                terminator = source.find(0, own)
                if own < 0 or terminator < own:
                    raise ValueError(f"{section}: unterminated string reference")
                size = terminator + 1 - own
            else:
                size = table.size if table else 8 if word >> 26 in (0x35, 0x37) else 4
            if table is None and not string and word >> 26 not in (0x23, 0x31, 0x35, 0x37):
                raise ValueError(f"{section}: reference has no literal load or jump table")
            if own < 0 or (not string and own % 4) or own + size > len(source):
                raise ValueError(f"{section}: reference outside pool words")
            anchored = {
                address + own - start
                for start, address, extent in anchors
                if start <= own < own + size <= start + extent
            }
            if original is None or target is None:
                if len(anchored) != 1:
                    raise ValueError(f"{section}: missing aligned pool reference at 0x{offset:X}")
                address = anchored.pop()
            else:
                if (high ^ original) & 0xFFFF0000 or (word ^ target) & 0xFFFF0000:
                    raise ValueError(f"{section}: pool reference instruction differs at 0x{offset:X}")
                address = (((original & 0xFFFF) << 16) + signed(target)) & 0xFFFFFFFF
                if anchored and anchored != {address}:
                    raise ValueError(f"{section}: pool reference disagrees with explicit storage")
            expected = (read_table or read_memory)(address, size) if table else read_memory(address, size)
            actual = material[own : own + size]
            raw = read_memory(address, size)
            if actual != expected and (table is None or table_pointer_bias(actual, raw) is None):
                raise ValueError(f"{section}.bytes: disagree at 0x{address:08X}")
            if emit_resident and table is not None and actual != raw and own not in normalized:
                normalized.add(own)
                for entry in range(0, size, 4):
                    delta = int.from_bytes(raw[entry : entry + 4], "big") - int.from_bytes(
                        actual[entry : entry + 4], "big"
                    )
                    addend = int.from_bytes(source[own + entry : own + entry + 4], "big")
                    struct.pack_into(">I", source, own + entry, (addend + delta) & 0xFFFFFFFF)
            uses.append((at, offset, own, address, size, symbol["value"], symbol["info"] & 15 != 3))
    if pending or not (uses or anchors):
        raise ValueError(f"{section}: missing complete pool reference pairs")
    chunks = [(own, address, size) for _, _, own, address, size, _, _ in uses] + anchors
    covered = {i for own, _, size in chunks for i in range(own, own + size)}
    if any(value and i not in covered for i, value in enumerate(source)):
        raise ValueError(f"{section}: unreferenced non-padding pool bytes")
    base = min(address for _, address, _ in chunks)
    end = max(address + size for _, address, size in chunks)
    if not anchors:
        end = (end + 3) & ~3
    if slices:
        if provided is not None:
            slices = [
                row
                for row in slices
                if any(
                    address < row["address"] + row["end"] - row["start"] and row["address"] < address + size
                    for _, address, size in chunks
                )
            ]
        for _, address, size in chunks:
            covered_span = sum(
                max(0, min(address + size, row["address"] + row["end"] - row["start"]) - max(address, row["address"]))
                for row in slices
            )
            if covered_span != size:
                raise ValueError(f"layout.pool_owner: {section}: unassigned compiler bytes at 0x{address:08X}")
        base = min(row["address"] for row in slices)
        end = max(row["address"] + row["end"] - row["start"] for row in slices)
    if not slices and end - base > max(0x10000, len(source) * 16):
        raise ValueError(f"{section}: pool references cross unrelated resident spans")
    if slices and provided is not None:
        # Only proved compiler bytes change providers. Unemitted resident bytes
        # remain with assembly, including private constants referenced as externs.
        result = bytearray(end - base)
        for row in sorted(slices, key=lambda row: row["address"]):
            ranges = sorted(
                (max(address, row["address"]), min(address + size, row["address"] + row["end"] - row["start"]))
                for _, address, size in chunks
                if address < row["address"] + row["end"] - row["start"] and row["address"] < address + size
            )
            merged: list[tuple[int, int]] = []
            for start, stop in ranges:
                if merged and start <= merged[-1][1]:
                    merged[-1] = merged[-1][0], max(merged[-1][1], stop)
                else:
                    merged.append((start, stop))
            for start, stop in merged:
                rom = row["start"] + start - row["address"]
                provided.append(dict(address=start, start=rom, end=rom + stop - start))
    elif slices:
        result = bytearray(end - base)
        for row in slices:
            size = row["end"] - row["start"]
            content = read_memory(row["address"], size)
            if len(content) != size:
                raise ValueError(f"layout.pool_span: {section}: incomplete private slice")
            result[row["address"] - base : row["address"] - base + size] = content
        # Every nonzero resident byte needs compiler-owned material; padding may
        # be retained only after the slice's complete bytes have been proved.
        supplied = {address + i for _, address, size in chunks for i in range(size)}
        if any(value and base + i not in supplied for i, value in enumerate(result)):
            raise ValueError(f"layout.pool_span: {section}: unaccounted private slice bytes")
    else:
        result = bytearray(read_memory(base, end - base))
    if len(result) != end - base:
        raise ValueError(f"{section}: incomplete resident pool words")
    moved: dict[int, int] = {}
    for own, address, size in anchors:
        destination = address - base
        result[destination : destination + size] = source[own : own + size]
        moved.update((old, destination + old - own) for old in range(own, own + size))
    for _, _, own, address, size, _, _ in uses:
        destination = address - base
        result[destination : destination + size] = source[own : own + size]
        for old in range(own, own + size):
            new = destination + old - own
            if (
                old in moved
                and moved[old] != new
                and any(pool.offset <= old < pool.offset + pool.size for pool in tables)
            ):
                raise ValueError(f"{section}: duplicated jump table")
            moved[old] = new
    for at, low, _, address, _, value, named in uses:
        destination = address - base
        symbol_value = moved.get(value, value) if named else value
        addend = (destination - symbol_value) & 0xFFFFFFFF
        for pos, immediate in ((at, (addend + 0x8000) >> 16), (low, addend)):
            previous = int(struct.unpack_from(">I", code, pos)[0])
            struct.pack_into(">I", code, pos, previous & 0xFFFF0000 | immediate & 0xFFFF)
    # Rehome table relocation offsets; table entry addends remain local text offsets.
    for rel_index, header in enumerate(obj.sections):
        if header[1] == 9 and header[7] == index:
            data = bytearray(obj.content(rel_index))
            for pos in range(0, len(data), 8):
                old = int(struct.unpack_from(">I", data, pos)[0])
                struct.pack_into(">I", data, pos, moved[old])
            replace(obj, rel_index, data)
    # Exported C storage symbols must follow their bytes when compiler alignment
    # is removed. Section symbols retain zero: their addends were adjusted above.
    for sym_index, symbols in obj.symbols.items():
        data = bytearray(obj.content(sym_index))
        for number, symbol in enumerate(symbols):
            if symbol["section"] == index and symbol["value"] in moved and symbol["info"] & 15 != 3:
                value = moved[symbol["value"]]
                struct.pack_into(">I", data, number * 16 + 4, value)
                symbol["value"] = value
        replace(obj, sym_index, data)
    replace(obj, text, code)
    replace(obj, index, result)
    if obj.path.is_symlink():
        raise ValueError(f"{obj.path}: cannot rewrite a symlink object")
    if persist:
        material = bytes(obj.data)
        if material != original_data:
            write(obj.path, material)
    return base


def signed(word: int) -> int:
    return (word & 0x7FFF) - (word & 0x8000)


def replace(obj: Object, index: int, data: bytes | bytearray) -> None:
    """Append replacement contents without disturbing other ELF offsets."""
    if obj.content(index) == data:
        return
    obj.data.extend(bytes(-len(obj.data) % 4))
    obj.sections[index][4:6] = [len(obj.data), len(data)]
    obj.data.extend(data)
    struct.pack_into(">10I", obj.data, obj.table + index * 40, *obj.sections[index])
