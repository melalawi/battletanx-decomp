#!/usr/bin/env python3
"""Place compiler constants over the exact resident ROM bytes proved by relocations."""

import argparse
import json
import re
import struct
from pathlib import Path
from typing import Any

from elf import Object
from extract import publish
from literal_layout import arrange, signed, storage
from pool_slices import split_pool
from rodata import fragment, insert_fragment, placement, relocated


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
    target_words = {
        at: int(struct.unpack_from(">I", image, interval["start"] + at)[0])
        for at in range(0, min(len(code), interval["end"] - interval["start"]), 4)
    }

    def read_memory(address: int, size: int) -> bytes:
        matches = [
            row
            for row in mappings or []
            if row["address"] <= address and address + size <= row["address"] + row["end"] - row["start"]
        ]
        if len(matches) > 1:
            raise ValueError(f"{obj.path}: {section_name} has ambiguous resident ROM mappings at 0x{address:08X}")
        row = matches[0] if matches else interval
        offset = row["start"] + address - row["address"]
        if offset < 0 or offset + size > len(image):
            raise ValueError(f"{obj.path}: {section_name} bytes disagree with resident ROM at 0x{address:08X}")
        return image[offset : offset + size]

    def read_table(address: int, size: int) -> bytes:
        data = read_memory(address, size)
        matches = [
            row for row in mappings or [] if row["address"] <= address < row["address"] + row["end"] - row["start"]
        ]
        bias = matches[0].get("table_entry_bias", 0) if matches else interval.get("table_entry_bias", 0)
        return b"".join(struct.pack(">I", (word[0] + bias) & 0xFFFFFFFF) for word in struct.iter_unpack(">I", data))

    try:
        base, dissent = placement(obj, section_name, target_words)
        if dissent:
            raise ValueError(f"{section_name}: conflicting placements")
        if "rodata_address" in interval and base != interval["rodata_address"]:
            raise ValueError(f"{section_name}: leading compiler padding precedes the local split row")
    except ValueError:
        return arrange(
            obj,
            section_name,
            target_words,
            interval["address"],
            read_memory,
            read_table,
            emit_resident="rodata_address" in interval,
        )
    if "rodata_address" in interval:
        material = relocated(obj, section_name, interval["address"])
        if material == read_memory(base, len(material)):
            return base
        return arrange(
            obj, section_name, target_words, interval["address"], read_memory, read_table, emit_resident=True
        )
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
        try:
            base = arrange(
                obj,
                section_name,
                target_words,
                interval["address"],
                read_memory,
                read_table,
                emit_resident="rodata_address" in interval,
            )
        except ValueError as error:
            raise ValueError(f"{obj.path}: {section_name} bytes disagree with resident ROM: {error}") from error
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


def transfer_private(obj: Object, interval: dict[str, Any], image: bytes, slices: list[dict[str, Any]]) -> list[str]:
    """Prove every slice and rehome compiler literals, strings and local tables."""
    text = obj.section(".text")
    if text is None:
        raise ValueError("layout.pool_span: missing compiler text")
    target = {
        at: struct.unpack_from(">I", image, interval["start"] + at)[0]
        for at in range(0, min(len(obj.content(text)), interval["end"] - interval["start"]), 4)
    }

    def read(address: int, size: int) -> bytes:
        matches = [
            row
            for row in slices
            if row["address"] <= address < address + size <= row["address"] + row["end"] - row["start"]
        ]
        if len(matches) != 1:
            raise ValueError(f"layout.pool_owner: reference 0x{address:08X} is not in one private slice")
        row = matches[0]
        start = row["start"] + address - row["address"]
        return image[start : start + size]

    def table(address: int, size: int) -> bytes:
        raw = read(address, size)
        row = next(row for row in slices if row["address"] <= address < row["address"] + row["end"] - row["start"])
        return b"".join(
            struct.pack(">I", (word[0] + row.get("table_entry_bias", 0)) & 0xFFFFFFFF)
            for word in struct.iter_unpack(">I", raw)
        )

    sections: list[str] = []
    allocated: set[int] = set()
    for section in (".rdata", ".rodata"):
        index = obj.section(section)
        if index is None or not obj.sections[index][5]:
            continue
        # The reference proof assigns bytes, rather than compiler section order.
        # Both sections together may be present, but a slice has one provider.
        addresses = {address for _, address, _ in storage(obj, index)}
        pending: dict[tuple[int, int], list[int]] = {}
        for at, kind, symbol in obj.relocations(text):
            if symbol["section"] != index:
                continue
            key = symbol["table"], symbol["index"]
            if kind == 5:
                pending.setdefault(key, []).append(at)
            elif kind == 6:
                for high in pending.pop(key, []):
                    if high in target and at in target:
                        addresses.add((((target[high] & 65535) << 16) + signed(target[at])) & 0xFFFFFFFF)
        matching = [
            row
            for row in slices
            if any(row["address"] <= address < row["address"] + row["end"] - row["start"] for address in addresses)
        ]
        if not matching or any(row["address"] in allocated for row in matching):
            raise ValueError("layout.pool_owner: compiler sections do not have disjoint private slices")
        base = arrange(obj, section, target, interval["address"], read, table, emit_resident=True, slices=matching)
        sections.extend(split_pool(obj, section, base, matching))
        allocated.update(row["address"] for row in matching)
    if not allocated:
        existing = [f".unbake_pool_{row['address']:08X}" for row in slices]
        if not all(obj.section(name) is not None for name in existing):
            raise ValueError("layout.pool_span: compiler emitted no provider for private slices")
        for row, name in zip(slices, existing, strict=True):
            if relocated(obj, name, interval["address"]) != read(row["address"], row["end"] - row["start"]):
                raise ValueError("layout.pool_span: existing compiler slice bytes disagree with ROM")
        return existing
    if allocated != {row["address"] for row in slices}:
        raise ValueError("layout.pool_span: incomplete compiler pool transfer")
    return sorted(sections)


def transfer_selectors(script: str, objname: str, slices: list[dict[str, Any]], sections: list[str]) -> str:
    for row, section in zip(sorted(slices, key=lambda item: item["address"]), sections, strict=True):
        # Structural pool rows are ordinary independent Splat assembly providers.
        pool = "obj/asm/data/" + row["path"] + ".rodata.o"
        pattern = re.escape(pool) + r"\s*\(\.rodata\)"
        script, count = re.subn(pattern, objname + "(" + section + ")", script)
        if count != 1:
            raise ValueError(f"layout.pool_span: {row['path']}: expected one load selector, found {count}")
    return script


def place(args: argparse.Namespace) -> None:
    script = args.script.read_text()
    intervals = json.loads(args.ranges.read_text())
    image = args.baserom.read_bytes()
    mappings = []
    if args.recipe is not None:
        configured = json.loads(args.recipe.read_text()).get("resident_mappings", {})
        mappings = resident_mappings(configured.get(args.version, []))
    sections: list[str] = []
    partial = args.non_matching == "1"
    objects = sorted(set(re.findall(r"(obj/src/[^\s()]+\.o)\(", script)))
    faults: list[str] = []
    for name in objects:
        try:
            script = place_object(args, name, script, intervals, image, mappings, sections, partial)
        except (OSError, ValueError, KeyError, struct.error) as error:
            # Every failing object is named so one link attributes all culprits.
            faults.append(f"{name}: {error}")
    if faults:
        raise ValueError("\n".join(faults))
    script = insert_fragment(script, "\n".join(sections))
    publish(args.output, script.encode())
    publish(args.output.with_suffix(".flags"), b"--no-check-sections" if sections else b"")


def place_object(
    args: argparse.Namespace,
    name: str,
    script: str,
    intervals: dict[str, Any],
    image: bytes,
    mappings: list[dict[str, int]],
    sections: list[str],
    partial: bool,
) -> str:
    unit = Path(name).stem
    if unit not in intervals:
        raise ValueError(f"unit-ranges.{unit} missing")
    obj = Object(args.build / name)
    slices = [row for row in intervals[unit].get("rodata_slices", []) if row["path"].startswith("rodata/")]
    if slices and not partial:
        for row in slices:
            mapped = [m for m in mappings if m["start"] <= row["start"] < row["end"] <= m["end"]]
            if len(mapped) > 1:
                raise ValueError("layout.pool_span: ambiguous private mapping")
            row["table_entry_bias"] = mapped[0]["table_entry_bias"] if mapped else 0
        placed = transfer_private(obj, intervals[unit], image, slices)
        return transfer_selectors(script, name, slices, placed)
    local = intervals[unit].get("rodata_address")
    if not partial and local is not None:
        for section in (".rdata", ".rodata"):
            index = obj.section(section)
            if index is None or not obj.sections[index][5]:
                continue
            base = resident(obj, intervals[unit], image, section, mappings)
            if base != local:
                raise ValueError(f"local {section} placement disagrees with split row")
            if section == ".rdata":
                script = re.sub(re.escape(name) + r"\s*\(\.rodata\)", name + "(.rdata)", script)
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
    return script


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
        parser.exit(1, "".join(f"HELD(link): {line}\n" for line in str(error).splitlines()))


if __name__ == "__main__":
    main()
