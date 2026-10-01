#!/usr/bin/env python3
"""Compile or assemble a content-keyed object with the declared project recipe."""

from __future__ import annotations

import argparse
import json
import os
import re
import shutil
import subprocess
import tempfile
import tomllib
from pathlib import Path
from typing import TypedDict

from cache import Cache, key

Compiler = TypedDict(
    "Compiler", {"kind": str, "cc": str, "cflags": list[str], "as": str, "wibo": str, "obj_parser": str}
)


Recipe = TypedDict(
    "Recipe",
    {
        "units": dict[str, str],
        "default_compiler": str,
        "assembly_compiler": str | None,
        "compilers": dict[str, Compiler],
        "macros": dict[str, list[str]],
        "sn64_asflags": list[str],
        "asflags": list[str],
        "asm": str,
        "include": list[str],
        "unit_cflags": dict[str, list[str]],
        "cpp": str,
        "cppflags": list[str],
        "as": str,
    },
)


def run(command: list[str]) -> bytes:
    result = subprocess.run(command, capture_output=True)
    if result.returncode:
        raise ValueError(
            f"{command[0]} exited {result.returncode}: " + (result.stdout + result.stderr).decode(errors="replace")
        )
    return result.stdout


def compiler_for(data: Recipe, unit: str) -> str:
    direct = data["units"].get(unit)
    stem = data["units"].get(Path(unit).stem)
    if direct and stem and direct != stem:
        raise ValueError(f"[units].{unit}: conflicts with [units].{Path(unit).stem}")
    ident = direct or stem or data["default_compiler"]
    if ident not in data["compilers"]:
        raise ValueError(f"[units].{unit}: unknown compiler {ident}")
    return ident


def cache_root() -> Path:
    explicit = os.environ.get("UNBAKE_POLICY")
    base = Path(os.environ.get("XDG_CONFIG_HOME", Path.home() / ".config"))
    path = Path(explicit) if explicit else base / "unbake/policy.toml"
    with path.open("rb") as source:
        data = tomllib.load(source)
    if "cache_root" not in data:
        raise ValueError(f"{path} cache_root: missing value")
    return Path(data["cache_root"]).expanduser()


def external_branches(content: bytes) -> bytes:
    text = content.decode()
    labels = set(re.findall(r"^\s*([.\w]+):", text, re.M))
    lines = []
    for line in text.splitlines(keepends=True):
        match = re.search(
            r"/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s*\*/\s*(\w+)\s+.*?(\.L[0-9A-Fa-f]+)(?:\s*/\*.*?\*/)?\s*$",
            line,
        )
        handwritten = (
            re.search(r"/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s*\*/", line)
            if "handwritten instruction" in line and not re.search(r"%(?:hi|lo)\(", line)
            else None
        )
        if handwritten or (match and match[3] not in labels and match[2].startswith(("b", "j"))):
            if handwritten:
                word = handwritten[1]
            else:
                assert match is not None
                word = match[1]
            line = f"    .word 0x{word}" + ("\n" if line.endswith("\n") else "")
        lines.append(line)
    return "".join(lines).encode()


def compile_object(args: argparse.Namespace) -> None:
    data: Recipe = json.loads(args.recipe.read_text())
    out = args.output.resolve()
    out.parent.mkdir(parents=True, exist_ok=True)
    version = args.version
    if version not in data["macros"]:
        raise ValueError(f"version.{version}: unknown VERSION")
    assembly = args.kind == "as"
    ident = data["assembly_compiler"] if assembly else compiler_for(data, args.unit)
    compiler = data["compilers"][ident] if ident else None
    sn64 = compiler is not None and compiler["kind"] == "sn64"
    asflags = [
        *(data["sn64_asflags"] if sn64 and not assembly else data["asflags"]),
        "-I" + str(Path(data["asm"]) / version / "include"),
    ]
    flags: list[str] = []
    if not assembly:
        assert compiler is not None
        flags = [
            *compiler["cflags"],
            *("-I" + p for p in data["include"]),
            *("-D" + macro for macro in data["macros"][version]),
        ]
        if args.non_matching == "1":
            flags.append("-DNON_MATCHING=1")
        direct = data["unit_cflags"].get(args.unit)
        stem = data["unit_cflags"].get(Path(args.unit).stem)
        if direct is not None and stem is not None and direct != stem:
            raise ValueError(f"[build].unit_cflags.{args.unit}: conflicting stem flags")
        flags.extend(direct if direct is not None else stem if stem is not None else [])
    dependencies = []
    if args.depfile:
        args.depfile.parent.mkdir(parents=True, exist_ok=True)
        dependencies = ["-MMD", "-MP", "-MF", str(args.depfile), "-MT", args.dep_target or str(out)]
    if sn64:
        from sn64_cc import partition_flags

        preprocess, codeflags = partition_flags(flags)
        if assembly:
            preprocess = [flag for flag in asflags if flag.startswith("-I")]
        cppflags = ["-P", "-undef", "-nostdinc"] if assembly else data["cppflags"]
        if assembly:
            with tempfile.NamedTemporaryFile(prefix=".input-", suffix=".s", dir=out.parent) as temporary:
                temporary.write(external_branches(args.source.read_bytes()))
                temporary.flush()
                content = run([data["cpp"], *cppflags, *preprocess, *dependencies, temporary.name])
                if args.depfile:
                    text = args.depfile.read_text().replace(temporary.name, str(args.source))
                    args.depfile.write_text(text)
        else:
            content = run([data["cpp"], *cppflags, *preprocess, *dependencies, str(args.source)])
        if assembly:
            from resolve_external_branches import read_symbols, resolve

            symbols, units = read_symbols(args.symbols)
            content = resolve(content.decode(), args.source.stem, symbols, units).encode()
    elif assembly:
        # GNU assembly includes are dependency inputs, not preprocessor directives.
        include_root = Path(data["asm"]) / version / "include"
        includes = sorted(include_root.rglob("*")) if include_root.exists() else []
        content = external_branches(args.source.read_bytes())
    else:
        assert compiler is not None
        cc = compiler["cc"]
        if args.depfile:
            text = run([cc, *[f for f in flags if f != "-c"], "-M", str(args.source)]).decode()
            target = args.dep_target or str(out)
            args.depfile.write_text(target + ":" + text.split(":", 1)[1])
        content = run([cc, *[f for f in flags if f != "-c"], "-E", str(args.source)])

    manifest = args.recipe.parent / "compiler.sha256"
    pins = {}
    if manifest.is_file():
        for line in manifest.read_text().splitlines():
            fields = line.split(maxsplit=1)
            if len(fields) == 2 and not line.startswith("#"):
                pins[fields[1].lstrip("*")] = fields[0]
    selected = {
        name: digest
        for name, digest in pins.items()
        if ident and compiler is not None and str(Path(name).parent) == str(Path(compiler["cc"]).parent)
    }
    driver_names = (
        ("compile.py", "elf.py", "sn64_cc.py", "asn64.py", "resolve_external_branches.py")
        if sn64
        else ("compile.py", "elf.py")
    )
    inputs = [args.recipe.parent / name for name in driver_names]
    if assembly and not sn64:
        inputs.extend(p for p in includes if p.is_file())
        assembler = shutil.which(data["as"]) if "/" not in data["as"] else data["as"]
        if not assembler:
            raise ValueError(f"[build].as: missing executable {data['as']}")
        inputs.append(Path(assembler))
    digest = key(content, json.dumps([ident, selected, flags, asflags, data["cppflags"]], sort_keys=True), *inputs)

    def produce(destination: Path) -> None:
        with tempfile.TemporaryDirectory(prefix=".object-", dir=out.parent) as temporary:
            work = Path(temporary)
            source = work / ("source.s" if assembly else "source.i")
            source.write_bytes(content)
            if sn64:
                assert compiler is not None
                from asn64 import assemble

                if not assembly:
                    generated = work / "source.s"
                    run([str(Path(compiler["cc"]).resolve()), "-quiet", *codeflags, str(source), "-o", str(generated)])
                    text = generated.read_text()
                else:
                    text = content.decode()
                assemble(
                    text,
                    destination,
                    Path(compiler["as"]),
                    Path(compiler["wibo"]),
                    Path(compiler["obj_parser"]),
                    asflags,
                )
            elif assembly:
                command = [data["as"], *asflags]
                if args.depfile:
                    command.extend(["--MD", str(args.depfile)])
                run([*command, "-o", str(destination), str(source)])
                if args.depfile:
                    text = args.depfile.read_text()
                    args.depfile.write_text(
                        (args.dep_target or str(out))
                        + ":"
                        + text.split(":", 1)[1].replace(str(source), str(args.source))
                    )
            else:
                assert compiler is not None
                run([compiler["cc"], *flags, "-c", str(source), "-o", str(destination)])
                from elf import Object

                Object(destination).trim_text()

    cached = Cache(args.cache_root or cache_root()).produce(args.kind, digest, produce)
    if not out.exists() or out.read_bytes() != cached.read_bytes():
        temporary = out.with_name(out.name + ".partial")
        shutil.copyfile(cached, temporary)
        temporary.replace(out)
    if assembly and args.depfile and not args.depfile.exists():
        args.depfile.write_text((args.dep_target or str(out)) + ": " + str(args.source) + "\n")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--kind", choices=("cc", "as"), required=True)
    for name in ("recipe", "source", "output", "depfile", "symbols", "cache-root"):
        parser.add_argument("--" + name, type=Path, required=name in ("recipe", "source", "output"))
    parser.add_argument("--non-matching", choices=("0", "1"), required=True)
    parser.add_argument("--version", required=True)
    parser.add_argument("--unit", required=True)
    parser.add_argument("--dep-target")
    args = parser.parse_args()
    try:
        compile_object(args)
    except (OSError, ValueError, KeyError) as error:
        parser.exit(1, f"HELD(compile): {error}\n")


if __name__ == "__main__":
    main()
