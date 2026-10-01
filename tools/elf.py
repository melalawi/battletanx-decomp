"""Read and trim the explicit section and relocation tables of MIPS ELF32 objects."""

import struct
from pathlib import Path
from typing import TypedDict


class Symbol(TypedDict):
    name: str
    value: int
    size: int
    info: int
    section: int


class Object:
    def __init__(self, path: str | Path) -> None:
        self.path = Path(path)
        self.data = bytearray(self.path.read_bytes())
        if self.data[:7] != b"\x7fELF\x01\x02\x01":
            raise ValueError(f"{path}: expected big-endian ELF32")
        header = struct.unpack_from(">HHIIIIIHHHHHH", self.data, 16)
        self.table, entry_size, count, names_index = header[5], header[10], header[11], header[12]
        if entry_size != 40:
            raise ValueError(f"{path}: ELF section header size {entry_size}")
        self.sections = [list(struct.unpack_from(">IIIIIIIIII", self.data, self.table + i * 40)) for i in range(count)]
        names = self.content(names_index)
        self.names = [self.string(names, section[0]) for section in self.sections]
        self.symbols: dict[int, list[Symbol]] = {}
        for index, section in enumerate(self.sections):
            if section[1] == 2:
                strings = self.content(section[6])
                self.symbols[index] = [
                    {"name": self.string(strings, name), "value": value, "size": size, "info": info, "section": shndx}
                    for name, value, size, info, other, shndx in struct.iter_unpack(">IIIBBH", self.content(index))
                ]

    @staticmethod
    def string(data: bytes, start: int) -> str:
        return data[start : data.index(0, start)].decode()

    def content(self, index: int) -> bytes:
        section = self.sections[index]
        return bytes(self.data[section[4] : section[4] + section[5]]) if section[1] != 8 else bytes(section[5])

    def section(self, name: str) -> int | None:
        return self.names.index(name) if name in self.names else None

    def relocations(self, target: int) -> list[tuple[int, int, Symbol]]:
        result = []
        for index, section in enumerate(self.sections):
            if section[1] == 9 and section[7] == target:
                symbols = self.symbols[section[6]]
                for offset, info in struct.iter_unpack(">II", self.content(index)):
                    result.append((offset, info & 255, symbols[info >> 8]))
        return result

    def trim_text(self) -> None:
        index = self.section(".text")
        if index is None:
            raise ValueError(f"{self.path}: missing .text")
        ends = [
            symbol["value"] + symbol["size"]
            for symbols in self.symbols.values()
            for symbol in symbols
            if symbol["section"] == index and symbol["info"] & 15 == 2 and symbol["size"]
        ]
        if not ends:
            return
        end = max(ends)
        content = self.content(index)
        if end > len(content):
            raise ValueError(f"{self.path}: function size exceeds .text")
        if any(content[end:]):
            return
        self.sections[index][5] = end
        struct.pack_into(">IIIIIIIIII", self.data, self.table + index * 40, *self.sections[index])
        self.path.write_bytes(self.data)
