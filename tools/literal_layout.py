"""Reposition compiler pool words using paired instructions and resident identity."""

import struct
from collections.abc import Callable, Mapping

from elf import Object
from rodata import pools, relocated


def arrange(
    obj: Object,
    section: str,
    target_words: Mapping[int, int | None],
    text_address: int,
    read_memory: Callable[[int, int], bytes],
    read_table: Callable[[int, int], bytes] | None = None,
) -> int:
    """Expand shared literal uses and preserve resident gaps, proving each emitted word.

    Only relocated loads or local jump-table addresses supply placement evidence.
    Compiler alignment zeros have no runtime identity and are omitted. Every other
    emitted byte must belong to a proved reference. The resulting object remains
    an ordinary relocatable ELF with its original symbols and relocation kinds.
    """
    index, text = obj.section(section), obj.section(".text")
    if index is None or text is None:
        raise ValueError(f"{section}: missing constant or text section")
    code = bytearray(obj.content(text))
    source = obj.content(index)
    material = relocated(obj, section, text_address)
    tables = pools(obj, section, True)
    pending: dict[tuple[str, int], list[tuple[int, int]]] = {}
    uses: list[tuple[int, int, int, int, int, int]] = []
    for offset, kind, symbol in obj.relocations(text):
        if symbol["section"] != index:
            continue
        key = symbol["name"], symbol["value"]
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
            if original is None or target is None:
                raise ValueError(f"{section}: missing aligned pool reference at 0x{offset:X}")
            if (high ^ original) & 0xFFFF0000 or (word ^ target) & 0xFFFF0000:
                raise ValueError(f"{section}: pool reference instruction differs at 0x{offset:X}")
            own = ((high & 0xFFFF) << 16) + signed(word) + symbol["value"]
            address = (((original & 0xFFFF) << 16) + signed(target)) & 0xFFFFFFFF
            table = next((pool for pool in tables if pool.offset == own), None)
            size = table.size if table else 8 if word >> 26 in (0x35, 0x37) else 4
            if table is None and word >> 26 not in (0x23, 0x31, 0x35, 0x37):
                raise ValueError(f"{section}: reference has no literal load or jump table")
            if own < 0 or own % 4 or own + size > len(source):
                raise ValueError(f"{section}: reference outside pool words")
            expected = (read_table or read_memory)(address, size) if table else read_memory(address, size)
            if expected != material[own : own + size]:
                raise ValueError(f"{section}.bytes: disagree at 0x{address:08X}")
            uses.append((at, offset, own, address, size, symbol["value"]))
    if pending or not uses:
        raise ValueError(f"{section}: missing complete pool reference pairs")
    covered = {i for _, _, own, _, size, _ in uses for i in range(own, own + size)}
    if any(value and i not in covered for i, value in enumerate(source)):
        raise ValueError(f"{section}: unreferenced non-padding pool bytes")
    base = min(address for _, _, _, address, _, _ in uses)
    end = max(address + size for _, _, _, address, size, _ in uses)
    if end - base > max(0x10000, len(source) * 16):
        raise ValueError(f"{section}: pool references cross unrelated resident spans")
    result = bytearray(read_memory(base, end - base))
    if len(result) != end - base:
        raise ValueError(f"{section}: incomplete resident pool words")
    moved: dict[int, int] = {}
    for at, low, own, address, size, value in uses:
        destination = address - base
        result[destination : destination + size] = source[own : own + size]
        for old in range(own, own + size, 4):
            new = destination + old - own
            if (
                old in moved
                and moved[old] != new
                and any(pool.offset <= old < pool.offset + pool.size for pool in tables)
            ):
                raise ValueError(f"{section}: duplicated jump table")
            moved[old] = new
        addend = (destination - value) & 0xFFFFFFFF
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
    replace(obj, text, code)
    replace(obj, index, result)
    if obj.path.is_symlink():
        raise ValueError(f"{obj.path}: cannot rewrite a symlink object")
    obj.path.write_bytes(obj.data)
    return base


def signed(word: int) -> int:
    return (word & 0x7FFF) - (word & 0x8000)


def replace(obj: Object, index: int, data: bytes | bytearray) -> None:
    """Append replacement contents without disturbing other ELF offsets."""
    obj.data.extend(bytes(-len(obj.data) % 4))
    obj.sections[index][4:6] = [len(obj.data), len(data)]
    obj.data.extend(data)
    struct.pack_into(">10I", obj.data, obj.table + index * 40, *obj.sections[index])
