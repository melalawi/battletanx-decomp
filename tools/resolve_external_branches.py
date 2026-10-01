#!/usr/bin/env python3
"""Encode branches ASN64 cannot relocate, using explicit version placements."""

from __future__ import annotations

import argparse
import re
from pathlib import Path

CONDITIONAL = {
    "b",
    "bal",
    "beq",
    "bne",
    "beql",
    "bnel",
    "beqz",
    "bnez",
    "blez",
    "bgtz",
    "blezl",
    "bgtzl",
    "bltz",
    "bgez",
    "bltzl",
    "bgezl",
    "bltzal",
    "bgezal",
    "bc1f",
    "bc1t",
    "bc1fl",
    "bc1tl",
}
JUMPS = {"j": 2, "jal": 3}
TRAPS = {"tge": 48, "tgeu": 49, "tlt": 50, "tltu": 51, "teq": 52, "tne": 54}
BRANCHES = CONDITIONAL | set(JUMPS) | {"jr", "jalr"}
SYMBOL = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")
RELATIVE = re.compile(r"\.\s*\+\s*4\s*\+\s*\(\s*(-?(?:0x[\da-fA-F]+|\d+))\s*<<\s*2\s*\)")
LABEL = re.compile(r"^\s*([A-Za-z_][\w]*):\s*$")


def register(value: str) -> int:
    names = [
        "zero",
        "at",
        "v0",
        "v1",
        "a0",
        "a1",
        "a2",
        "a3",
        "t0",
        "t1",
        "t2",
        "t3",
        "t4",
        "t5",
        "t6",
        "t7",
        "s0",
        "s1",
        "s2",
        "s3",
        "s4",
        "s5",
        "s6",
        "s7",
        "t8",
        "t9",
        "k0",
        "k1",
        "gp",
        "sp",
        "fp",
        "ra",
    ]
    value = value.removeprefix("$")
    if value in names:
        return names.index(value)
    if value.isdecimal() and 0 <= int(value) <= 31:
        return int(value)
    raise ValueError(f"unsupported register ${value}")


def instruction(line: str) -> tuple[str, list[str]] | None:
    body = re.sub(r"/\*.*?\*/", "", line).split("#", 1)[0].strip()
    if not body or body.startswith(".") or body.endswith(":"):
        return None
    parts = body.split(None, 1)
    return parts[0], [x.strip() for x in parts[1].split(",")] if len(parts) == 2 else []


def width(line: str) -> int:
    body = re.sub(r"/\*.*?\*/", "", line).split("#", 1)[0].strip()
    if re.match(r"\.word\s", body):
        return 4 * len(body.split(None, 1)[1].split(","))
    parsed = instruction(line)
    if parsed and parsed[0] not in {"glabel", "dlabel", "jlabel", "alabel", "endlabel", "enddlabel", "nonmatching"}:
        return 4
    return 0


def encode(mnemonic: str, operands: list[str], pc: int, target: int) -> int:
    delta = target - pc - 4
    if delta % 4 or not -131072 <= delta < 131072:
        raise ValueError(f"branch target 0x{target:08X} out of range at 0x{pc:08X}")
    immediate = (delta // 4) & 0xFFFF
    if mnemonic == "b":
        return (4 << 26) | immediate
    if mnemonic == "bal":
        return (1 << 26) | (17 << 16) | immediate
    if mnemonic in {"beq", "bne", "beql", "bnel"}:
        opcode = {"beq": 4, "bne": 5, "beql": 20, "bnel": 21}[mnemonic]
        return (opcode << 26) | (register(operands[0]) << 21) | (register(operands[1]) << 16) | immediate
    if mnemonic in {"beqz", "bnez"}:
        return ((4 if mnemonic == "beqz" else 5) << 26) | (register(operands[0]) << 21) | immediate
    if mnemonic in {"blez", "bgtz", "blezl", "bgtzl"}:
        opcode = {"blez": 6, "bgtz": 7, "blezl": 22, "bgtzl": 23}[mnemonic]
        return (opcode << 26) | (register(operands[0]) << 21) | immediate
    if mnemonic in {"bltz", "bgez", "bltzl", "bgezl", "bltzal", "bgezal"}:
        rt = {"bltz": 0, "bgez": 1, "bltzl": 2, "bgezl": 3, "bltzal": 16, "bgezal": 17}[mnemonic]
        return (1 << 26) | (register(operands[0]) << 21) | (rt << 16) | immediate
    rt = {"bc1f": 0, "bc1t": 1, "bc1fl": 2, "bc1tl": 3}[mnemonic]
    return (17 << 26) | (8 << 21) | (rt << 16) | immediate


def read_symbols(path: Path) -> tuple[dict[str, int], set[str]]:
    symbols, units = {}, set()
    for line in path.read_text().splitlines():
        fields = line.split()
        if len(fields) not in {2, 3}:
            raise ValueError(f"malformed symbol in {path}: {line}")
        symbols[fields[0]] = int(fields[1], 0)
        if len(fields) == 3 and fields[2] == "unit":
            units.add(fields[0])
    return symbols, units


def resolve(text: str, unit: str, symbols: dict[str, int], units: set[str]) -> str:
    text = re.sub(r"\.L([0-9A-Fa-f]+)", r"L_\1", text)
    # Keep the function open through any trailing interval instructions.
    lines, pending = [], None
    raw = text.splitlines()
    for index, line in enumerate(raw):
        if re.match(r"\s*\.end\s", line):
            pending = line
            continue
        entry = re.match(r"\s*\.globl\s+(\w+)\s*$", line)
        following = raw[index + 1].split() if index + 1 < len(raw) else []
        if pending and entry and following[:2] == [".ent", entry[1]]:
            lines.append(pending)
            pending = None
        lines.append(line)
    if pending:
        lines.append(pending)
    if unit not in symbols:
        if any((parsed := instruction(line)) and parsed[0] in BRANCHES for line in lines):
            raise ValueError(f"unit {unit} is missing from symbol-addresses.txt")
        return text
    base = symbols[unit]
    addresses = dict(symbols)
    pc, started = base, False
    defined = set()
    for line in lines:
        label = LABEL.match(line)
        macro = re.match(r"\s*(?:glabel|alabel|jlabel|dlabel)\s+(\w+)", line)
        name = label[1] if label else macro[1] if macro else None
        if name:
            if not started and name in addresses and addresses[name] != base:
                raise ValueError(f"unit {unit} starts at conflicting label {name}")
            started = True
            addresses.setdefault(name, pc)
            defined.add(name)
        elif started:
            pc += width(line)
    pc, started, delay = base, False, False
    output = []
    for line in lines:
        label = LABEL.match(line)
        macro = re.match(r"\s*(?:glabel|alabel|jlabel|dlabel)\s+(\w+)", line)
        if label or macro:
            started = True
            output.append(line)
            continue
        parsed = instruction(line) if started else None
        if parsed:
            mnemonic, operands = parsed
            word = None
            if mnemonic in CONDITIONAL:
                target_name = operands[-1]
                relative = RELATIVE.fullmatch(target_name)
                target = addresses.get(target_name)
                if target is None and re.fullmatch(r"L_[\da-fA-F]{8}", target_name):
                    target = int(target_name[2:], 16)
                if relative:
                    target = pc + 4 + (int(relative[1], 0) << 2)
                if target is None:
                    raise ValueError(f"branch target {target_name} missing for {unit}")
                word = encode(mnemonic, operands, pc, target)
            elif mnemonic in JUMPS and operands[-1] not in defined and operands[-1] not in units:
                target = addresses.get(operands[-1])
                if target is None and re.fullmatch(r"L_[\da-fA-F]{8}", operands[-1]):
                    target = int(operands[-1][2:], 16)
                if target is not None:
                    if target >> 28 != (pc + 4) >> 28:
                        raise ValueError(f"jump target {operands[-1]} outside region for {unit}")
                    word = (JUMPS[mnemonic] << 26) | ((target >> 2) & 0x03FFFFFF)
            elif mnemonic == "jr" and delay:
                word = (register(operands[0]) << 21) | 8
            elif mnemonic in TRAPS:
                code = int(operands[2], 0) if len(operands) > 2 else 0
                word = (
                    (register(operands[0]) << 21)
                    | (register(operands[1]) << 16)
                    | ((code & 1023) << 6)
                    | TRAPS[mnemonic]
                )
            elif mnemonic in {"div", "divu", "mult", "multu"}:
                if len(operands) != 2:
                    raise ValueError(f"{mnemonic}: expected two register operands")
                function = {"div": 26, "divu": 27, "mult": 24, "multu": 25}[mnemonic]
                word = (register(operands[0]) << 21) | (register(operands[1]) << 16) | function
            elif mnemonic in {"mfhi", "mflo"}:
                word = (register(operands[0]) << 11) | (16 if mnemonic == "mfhi" else 18)
            if word is not None:
                line = f"    .word 0x{word:08X}"
            if width(line):
                delay = mnemonic in BRANCHES
        if started:
            pc += width(line)
        output.append(line)
    return "\n".join(output) + "\n"


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("source", type=Path)
    parser.add_argument("destination", type=Path)
    parser.add_argument("--symbols", type=Path, required=True)
    parser.add_argument("--unit", required=True)
    args = parser.parse_args()
    try:
        symbols, units = read_symbols(args.symbols)
        args.destination.write_text(resolve(args.source.read_text(), args.unit, symbols, units))
    except (OSError, ValueError) as error:
        parser.exit(1, f"HELD(resolve-branches): {error}\n")


if __name__ == "__main__":
    main()
