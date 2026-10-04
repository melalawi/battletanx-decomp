#!/usr/bin/env python3
"""Place compiler constants over the exact resident ROM bytes proved by relocations."""

import argparse
import json
import re
import struct
from collections.abc import Callable
from pathlib import Path
from typing import Any

from atomic import write
from elf import Object
from extract import publish
from link_inputs import Objects, Selectors, Spans, clone
from literal_layout import arrange, signed, storage
from pool_slices import Provider, link_pools, split_pool
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


def transfer_private(
    obj: Object, interval: dict[str, Any], image: bytes, slices: list[dict[str, Any]], *, lookup: Spans | None = None
) -> list[str]:
    """Rehome only compiler-provided bytes; retain other owners in assembly."""
    lookup = lookup if lookup is not None else Spans(slices)
    original = obj
    if any(obj.sections[index][5] for index in (obj.section(".rdata"), obj.section(".rodata")) if index is not None):
        obj = clone(obj)
    text = obj.section(".text")
    if text is None:
        raise ValueError("layout.pool_span: missing compiler text")
    target = {
        at: struct.unpack_from(">I", image, interval["start"] + at)[0]
        for at in range(0, min(len(obj.content(text)), interval["end"] - interval["start"]), 4)
    }

    def read(address: int, size: int) -> bytes:
        material = bytearray()
        cursor = address
        while cursor < address + size:
            matches = lookup.containing(cursor)
            if len(matches) != 1:
                raise ValueError(f"layout.pool_owner: reference 0x{cursor:08X} is not in one ROM slice")
            row = matches[0]
            take = min(address + size - cursor, row["address"] + row["end"] - row["start"] - cursor)
            start = row["start"] + cursor - row["address"]
            part = image[start : start + take]
            if len(part) != take:
                raise ValueError(f"layout.pool_bytes: incomplete ROM at 0x{cursor:08X}")
            material.extend(part)
            cursor += take
        return bytes(material)

    def table(address: int, size: int) -> bytes:
        raw = read(address, size)
        row = lookup.containing(address)[0]
        return b"".join(
            struct.pack(">I", (word[0] + row.get("table_entry_bias", 0)) & 0xFFFFFFFF)
            for word in struct.iter_unpack(">I", raw)
        )

    sections: list[str] = []
    for section in (".rdata", ".rodata"):
        index = obj.section(section)
        if index is None or not obj.sections[index][5]:
            continue
        # The reference proof assigns bytes, rather than compiler section order.
        # Both compiler sections may provide disjoint extents of a ROM slice.
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
        matching = any(lookup.containing(address) for address in addresses)
        provided: list[dict[str, int]] = []
        if not matching:
            raise ValueError(f"layout.pool_owner: {section}: no mapped compiler constants")
        base = arrange(
            obj,
            section,
            target,
            interval["address"],
            read,
            table,
            emit_resident=True,
            slices=slices,
            provided=provided,
            persist=False,
        )
        sections.extend(split_pool(obj, section, base, provided, persist=False))
    if not sections:
        sections = [name for name in obj.names if re.fullmatch(r"\.unbake_pool_[0-9A-F]{8}", name)]
    for name in sections:
        address = int(name.rsplit("_", 1)[1], 16)
        index = obj.section(name)
        assert index is not None
        material = relocated(obj, name, interval["address"])
        if material != read(address, len(material)):
            raise ValueError(f"layout.pool_bytes: {name}: compiler bytes disagree at 0x{address:08X}")
    if obj.data != original.data:
        write(obj.path, bytes(obj.data))
        original.__dict__.update(obj.__dict__)
    return sorted(sections)


def transfer_selectors(script: str, objname: str, slices: list[dict[str, Any]], sections: list[str]) -> str:
    for section in sections:
        address = int(section.rsplit("_", 1)[1], 16)
        row = next(row for row in slices if row["address"] == address)
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
    providers: list[Provider] = []
    pool_path = args.ranges.with_name("pool-providers.json")
    pools = json.loads(pool_path.read_text()) if pool_path.is_file() else []
    pools = [row for row in pools if row["path"].startswith("rodata/")]
    for row in pools:
        mapped = [m for m in mappings if m["start"] <= row["start"] < row["end"] <= m["end"]]
        if len(mapped) > 1:
            raise ValueError("layout.pool_span: ambiguous pool mapping")
        row["table_entry_bias"] = mapped[0]["table_entry_bias"] if mapped else 0
    inventory = resident_slices(pools, mappings) if pools else None
    faults: list[str] = []
    selectors = Selectors(script)
    lookup = Spans(inventory) if inventory is not None else None
    with Objects(args.build / ".elf-metadata.sqlite") as load:
        load.prefetch(args.build / name for name in sorted({name for name, _ in selectors.entries}))
        for name in objects:
            try:
                script = place_object(
                    args,
                    name,
                    script,
                    intervals,
                    image,
                    mappings,
                    sections,
                    partial,
                    pools=pools,
                    providers=providers,
                    load=load,
                    selectors=selectors,
                    inventory=inventory,
                    lookup=lookup,
                )
            except (OSError, ValueError, KeyError, struct.error) as error:
                # Every failing object is named so one link attributes all culprits.
                faults.append(f"{name}: {error}")
        if faults:
            raise ValueError("\n".join(faults))
        script = selectors.apply(script)
        if providers:
            pool_objects = [
                args.build / ("obj/asm/data/" + row["path"] + row.get("section", ".rodata") + ".o") for row in pools
            ]
            load.prefetch([*(args.build / provider.object for provider in providers), *pool_objects])
            script = link_pools(args.build, script, pools, providers, image, load=load)
    script = insert_fragment(script, "\n".join(sections))
    publish(args.output, script.encode())
    publish(args.output.with_suffix(".flags"), b"--no-check-sections" if sections else b"")


def resident_slices(slices: list[dict[str, Any]], mappings: list[dict[str, int]]) -> list[dict[str, Any]]:
    """Keep resident gaps distinct from structural assembly pool ownership."""
    result = list(slices)
    occupied = sorted((row["address"], row["address"] + row["end"] - row["start"]) for row in slices)
    for mapping in mappings:
        start = mapping["address"]
        end = start + mapping["end"] - mapping["start"]
        cursor = start
        gaps = []
        for left, right in occupied:
            if right <= cursor or left >= end:
                continue
            if cursor < left:
                gaps.append((cursor, left))
            cursor = max(cursor, min(right, end))
        if cursor < end:
            gaps.append((cursor, end))
        for left, right in gaps:
            offset = mapping["start"] + left - start
            result.append(
                dict(
                    address=left,
                    start=offset,
                    end=offset + right - left,
                    table_entry_bias=mapping["table_entry_bias"],
                    resident=True,
                )
            )
    return result


def place_object(
    args: argparse.Namespace,
    name: str,
    script: str,
    intervals: dict[str, Any],
    image: bytes,
    mappings: list[dict[str, int]],
    sections: list[str],
    partial: bool,
    *,
    pools: list[dict[str, Any]] | None = None,
    providers: list[Provider] | None = None,
    inventory: list[dict[str, Any]] | None = None,
    load: Callable[[Path], Object] = Object,
    selectors: Selectors | None = None,
    lookup: Spans | None = None,
) -> str:
    unit = Path(name).stem
    if unit not in intervals:
        raise ValueError(f"unit-ranges.{unit} missing")
    obj = load(args.build / name)
    if not any(
        obj.sections[index][5] for section in (".rdata", ".rodata") if (index := obj.section(section)) is not None
    ) and not any(re.fullmatch(r"\.unbake_pool_[0-9A-F]{8}", section) for section in obj.names):
        return script
    slices = [row for row in intervals[unit].get("rodata_slices", []) if row["path"].startswith("rodata/")]
    if (slices or pools) and not partial:
        if inventory is not None:
            slices = inventory
        else:
            slices = pools or slices
            for row in slices:
                mapped = [m for m in mappings if m["start"] <= row["start"] < row["end"] <= m["end"]]
                if len(mapped) > 1:
                    raise ValueError("layout.pool_span: ambiguous private mapping")
                row["table_entry_bias"] = mapped[0]["table_entry_bias"] if mapped else 0
            slices = resident_slices(slices, mappings)
        placed = transfer_private(obj, intervals[unit], image, slices, lookup=lookup)
        if providers is None and not mappings:
            return transfer_selectors(script, name, slices, placed)
        for section in placed:
            address = int(section.rsplit("_", 1)[1], 16)
            row = next(row for row in slices if row["address"] <= address < row["address"] + row["end"] - row["start"])
            if row.get("resident"):
                sections.append(fragment([dict(object=name, section=section, address=address)]))
            elif providers is not None:
                providers.append(Provider(name, section, address, intervals[unit]["address"]))
            else:
                script = transfer_selectors(script, name, slices, [section])
        return script
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
                if selectors is None:
                    script = re.sub(re.escape(name) + r"\s*\(\.rodata\)", name + "(.rdata)", script)
                else:
                    selectors.replace(name, ".rodata", ".rdata")
    if partial:
        for section in (".rdata", ".rodata"):
            index = obj.section(section)
            if index is not None and obj.sections[index][5]:
                # Partial constants have no byte-identical placement evidence.
                sections.append(f"  .partial_{unit}_{section[1:]} : {{ {name}({section}) }}")
    else:
        for section in (".rdata", ".rodata"):
            selected = (
                selectors.contains(name, section)
                if selectors is not None
                else re.search(re.escape(name) + r"\s*\(" + re.escape(section) + r"\)", script) is not None
            )
            if selected:
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
