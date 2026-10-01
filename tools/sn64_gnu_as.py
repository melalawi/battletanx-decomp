#!/usr/bin/env python3
"""Normalize SN64 assembly and assemble directly with GNU MIPS as."""

from __future__ import annotations

import argparse
import re
import shlex
import subprocess
from pathlib import Path

from resolve_external_branches import read_symbols, resolve
from sn64_schedule import schedule


def run(command: list[str], *, cwd: str | Path | None = None) -> str:
    completed = subprocess.run(command, cwd=cwd, capture_output=True, text=True)
    if completed.returncode:
        raise ValueError(f"{command[0]} exited {completed.returncode}: {completed.stdout}{completed.stderr}")
    return completed.stdout


def string_bytes(operands: str) -> bytes:
    """Decode compiler assembly strings, including one NUL per operand."""
    result = bytearray()
    escapes = {
        "a": 7,
        "b": 8,
        "f": 12,
        "n": 10,
        "r": 13,
        "t": 9,
        "v": 11,
        '"': 34,
        "\\": 92,
    }
    remaining = operands.strip()
    while remaining:
        match = re.match(r'"((?:\\.|[^"\\])*)"', remaining)
        if match is None:
            raise ValueError(f".string: invalid operand {remaining!r}")
        content = match[1]
        position = 0
        while position < len(content):
            char = content[position]
            position += 1
            if char != "\\":
                result.extend(char.encode())
                continue
            escape = content[position]
            position += 1
            if escape in "01234567":
                digits = escape
                while position < len(content) and len(digits) < 3 and content[position] in "01234567":
                    digits += content[position]
                    position += 1
                result.append(int(digits, 8) & 0xFF)
            elif escape in escapes:
                result.append(escapes[escape])
            else:
                raise ValueError(f".string: unsupported escape \\{escape}")
        result.append(0)
        remaining = remaining[match.end() :].strip()
        if not remaining or remaining.startswith("#"):
            break
        if not remaining.startswith(",") or not remaining[1:].strip():
            raise ValueError(f".string: invalid trailing operand {remaining!r}")
        remaining = remaining[1:].strip()
    if not result:
        raise ValueError(".string: missing operand")
    return bytes(result)


def directives(text: str) -> bytes:
    lines = []
    for line in text.splitlines():
        stripped = line.strip()
        if stripped == ".set gp=64":
            continue
        if stripped.startswith((".version", ".size", ".type", ".ident")):
            continue
        literal = re.match(r"^(\s*(?:[.\w]+:\s*)?)\.string\s+(.*)$", line)
        if literal:
            content = string_bytes(literal[2])
            for offset in range(0, len(content), 16):
                prefix = literal[1] if offset == 0 else "\t"
                lines.append(prefix + ".byte " + ",".join(str(byte) for byte in content[offset : offset + 16]))
            continue
        line = line.replace(".rodata", ".rdata")
        lines.append(line)
    return ("\r\n".join(lines) + "\r\n").encode()


def normalize(text: str) -> bytes:
    return schedule(directives(text).decode()).encode()


def assemble(text: str, output: Path, assembler: Path, asflags: list[str]) -> None:
    output.parent.mkdir(parents=True, exist_ok=True)
    options = [flag for flag in asflags if flag not in {"-mips3"}]
    completed = subprocess.run(
        [
            str(assembler),
            "-march=vr4300",
            "-mabi=32",
            "-EB",
            "-G0",
            "--no-pad-sections",
            *options,
            "-o",
            str(output),
            "-",
        ],
        input=normalize(text),
        capture_output=True,
    )
    if completed.returncode:
        raise ValueError(completed.stderr.decode(errors="replace"))


def main() -> None:
    parser = argparse.ArgumentParser()
    for name in ("assembler", "symbols", "source", "output", "depfile"):
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
        assemble(text, args.output, args.assembler, options)
    except (OSError, ValueError) as error:
        parser.exit(1, f"HELD(assembly): {args.source}: {error}\n")


if __name__ == "__main__":
    main()
