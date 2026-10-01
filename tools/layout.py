#!/usr/bin/env python3
"""Place compiler constants over the exact resident ROM bytes proved by relocations."""

import argparse
import json
import re
import struct
from pathlib import Path

from elf import Object
from extract import publish
from rodata import fragment, insert_fragment


def signed(value: int) -> int:
    return value - 65536 if value & 32768 else value


def resident(
    obj: Object,
    interval: dict[str, int],
    image: bytes,
    section_name: str,
    mappings: list[dict[str, int]] | None = None,
) -> int | None:
    section = obj.section(section_name)
    if section is None or not obj.sections[section][5]:
        return None
    text = obj.section(".text")
    if text is None:
        raise ValueError(f"{obj.path}: missing .text")
    code = obj.content(text)
    pending: dict[tuple[str, int], list[tuple[int, int]]] = {}
    bases: list[int] = []
    for offset, kind, symbol in obj.relocations(text):
        if symbol["section"] != section:
            continue
        if offset + 4 > interval["end"] - interval["start"]:
            raise ValueError(f"{obj.path}: {section_name} relocation outside original function")
        word = struct.unpack_from(">I", code, offset)[0]
        original = struct.unpack_from(">I", image, interval["start"] + offset)[0]
        if word & 0xFFFF0000 != original & 0xFFFF0000:
            raise ValueError(f"{obj.path}: {section_name} relocation instruction differs at text+0x{offset:X}")
        key = symbol["name"], symbol["value"]
        if kind == 5:
            pending.setdefault(key, []).append((word, original))
        elif kind == 6:
            for high, target in pending.pop(key, []):
                address = ((target & 65535) << 16) + signed(original & 65535)
                addend = ((high & 65535) << 16) + signed(word & 65535)
                bases.append(address - addend - symbol["value"])
        else:
            raise ValueError(f"{obj.path}: unsupported .rdata relocation type {kind}")
    if pending or not bases or len(set(bases)) != 1:
        raise ValueError(f"{obj.path}: {section_name} placement has missing or conflicting HI16/LO16 evidence {bases}")
    base = bases[0]
    content = bytearray(obj.content(section))
    matches = [
        row
        for row in mappings or []
        if row["address"] <= base and base + len(content) <= row["address"] + row["end"] - row["start"]
    ]
    if len(matches) > 1:
        raise ValueError(f"{obj.path}: {section_name} has ambiguous resident ROM mappings at 0x{base:08X}")
    mapping = matches[0] if matches else interval
    offset = mapping["start"] + base - mapping["address"]
    pointer_bias = mapping.get("table_entry_bias", 0)
    for at, kind, symbol in obj.relocations(section):
        if kind != 2 or symbol["section"] != text:
            raise ValueError(f"{obj.path}: {section_name} relocation {kind} needs explicit placement")
        value = (
            struct.unpack_from(">I", content, at)[0] + interval["address"] + symbol["value"] - pointer_bias
        ) & 0xFFFFFFFF
        struct.pack_into(">I", content, at, value)
    if offset < 0 or offset + len(content) > len(image) or content != image[offset : offset + len(content)]:
        raise ValueError(f"{obj.path}: {section_name} bytes disagree with resident ROM at 0x{base:08X}")
    return base


def resident_mappings(value: object) -> list[dict[str, int]]:
    """Validate explicit runtime-address to ROM spans; never infer aliases from bytes."""
    if not isinstance(value, list):
        raise ValueError("resident_mappings: expected an array")
    result = []
    for index, row in enumerate(value):
        if not isinstance(row, dict) or set(row) != {"address", "start", "end", "table_entry_bias"}:
            raise ValueError(f"resident_mappings[{index}]: requires address, start, end, table_entry_bias")
        if any(isinstance(v, bool) or not isinstance(v, int) or not 0 <= v <= 0xFFFFFFFF for v in row.values()):
            raise ValueError(f"resident_mappings[{index}]: expected unsigned 32-bit integers")
        if row["end"] <= row["start"] or row["address"] + row["end"] - row["start"] > 0x100000000:
            raise ValueError(f"resident_mappings[{index}]: invalid span")
        result.append(row)
    return result


def place(args: argparse.Namespace) -> None:
    script = args.script.read_text()
    intervals = json.loads(args.ranges.read_text())
    image = args.baserom.read_bytes()
    mappings = []
    if args.recipe is not None:
        configured = json.loads(args.recipe.read_text()).get("resident_mappings", {})
        mappings = resident_mappings(configured.get(args.version, []))
    sections = []
    partial = args.non_matching == "1"
    objects = sorted(set(re.findall(r"(obj/src/[^\s()]+\.o)\(", script)))
    for name in objects:
        unit = Path(name).stem
        if unit not in intervals:
            raise ValueError(f"{name}: unit-ranges.{unit} missing")
        obj = Object(args.build / name)
        if partial:
            for section in (".rdata", ".rodata"):
                index = obj.section(section)
                if index is not None and obj.sections[index][5]:
                    # Partial constants have no byte-identical placement evidence.
                    sections.append(f"  .partial_{unit}_{section[1:]} : {{ {name}({section}) }}")
        else:
            for section in (".rdata", ".rodata"):
                if re.search(re.escape(name) + r"\s*\(" + re.escape(section) + r"\)", script):
                    continue
                base = resident(obj, intervals[unit], image, section, mappings)
                if base is not None:
                    sections.append(fragment([{"object": name, "section": section, "address": base}]))
    script = insert_fragment(script, "\n".join(sections))
    publish(args.output, script.encode())
    publish(args.output.with_suffix(".flags"), b"--no-check-sections" if sections else b"")


def main() -> None:
    parser = argparse.ArgumentParser()
    for name in ("script", "output", "build", "ranges", "baserom"):
        parser.add_argument("--" + name, type=Path, required=True)
    parser.add_argument("--recipe", type=Path)
    parser.add_argument("--version")
    parser.add_argument("--non-matching", choices=("0", "1"), required=True)
    try:
        place(parser.parse_args())
    except (OSError, ValueError, KeyError, struct.error) as error:
        parser.exit(1, f"HELD(link): {error}\n")


if __name__ == "__main__":
    main()
