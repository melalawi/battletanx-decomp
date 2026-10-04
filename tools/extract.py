#!/usr/bin/env python3
"""Extract a version and describe the exact files in splat's linker script."""

from __future__ import annotations

import argparse
import ast
import csv
import hashlib
import json
import os
import re
import subprocess
import sys
import tarfile
import tempfile
from itertools import pairwise
from pathlib import Path
from typing import Any

from cache import Cache
import atomic as atomic_files
from atomic import receipt as refresh_receipt
from atomic import write
from compile import cache_root
from rodata import defer_bss


def prepare_build(build: Path) -> None:
    """Publish a standalone build through the numbered generation directory."""
    build.parent.mkdir(parents=True, exist_ok=True)
    if build.is_symlink():
        if not build.is_dir():
            raise ValueError(f"{build}: build generation symlink is invalid")
        # Retained proof generations share immutable assembly directories.
        # Ordinary Make may rebuild assembly, so detach before reading its graph.
        for name in ("asm", "assets"):
            path = build / "obj" / name
            if path.is_symlink():
                source = path.resolve()
                path.unlink()
                atomic_files.copytree(source, path, symlinks=True)
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


# Files one extraction wrote: content digest by path, for its cache record.
_WRITTEN: dict[str, str] = {}


def publish(path: Path, content: bytes) -> None:
    """Keep timestamps when extraction produced the same bytes."""
    _WRITTEN[str(path)] = hashlib.sha256(content).hexdigest()
    path.parent.mkdir(parents=True, exist_ok=True)
    if not path.exists() or path.read_bytes() != content:
        write(path, content)


def assembly_symbols(
    directory: Path, includes: Path, symbols: dict[str, int], units: dict[str, int], build: Path
) -> None:
    """Publish only each assembly source's named addresses, retaining unchanged mtimes.

    Include closure tokens cover symbols supplied by assembler/preprocessor macros.
    Unit placement is an input to SN64's external branch encoder even when the
    source does not explicitly name its split unit.
    """
    token = re.compile(r"[A-Za-z_.$][\w.$]*")
    include = re.compile(r'^\s*(?:#\s*include|\.include)\s*[<"]([^>"]+)[>"]', re.M)
    memo: dict[Path, tuple[set[str], list[Path]]] = {}

    def references(source: Path) -> set[str]:
        names: set[str] = set()
        pending, visited = [source], set()
        while pending:
            path = pending.pop().resolve()
            if path in visited:
                continue
            visited.add(path)
            if path not in memo:
                text = re.sub(r"/\*.*?\*/", "", path.read_text(), flags=re.S)
                headers = include.findall(text)
                # Comments and string literals do not reference address definitions.
                text = re.sub(r'"[^"\n]*"|(?<!\S)#(?!\s*(?:define|if|elif|ifdef|ifndef|include)\b)[^\n]*', "", text)
                dependencies = []
                for name in headers:
                    candidates = (path.parent / name, includes / name, directory / name)
                    header = next((candidate for candidate in candidates if candidate.is_file()), None)
                    if header is None:
                        raise ValueError(f"assembly include {name} missing for {path.name}")
                    dependencies.append(header)
                memo[path] = set(token.findall(text)), dependencies
            tokens, headers_paths = memo[path]
            names.update(tokens)
            pending.extend(headers_paths)
        return names

    for source in sorted(directory.rglob("*.s")):
        names = references(source) | {source.stem}
        content = "".join(
            f"{name} 0x{symbols[name]:08X}{' unit' if name in units else ''}\n"
            for name in sorted(names & symbols.keys())
        )
        publish(build / "asm-symbols" / source.relative_to(directory).with_suffix(".txt"), content.encode())


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


def pool_rows(text: str, *, storage: bool = False) -> list[dict[str, Any]]:
    """Derive all native pool slices, with structural owner paths preserved."""
    blocks = re.split(r"(?=^  - )", text, flags=re.M)
    found: list[dict[str, Any]] = []
    for block_index, block in enumerate(blocks):
        if not re.search(r"^    type: code$", block, re.M):
            continue
        start = re.search(r"^    start: (\S+)", block, re.M)
        vram = re.search(r"^    vram: (\S+)", block, re.M)
        if not start or not vram:
            raise ValueError("layout.pool_span: code segment requires start and vram")
        rows = re.findall(r"^      - \[\s*(0x[\da-fA-F]+|\d+)\s*,\s*([^,\]]+)\s*,\s*([^,\]]+)", block, re.M)
        for index, (offset, kind, name) in enumerate(rows):
            if kind.strip().lstrip(".") not in (("data", "rodata", "rdata") if storage else ("rodata", "rdata")):
                continue
            if index + 1 < len(rows):
                end = int(rows[index + 1][0], 0)
            else:
                following = blocks[block_index + 1] if block_index + 1 < len(blocks) else ""
                boundary = re.search(r"^  - \[\s*(0x[\da-fA-F]+|\d+)|^    start: (\S+)", following, re.M)
                if boundary is None:
                    raise ValueError(f"layout.pool_span: {name}: end missing")
                end = int(boundary[1] or boundary[2], 0)
            path = scalar(name)
            parts = Path(path).parts
            structural = len(parts) == 3 and parts[0] == "rodata"
            owner = parts[1] if structural and parts[1] not in ("shared", "unresolved", "writable") else None
            if kind.strip().startswith(".") and not structural:
                owner = Path(path).name
            rom = int(offset, 0)
            if rom >= end:
                raise ValueError(f"layout.pool_span: {name}: empty or reversed slice")
            found.append(
                dict(
                    start=rom,
                    end=end,
                    address=int(vram[1], 0) + rom - int(start[1], 0),
                    path=path,
                    section="." + kind.strip().lstrip("."),
                    owner=owner,
                    kind="private" if owner else "shared" if structural and parts[1] == "shared" else "unresolved",
                )
            )
    ordered = sorted(found, key=lambda row: row["start"])
    if any(a["end"] > b["start"] for a, b in pairwise(ordered)):
        raise ValueError("layout.pool_span: overlapping pool slices")
    return found


def unit_ranges(text: str) -> dict[str, dict[str, Any]]:
    blocks = re.split(r"(?=^  - )", text, flags=re.M)
    found: dict[str, dict[str, Any]] = {}
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
            found[Path(scalar(name)).name] = dict(
                start=rom_offset, end=end, address=int(vram[1], 0) + rom_offset - int(start[1], 0)
            )
    for row in pool_rows(text):
        if row["owner"] in found:
            interval = found[row["owner"]]
            interval.setdefault("rodata_slices", []).append(row)
            # A contiguous native .rodata row remains a supported representation.
            if not row["path"].startswith("rodata/"):
                interval["rodata_address"] = row["address"]
    return found


def raw_storage(row: dict[str, Any], image: bytes) -> str:
    """Emit the complete byte extent without object-relative numeric alignment."""
    if not 0 <= row["start"] < row["end"] <= len(image):
        raise ValueError("layout.pool_span: storage outside ROM bytes")
    material = image[row["start"] : row["end"]]
    flags = "a" if row["section"] in (".rdata", ".rodata") else "wa"
    return f'.section {row["section"]}, "{flags}"\n' + "".join(
        ".byte " + ",".join(f"0x{value:02X}" for value in material[offset : offset + 16]) + "\n"
        for offset in range(0, len(material), 16)
    )


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


def instruction_symbols(directory: Path, committed: dict[str, int]) -> dict[str, int]:
    """Retain symbolic addresses proved by original HI16/LO16 words.

    Some interior data labels are omitted from the disassembler's CSV. Decode
    its original instruction comments rather than infer addresses from names.
    """
    found = dict(committed)
    pattern = re.compile(
        r"/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s*\*/"
        r"[^\n]*?%(hi|lo)\(([A-Za-z_.$][\w.$]*)\)"
    )
    for path in directory.rglob("*.s"):
        pending: dict[str, list[int]] = {}
        for raw, kind, name in pattern.findall(path.read_text()):
            word = int(raw, 16)
            if kind == "hi" and word >> 26 == 15:
                pending.setdefault(name, []).append((word & 65535) << 16)
            elif kind == "lo":
                low = word & 65535
                low = low - 65536 if low & 32768 else low
                for high in pending.pop(name, []):
                    address = (high + low) & 0xFFFFFFFF
                    if name in found and found[name] != address:
                        raise ValueError(f"conflicting instruction address for {name} in {path.name}")
                    found[name] = address
    return found


def inventory(script: str, staging: Path, asm: Path, src: Path, compiler: str) -> tuple[str, list[str]]:
    groups: dict[str, list[str]] = {"C": [], "ASM": [], "ASSET": []}
    edges = []
    seen = set()
    # Splat's legacy and current scripts both name an object followed by sections.
    pattern = re.compile(r'("?)([^\s"(){};]+\.(?:s|c|bin)\.o)\1(?=\s*\()')
    base = str(staging.resolve())

    def replace(match: re.Match[str]) -> str:
        original = Path(match.group(2))
        # Resolve from the isolated Splat base directory; it holds no symbolic links.
        spelling = os.path.relpath(os.path.normpath(os.path.join(base, match.group(2))), base)
        if spelling.startswith(".."):
            raise ValueError(f"linker object outside extraction: {original}")
        relative = Path(spelling)
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
            if group == "ASM" and compiler == "sn64":
                symbol_input = "$(BUILD)/asm-symbols/" + str(obj.relative_to("obj/asm").with_suffix(".txt"))
                edges.append(f"{target[:-2] + '.built'}: {symbol_input}")
                edges.append(f"{symbol_input}: | $(BUILD)/.split")
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


_C_ROW = re.compile(r"^(\s*-\s*\[\s*(?:0[xX][\da-fA-F]+|\d+)\s*,\s*)c(\s*,\s*)([^,\]\n]+)([^\n]*\]\s*)$", re.M)
# Splat outputs that do not depend on whether a code row is C or assembly.
_SPLAT_OUTPUTS = (
    "asm",
    "assets",
    "include",
    "layout.ld",
    ".splat",
    "undefined_funcs_auto.txt",
    "undefined_syms_auto.txt",
)


def disassemble(
    args: argparse.Namespace, text: str, staging: Path, config: Path, overlay: Path, store: Cache, root: Path
) -> None:
    """Run splat with every C row disassembled, reusing an identical earlier run.

    Switching a row between C and assembly changes only object spellings, so a
    batch that publishes C reuses the disassembly of the unchanged boundaries.
    """
    names = [scalar(match[3]) for match in _C_ROW.finditer(text)]
    assembly = _C_ROW.sub(lambda match: match[1] + "asm" + match[2] + match[3] + match[4], text)
    digest = hashlib.sha256()
    extensions = sorted((root / "tools" / "splat_ext").rglob("*")) if (root / "tools" / "splat_ext").is_dir() else []
    for path in (args.baserom, args.symbols, args.recipe, Path(__file__), *extensions):
        if path.is_file():
            content = path.read_bytes()
            label = str(path.relative_to(root)) if path.is_absolute() and path.is_relative_to(root) else path.name
            digest.update(label.encode() + len(content).to_bytes(8, "big") + content)
    # The staging and project directories differ per build tree; splat output does not name them.
    options = overlay.read_text().replace(str(staging), "<staging>").replace(str(root), "<root>")
    for word in (assembly, options, Path(args.splat).name):
        digest.update(len(word).to_bytes(8, "big") + word.encode())
    cached = store.get("splat", digest.hexdigest())
    if cached is not None:
        with tarfile.open(cached) as archive:
            archive.extractall(staging, filter="tar")
    else:
        atomic_files.text(config, assembly)
        result = subprocess.run(
            [args.splat, "split", str(config), str(overlay)],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )
        if result.returncode:
            sys.stderr.write(result.stdout.decode(errors="replace"))
            raise subprocess.CalledProcessError(result.returncode, result.args)
        bundle = staging / ".splat-outputs.tar"
        with atomic_files.staging(bundle) as pending, tarfile.open(pending, "w") as archive:
            for name in _SPLAT_OUTPUTS:
                if (staging / name).exists():
                    archive.add(staging / name, arcname=name)
        store.put("splat", digest.hexdigest(), bundle)
        bundle.unlink()
    if not names:
        return
    # Name the C rows' objects as splat does for C, in the script and symbol dump.
    script = staging / "layout.ld"
    spelled = script.read_text()
    for name in names:
        spelled = re.sub(rf"(?<![\w/.])asm/{re.escape(name)}\.s\.o\b", f"src/{name}.c.o", spelled)
        spelled = re.sub(rf"/asm/{re.escape(name)}\.s\.o\b", f"/src/{name}.c.o", spelled)
    atomic_files.text(script, spelled)
    dump = staging / ".splat" / "splat_symbols.csv"
    owners = {Path(name).name for name in names}
    lines = dump.read_text().splitlines(keepends=True)
    for index, line in enumerate(lines):
        fields = line.rstrip("\n").split(",")
        if len(fields) > 2 and fields[-1] == "asm" and fields[-2] in owners:
            lines[index] = ",".join([*fields[:-1], "c"]) + "\n"
    atomic_files.text(dump, "".join(lines))


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
    for word in (str(args.asm), str(args.src), args.name, compiler):
        digest.update(len(word).to_bytes(8, "big") + word.encode())
    receipt = build / ".extract-key"
    graph_path = build / ".split.mk"
    if receipt.exists() and receipt.read_text() == digest.hexdigest() and graph_path.exists():
        # Make needs a timestamp receipt when input mtimes changed but bytes did not.
        refresh_receipt(graph_path)
        return
    # A fresh generation reuses an identical extraction whose published
    # assembly is still present byte for byte.
    store = Cache(cache_root())
    cached = store.get("extract", digest.hexdigest())
    if cached is not None and _restore(json.loads(cached.read_bytes()), build):
        write(receipt, digest.hexdigest().encode())
        return
    _WRITTEN.clear()

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
        options["base_path"] = str(staging)
        atomic_files.text(
            overlay, "options:\n" + "".join(f"  {key}: {json.dumps(value)}\n" for key, value in options.items())
        )
        disassemble(args, text, staging, config, overlay, store, root)
        # Floating directives align relative to an object, while native rows
        # may start between alignment boundaries. Retain exact ROM bytes in
        # independent assembly storage; discovered addresses remain explicit
        # linker definitions. Text retains its actual symbolic relocations.
        image = args.baserom.read_bytes()
        for row in pool_rows(text, storage=True):
            source = staging / "asm" / "data" / (row["path"] + row["section"] + ".s")
            if source.is_file():
                atomic_files.text(source, raw_storage(row, image))
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
        prune_stale(args.asm, text, {Path(name).resolve() for name in _WRITTEN})
        tables = [args.symbols]
        symbol_dump = staging / ".splat" / "splat_symbols.csv"
        publish(args.build / "splat_symbols.csv", symbol_dump.read_bytes())
        committed = instruction_symbols(staging / "asm", discovered_symbols(symbol_dump, symbols_from(tables)))
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
                atomic_files.text(path, path.read_text() + external_labels(staging / "asm"))
            atomic_files.text(path, automatic_symbols(path.read_text(), committed))
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
        if compiler == "sn64":
            assembly_symbols(staging / "asm", staging / "include", symbols, units, args.build)
        publish(args.build / "unit-ranges.json", json.dumps(unit_ranges(text), sort_keys=True).encode())
        publish(args.build / "pool-providers.json", json.dumps(pool_rows(text, storage=True), sort_keys=True).encode())
        publish(args.build / (args.name + ".ld"), rewritten.encode())
        graph.extend(["LINK_SCRIPTS := " + " ".join(link_scripts), f"ROM_BYTES := {args.baserom.stat().st_size}"])
        # This file is the successful extraction receipt; replace it last.
        destination = args.build / ".split.mk"
        write(destination, ("\n".join(graph) + "\n").encode())
        outputs, published = {".split.mk": destination.read_text()}, {}
        for name, value in _WRITTEN.items():
            path = Path(name).resolve()
            if path.is_relative_to(build):
                outputs[str(path.relative_to(build))] = path.read_text()
            else:
                published[name] = value
        record = build / ".extract-record.json"
        write(record, json.dumps({"outputs": outputs, "published": published}, sort_keys=True).encode())
        store.put("extract", digest.hexdigest(), record)
        record.unlink()
        write(receipt, digest.hexdigest().encode())


def prune_stale(asm: Path, text: str, written: set[Path]) -> int:
    """Remove matched C assembly and pool files this extraction no longer emits."""
    matched = {
        Path(scalar(name)).with_suffix(".s")
        for name in re.findall(r"^\s*-\s*\[\s*[\w]+\s*,\s*c\s*,\s*([^,\]]+)", text, re.M)
    }
    count = 0
    for path in sorted(asm.rglob("*.s")):
        relative = path.relative_to(asm)
        if relative not in matched and (relative.parts[0] != "data" or path.resolve() in written):
            continue
        path.unlink()
        _WRITTEN.pop(str(path), None)
        count += 1
    return count


def _restore(record: dict[str, Any], build: Path) -> bool:
    """Write a cached extraction's build files when its published files are unchanged."""
    for name, expected in record["published"].items():
        path = Path(name)  # relative to the project root, the working directory
        try:
            if hashlib.sha256(path.read_bytes()).hexdigest() != expected:
                return False
        except OSError:
            return False
    graph = record["outputs"].pop(".split.mk")
    for name, content in record["outputs"].items():
        publish(build / name, content.encode())
    # The graph is the extraction receipt Make reads; write it last.
    write(build / ".split.mk", graph.encode())
    return True


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
