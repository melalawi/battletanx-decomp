#!/usr/bin/env python3
"""Run ASN64 from a short working directory and convert its object to ELF."""

from __future__ import annotations

import argparse
import shlex
import subprocess
import tempfile
from pathlib import Path

from resolve_external_branches import read_symbols, resolve


def run(command: list[str], *, cwd: str | Path | None = None) -> str:
    completed = subprocess.run(command, cwd=cwd, capture_output=True, text=True)
    if completed.returncode:
        raise ValueError(f"{command[0]} exited {completed.returncode}: {completed.stdout}{completed.stderr}")
    return completed.stdout


def normalize(text: str) -> bytes:
    lines = []
    for line in text.splitlines():
        stripped = line.strip()
        if stripped == ".set gp=64":
            continue
        if stripped.startswith((".version", ".size", ".type", ".ident")):
            continue
        line = line.replace(".rodata", ".rdata")
        lines.append(line)
    return ("\r\n".join(lines) + "\r\n").encode()


def assemble(text: str, output: Path, assembler: Path, wibo: Path, obj_parser: Path, asflags: list[str]) -> None:
    output = output.resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix=".a-", dir=output.parent) as temporary:
        work = Path(temporary)
        source, psyq, elf = work / "a.s", work / "a.obj", work / "a.o"
        source.write_bytes(normalize(text))
        # Absolute inputs avoid the assembler's limit on working-directory length.
        options = []
        previous = False
        for flag in asflags:
            if previous:
                options.append(str(Path(flag).resolve()))
                previous = False
            elif flag == "-I":
                options.append(flag)
                previous = True
            elif flag.startswith("-I"):
                options.append("-I" + str(Path(flag[2:]).resolve()))
            else:
                options.append(flag)
        if previous:
            raise ValueError("[build].asflags contains -I without a directory")
        run([str(wibo.resolve()), str(assembler.resolve()), *options, "-o", str(psyq), str(source)], cwd="/")
        run([str(obj_parser.resolve()), str(psyq), "-o", str(elf), "-b", "-n"])
        if not elf.is_file() or not elf.stat().st_size:
            raise ValueError(f"obj_parser produced no object for {output}")
        elf.replace(output)


def main() -> None:
    parser = argparse.ArgumentParser()
    for name in ("assembler", "wibo", "obj-parser", "symbols", "source", "output", "depfile"):
        parser.add_argument("--" + name, type=Path, required=True)
    parser.add_argument("--cpp", required=True)
    parser.add_argument("--asflags", required=True)
    parser.add_argument("--dep-target")
    args = parser.parse_args()
    try:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.depfile.parent.mkdir(parents=True, exist_ok=True)
        options = shlex.split(args.asflags)
        includes = []
        previous = False
        for flag in options:
            if previous:
                includes.append(flag)
                previous = False
            elif flag == "-I":
                includes.append(flag)
                previous = True
            elif flag.startswith("-I"):
                includes.append(flag)
        text = run(
            [
                args.cpp,
                "-P",
                "-undef",
                "-nostdinc",
                "-MMD",
                "-MP",
                "-MF",
                str(args.depfile),
                "-MT",
                args.dep_target or str(args.output),
                *includes,
                str(args.source),
            ]
        )
        symbols, units = read_symbols(args.symbols)
        text = resolve(text, args.source.stem, symbols, units)
        assemble(text, args.output, args.assembler, args.wibo, args.obj_parser, options)
    except (OSError, ValueError) as error:
        parser.exit(1, f"HELD(assembly): {args.source}: {error}\n")


if __name__ == "__main__":
    main()
