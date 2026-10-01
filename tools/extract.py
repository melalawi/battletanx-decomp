#!/usr/bin/env python3
"""Extract a version and describe the exact files in splat's linker script."""

from __future__ import annotations

import argparse
import ast
import csv
import hashlib
import json
import re
import subprocess
import sys
import tempfile
from pathlib import Path

from rodata import defer_bss


def prepare_build(build: Path) -> None:
    """Publish a standalone build through the numbered generation directory."""
    build.parent.mkdir(parents=True, exist_ok=True)
    if build.is_symlink():
        if not build.is_dir():
            raise ValueError(f"{build}: build generation symlink is invalid")
        return
    if build.exists() and not build.is_dir():
        raise ValueError(f"{build}: build must be a directory")
    number = 0
    generation = build.with_name(f"{build.name}.{number}")
    while generation.exists() or generation.is_symlink():
        number += 1
        generation = build.with_name(f"{build.name}.{number}")
    if build.exists():
        build.rename(generation)
    else:
        generation.mkdir()
    build.symlink_to(generation.name, target_is_directory=True)


def automatic_symbols(text: str, committed: dict[str, int]) -> str:
    """Remove automatic definitions whose names are already committed."""
    pattern = re.compile(r"([A-Za-z_.$][\w.$]*)\s*=\s*0[xX][0-9A-Fa-f]+\s*;")
    return pattern.sub(lambda match: "" if match[1] in committed else match[0], text)


def publish(path: Path, content: bytes) -> None:
    """Keep timestamps when extraction produced the same bytes."""
    path.parent.mkdir(parents=True, exist_ok=True)
    if not path.exists() or path.read_bytes() != content:
        partial = path.with_name(path.name + ".partial")
        partial.write_bytes(content)
        partial.replace(path)


def scalar(text: str) -> str:
    text = text.split(" #", 1)[0].strip()
    return str(ast.literal_eval(text)) if text[:1] in {"'", '"'} else text


def alignment_rows(text: str) -> tuple[str, dict[str, int]]:
    """Separate explicit text alignment metadata from Splat's three-field rows."""
    alignments = {}
    pattern = re.compile(
        r"^(\s*-\s*\[\s*(?:0x[\da-fA-F]+|\d+)\s*,\s*(asm|c)\s*,\s*([^,\]\n]+))"
        r",\s*\{\s*align:\s*(0x[\da-fA-F]+|\d+)\s*\}(\s*\]\s*)$",
        re.M,
    )

    def remove(match: re.Match[str]) -> str:
        name = scalar(match[3])
        value = int(match[4], 0)
        if not value or value & (value - 1):
            raise ValueError(f"{name} align: required positive power of two")
        if name in alignments:
            raise ValueError(f"{name} align: duplicate text row")
        alignments[name] = value
        return match[1] + match[5]

    stripped = pattern.sub(remove, text)
    if re.search(r"\{\s*align:", stripped):
        raise ValueError("align: required text row with explicit positive integer")
    return stripped, alignments


def render_alignment(script: str, alignments: dict[str, int]) -> str:
    """Pad each annotated text object's tail with a linker ALIGN expression."""
    for name, value in alignments.items():
        path = re.escape(name)
        pattern = re.compile(r"(obj/(?:src|asm)/" + path + r"\.o\s*\(\.text(?:\s+\.text\.\*)?\))")
        suffix = f"\n    . = ALIGN({value});"

        def append_alignment(match: re.Match[str], suffix: str = suffix) -> str:
            return match[1] + suffix

        script, count = pattern.subn(append_alignment, script)
        if count != 1:
            raise ValueError(f"{name} align: expected one linker text selector, found {count}")
    return script


def unit_addresses(text: str) -> dict[str, int]:
    """Read explicit code interval placements, never addresses embedded in names."""
    found: dict[str, int] = {}
    start = vram = None
    in_code = False
    for line in text.splitlines():
        if re.match(r"^  - ", line):
            start = vram = None
            in_code = False
        match = re.match(r"^    (type|start|vram):\s*(\S+)", line)
        if match:
            field, value = match.groups()
            if field == "type":
                in_code = value == "code"
            elif field == "start":
                start = int(value, 0)
            else:
                vram = int(value, 0)
        row = re.match(r"^      - \[\s*(0x[0-9A-Fa-f]+|\d+)\s*,\s*(asm|c)\s*,\s*([^\],]+)", line)
        if row:
            if not in_code or start is None or vram is None:
                raise ValueError("split code segment requires type, start, vram before subsegments")
            rom, _, name = row.groups()
            name = Path(scalar(name)).name
            if not re.fullmatch(r"[A-Za-z_.$][\w.$]*", name):
                raise ValueError(f"invalid split unit symbol {name}")
            address = vram + int(rom, 0) - start
            if name in found and found[name] != address:
                raise ValueError(f"conflicting split unit symbol {name}")
            found[name] = address
    return found


def unit_ranges(text: str) -> dict[str, dict[str, int]]:
    blocks = re.split(r"(?=^  - )", text, flags=re.M)
    found: dict[str, dict[str, int]] = {}
    for block_index, block in enumerate(blocks):
        if not re.search(r"^    type: code$", block, re.M):
            continue
        start = re.search(r"^    start: (\S+)", block, re.M)
        vram = re.search(r"^    vram: (\S+)", block, re.M)
        if not start or not vram:
            raise ValueError("code segment requires start and vram")
        rows = re.findall(r"^      - \[\s*(0x[\da-fA-F]+|\d+)\s*,\s*([^,\]]+)\s*,\s*([^,\]]+)", block, re.M)
        for index, (offset, kind, name) in enumerate(rows):
            if kind.strip() != "c":
                continue
            if index + 1 < len(rows):
                end = int(rows[index + 1][0], 0)
            else:
                next_block = blocks[block_index + 1] if block_index + 1 < len(blocks) else ""
                boundary = re.search(r"^  - \[\s*(0x[\da-fA-F]+|\d+)|^    start: (\S+)", next_block, re.M)
                if boundary is None:
                    raise ValueError(f"{name}: C row end missing")
                end = int(boundary[1] or boundary[2], 0)
            rom_offset = int(offset, 0)
            found[Path(scalar(name)).name] = {
                "start": rom_offset,
                "end": end,
                "address": int(vram[1], 0) + rom_offset - int(start[1], 0),
            }
    for block in blocks:
        start = re.search(r"^    start: (\S+)", block, re.M)
        vram = re.search(r"^    vram: (\S+)", block, re.M)
        if not start or not vram:
            continue
        for offset, name in re.findall(
            r"^      - \[\s*(0x[\da-fA-F]+|\d+)\s*,\s*\.rodata\s*,\s*([^,\]]+)", block, re.M
        ):
            unit = Path(scalar(name)).name
            if unit in found:
                found[unit]["rodata_address"] = int(vram[1], 0) + int(offset, 0) - int(start[1], 0)
    return found


def symbols_from(paths: list[Path]) -> dict[str, int]:
    found: dict[str, int] = {}
    for path in paths:
        for name, value in re.findall(r"([A-Za-z_.$][\w.$]*)\s*=\s*(0[xX][0-9A-Fa-f]+)\s*;", path.read_text()):
            address = int(value, 16)
            if name in found and found[name] != address:
                raise ValueError(f"conflicting symbol {name} in {path}")
            found[name] = address
    return found


def discovered_symbols(path: Path, committed: dict[str, int]) -> dict[str, int]:
    """Retain Splat's explicit addresses even for labels omitted by compiled C."""
    found = dict(committed)
    with path.open(newline="") as stream:
        for row in csv.DictReader(stream):
            name = row["name"]
            if not re.fullmatch(r"[A-Za-z_.$][\w.$]*", name):
                raise ValueError(f"invalid discovered symbol {name}")
            address = int(row["vram_start"], 16)
            if name in found and found[name] != address:
                raise ValueError(f"conflicting discovered symbol {name}")
            found[name] = address
    return found


def external_labels(directory: Path) -> str:
    labels = set()
    for path in directory.rglob("*.s"):
        text = path.read_text()
        defined = set(re.findall(r"^\s*(\.L[0-9A-Fa-f]{8}):", text, re.M))
        referenced = set(re.findall(r"\.L[0-9A-Fa-f]{8}\b", text))
        labels.update(referenced - defined)
    return "".join(f"{name} = 0x{name[2:]};\n" for name in sorted(labels))


def inventory(script: str, staging: Path, asm: Path, src: Path, compiler: str) -> tuple[str, list[str]]:
    groups: dict[str, list[str]] = {"C": [], "ASM": [], "ASSET": []}
    edges = []
    seen = set()
    # Splat's legacy and current scripts both name an object followed by sections.
    pattern = re.compile(r'("?)([^\s"(){};]+\.(?:s|c|bin)\.o)\1(?=\s*\()')

    def replace(match: re.Match[str]) -> str:
        original = Path(match.group(2))
        # Resolve from the isolated Splat base directory.
        try:
            source_path = original if original.is_absolute() else staging / original
            relative = source_path.resolve().relative_to(staging.resolve())
        except ValueError as error:
            raise ValueError(f"linker object outside extraction: {original}") from error
        spelling = str(relative)
        if spelling.startswith("asm/") and spelling.endswith(".s.o"):
            group, obj = "ASM", Path("obj") / (spelling[:-4] + ".o")
            extracted_source = staging / spelling[:-2]
            if not extracted_source.exists() and spelling.endswith(".bss.s.o"):
                sections = re.findall(re.escape(match.group(2)) + r"\s*\(([^)]+)\)", script)
                if not sections or any(section != ".bss" for section in sections):
                    raise ValueError(f"missing assembly {extracted_source}")
                publish(extracted_source, b".section .bss\n")
            source = asm / str(relative.relative_to("asm"))[:-2]
        elif spelling.startswith("src/") and spelling.endswith(".c.o"):
            group, obj = "C", Path("obj") / (spelling[:-4] + ".o")
            source = src / str(relative.relative_to("src"))[:-2]
        elif spelling.startswith("assets/") and spelling.endswith(".bin.o"):
            group, obj = "ASSET", Path("obj") / relative
            source = asm / relative.with_suffix("")
        else:
            raise ValueError(f"unsupported linker object {original}")
        target = "$(BUILD)/" + str(obj)
        if target not in seen:
            groups[group].append(target)
            edges.append(f"{target if group == 'ASSET' else target[:-2] + '.built'}: {source}")
            if group != "C":
                edges.append(f"{source}: | $(BUILD)/.split")
            seen.add(target)
        return str(obj)

    rewritten = pattern.sub(replace, script)
    if not seen:
        raise ValueError("splat linker script names no .s.o, .c.o, or .bin.o objects")
    lines = [f"{kind}_OBJECTS := {' '.join(objects)}" for kind, objects in groups.items()]
    lines.extend(
        [
            "OBJECTS := $(C_OBJECTS) $(ASM_OBJECTS) $(ASSET_OBJECTS)",
            "DEPFILES := $(C_OBJECTS:.o=.d) $(ASM_OBJECTS:.o=.d)",
            *edges,
        ]
    )
    return rewritten, lines


def partial_rows(text: str, src: Path) -> str:
    """Select guarded C for assembly rows in the optional partial build only."""
    pattern = re.compile(r"^(\s*-\s*\[\s*(?:0[xX][\da-fA-F]+|\d+)\s*,\s*)asm(\s*,\s*)([^,\]\n]+)([^\n]*\]\s*)$", re.M)

    def replace(match: re.Match[str]) -> str:
        name = scalar(match[3])
        source = src / (name + ".c")
        if not source.is_file():
            return match[0]
        content = source.read_text()
        if not content.startswith("#ifdef NON_MATCHING\n"):
            return match[0]
        if not content.rstrip().endswith("#endif"):
            raise ValueError(f"{source}: NON_MATCHING.guard is invalid")
        return match[1] + "c" + match[2] + json.dumps(name) + match[4]

    return pattern.sub(replace, text)


def extract(args: argparse.Namespace) -> None:
    root = Path.cwd()
    split = args.split.resolve()
    text = split.read_text()
    text, alignments = alignment_rows(text)
    if args.non_matching == "1":
        text = partial_rows(text, args.src)
    # Splat merges the overlay's options using the first config's anchor.
    # Override base_path too, to make every output and input independent of YAML location.
    build = args.build.resolve()
    build.mkdir(parents=True, exist_ok=True)
    recipe = json.loads(args.recipe.read_text())
    compiler = recipe["compilers"][recipe["assembly_compiler"]]["kind"] if recipe["assembly_compiler"] else "ido"
    digest = hashlib.sha256()
    for path in (
        args.baserom,
        args.split,
        args.symbols,
        args.recipe,
        Path(__file__),
        Path(__file__).with_name("rodata.py"),
    ):
        content = path.read_bytes()
        digest.update(len(content).to_bytes(8, "big"))
        digest.update(content)
    digest.update(text.encode())
    digest.update(args.non_matching.encode())
    receipt = build / ".extract-key"
    graph_path = build / ".split.mk"
    if receipt.exists() and receipt.read_text() == digest.hexdigest() and graph_path.exists():
        # Make needs a timestamp receipt when input mtimes changed but bytes did not.
        graph_path.touch()
        return
    with tempfile.TemporaryDirectory(prefix=".extract-", dir=build) as temporary:
        staging = Path(temporary)
        options = {
            "base_path": str(staging),
            "target_path": str(args.baserom.resolve()),
            "asm_path": str(staging / "asm"),
            "src_path": str(staging / "src"),
            "asset_path": str(staging / "assets"),
            "build_path": str(root),
            "ld_script_path": str(staging / "layout.ld"),
            "cache_path": str(staging / "cache"),
            "symbol_addrs_path": str(args.symbols.resolve()),
            "undefined_funcs_auto_path": str(staging / "undefined_funcs_auto.txt"),
            "undefined_syms_auto_path": str(staging / "undefined_syms_auto.txt"),
            "generated_asm_macros_directory": str(staging / "include"),
            "ld_legacy_generation": True,
            "create_asm_dependencies": False,
            "dump_symbols": True,
            "extensions_path": str(root / "tools" / "splat_ext"),
            "compiler": "SN64" if compiler == "sn64" else "IDO",
        }
        overlay = staging / "outputs.yaml"
        config = staging / "input.yaml"
        config.write_text(text)
        options["base_path"] = str(staging)
        overlay.write_text("options:\n" + "".join(f"  {key}: {json.dumps(value)}\n" for key, value in options.items()))
        result = subprocess.run(
            [args.splat, "split", str(config), str(overlay)],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )
        if result.returncode:
            sys.stderr.write(result.stdout.decode(errors="replace"))
            raise subprocess.CalledProcessError(result.returncode, result.args)
        script = defer_bss((staging / "layout.ld").read_text())
        rewritten, graph = inventory(script, staging, args.asm, args.src, compiler)
        rewritten = render_alignment(rewritten, alignments)
        for directory in ("asm", "assets", "include"):
            extracted = staging / directory
            if extracted.exists():
                for path in extracted.rglob("*"):
                    if path.is_file():
                        relative = path.relative_to(extracted)
                        destination = args.asm / (directory if directory != "asm" else "") / relative
                        publish(destination, path.read_bytes())
        tables = [args.symbols]
        symbol_dump = staging / ".splat" / "splat_symbols.csv"
        publish(args.build / "splat_symbols.csv", symbol_dump.read_bytes())
        committed = discovered_symbols(symbol_dump, symbols_from(tables))
        units = unit_addresses(text)
        for name, address in units.items():
            if name in committed and committed[name] != address:
                raise ValueError(f"split and symbols disagree for {name}")
            committed[name] = address
        definitions = "".join(f"PROVIDE({name} = 0x{address:08X});\n" for name, address in sorted(committed.items()))
        publish(args.build / "committed_symbols.ld", definitions.encode())
        link_scripts = ["$(BUILD)/committed_symbols.ld"]
        for filename in ("undefined_funcs_auto.txt", "undefined_syms_auto.txt"):
            path = staging / filename
            if not path.is_file():
                raise ValueError(f"splat output {filename} is missing")
            if filename == "undefined_syms_auto.txt" and compiler != "sn64":
                path.write_text(path.read_text() + external_labels(staging / "asm"))
            path.write_text(automatic_symbols(path.read_text(), committed))
            tables.append(path)
            publish(args.build / filename, path.read_bytes())
            link_scripts.append("$(BUILD)/" + filename)
        symbols = symbols_from(tables)
        for name, address in units.items():
            if name in symbols and symbols[name] != address:
                raise ValueError(f"split and symbols disagree for {name}")
            symbols[name] = address
        addresses = "".join(
            f"{name} 0x{value:08X}{' unit' if name in units else ''}\n" for name, value in sorted(symbols.items())
        )
        publish(args.build / "symbol-addresses.txt", addresses.encode())
        publish(args.build / "unit-ranges.json", json.dumps(unit_ranges(text), sort_keys=True).encode())
        publish(args.build / (args.name + ".ld"), rewritten.encode())
        graph.extend(["LINK_SCRIPTS := " + " ".join(link_scripts), f"ROM_BYTES := {args.baserom.stat().st_size}"])
        # This file is the successful extraction receipt; replace it last.
        destination = args.build / ".split.mk"
        destination.write_text("\n".join(graph) + "\n")
        receipt.write_text(digest.hexdigest())


def main() -> None:
    if sys.argv[1:2] == ["prepare-build"]:
        parser = argparse.ArgumentParser()
        parser.add_argument("prepare-build")
        parser.add_argument("--build", type=Path, required=True)
        try:
            prepare_build(parser.parse_args().build)
        except (OSError, ValueError) as error:
            parser.exit(1, f"HELD(build): {error}\n")
        return
    parser = argparse.ArgumentParser()
    for name in ("split", "symbols", "baserom", "build", "asm", "src"):
        parser.add_argument("--" + name, type=Path, required=True)
    parser.add_argument("--non-matching", choices=("0", "1"), required=True)
    parser.add_argument("--name", required=True)
    parser.add_argument("--splat", required=True)
    parser.add_argument("--recipe", type=Path, required=True)
    try:
        extract(parser.parse_args())
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        parser.exit(1, f"HELD(extract): {error}\n")


if __name__ == "__main__":
    main()
