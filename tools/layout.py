#!/usr/bin/env python3
"""Place compiler constants over the exact resident ROM bytes proved by relocations."""
import argparse
import json
from pathlib import Path
import re
import struct

from elf import Object
from extract import publish
from rodata import fragment, insert_fragment


def signed(value):
    return value - 65536 if value & 32768 else value


def resident(obj, interval, image, section_name):
    section = obj.section(section_name)
    if section is None or not obj.sections[section][5]:
        return None
    text = obj.section(".text")
    code = obj.content(text)
    pending, bases = {}, []
    for offset, kind, symbol in obj.relocations(text):
        if symbol["section"] != section:
            continue
        if offset + 4 > interval["end"] - interval["start"]:
            raise ValueError(f"{obj.path}: {section_name} relocation outside original function")
        word = struct.unpack_from(">I", code, offset)[0]
        original = struct.unpack_from(">I", image, interval["start"] + offset)[0]
        if word & 0xffff0000 != original & 0xffff0000:
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
    offset = interval["start"] + base - interval["address"]
    content = bytearray(obj.content(section))
    for at, kind, symbol in obj.relocations(section):
        if kind != 2 or symbol["section"] != text:
            raise ValueError(f"{obj.path}: {section_name} relocation {kind} needs explicit placement")
        value = struct.unpack_from(">I", content, at)[0] + interval["address"] + symbol["value"]
        struct.pack_into(">I", content, at, value)
    if offset < 0 or offset + len(content) > len(image) or content != image[offset:offset + len(content)]:
        raise ValueError(f"{obj.path}: {section_name} bytes disagree with resident ROM at 0x{base:08X}")
    return base


def place(args):
    script = args.script.read_text()
    intervals = json.loads(args.ranges.read_text())
    image = args.baserom.read_bytes()
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
                base = resident(obj, intervals[unit], image, section)
                if base is not None:
                    sections.append(fragment([{"object": name, "section": section, "address": base}]))
    script = insert_fragment(script, "\n".join(sections))
    publish(args.output, script.encode())
    publish(args.output.with_suffix(".flags"), b"--no-check-sections" if sections else b"")


def main():
    parser = argparse.ArgumentParser()
    for name in ("script", "output", "build", "ranges", "baserom"):
        parser.add_argument("--" + name, type=Path, required=True)
    parser.add_argument("--non-matching", choices=("0", "1"), required=True)
    try:
        place(parser.parse_args())
    except (OSError, ValueError, KeyError, struct.error) as error:
        parser.exit(1, f"HELD(link): {error}\n")


if __name__ == "__main__":
    main()
