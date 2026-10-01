"""Expand SN64 instruction macros with explicit register and guard choices."""

from __future__ import annotations

import re

from sn64_literals import literal_words

HEADER = (
    ".macro glabel label\n    .global \\label\n    \\label:\n.endm\n"
    ".macro dlabel label\n    .global \\label\n    \\label:\n.endm\n"
    ".macro move a, b\n    addu \\a, \\b, $0\n.endm\n"
    ".macro b target\n    bgez $0, \\target\n.endm\n\t.set noreorder\n"
)
SYMBOL_BASE_OPERAND = re.compile(r"^([A-Za-z_.][A-Za-z0-9_.]*(?:[+-](?:0x[0-9a-fA-F]+|[0-9]+))?)\(\$([A-Za-z0-9]+)\)$")


def memory(opcode: str, operand: str, original: str) -> str:
    register, address = [part.strip() for part in operand.split(",", 1)]
    match = SYMBOL_BASE_OPERAND.fullmatch(address)
    if match:
        symbol, base = match.groups()
        add = "" if base in ("0", "zero") else f"\taddu $at, $at, ${base}\n"
        return f"\t.set noat\n\tlui $at, %hi({symbol})\n{add}\t{opcode} {register}, %lo({symbol})($at)\n\t.set at\n"
    match = re.fullmatch(r"(-?(?:0x[0-9a-fA-F]+|[0-9]+))\((\$\w+)\)", address)
    if match and not -32768 <= int(match[1], 0) <= 32767:
        value, base = int(match[1], 0), match[2]
        low = ((value + 32768) & 65535) - 32768
        high = ((value - low) >> 16) & 65535
        return f"\t.set noat\n\tlui $at,{high}\n\taddu $at,{base},$at\n\t{opcode} {register},{low}($at)\n\t.set at\n"
    return original


def floating(opcode: str, operands: list[str], number: int) -> str:
    double = opcode == "li.d"
    symbol = f"RODATA_SYM_{number}"
    load, alignment = ("ldc1", 3) if double else ("lwc1", 2)
    return (
        f"\t.section .rdata\n{symbol}:\n\t.align {alignment}\n"
        f"{literal_words(operands[1], double)}\n\t.text\n\t.set noat\n"
        f"\tlui $at, %hi({symbol})\n\t{load} {operands[0]}, %lo({symbol})($at)\n\t.set at\n"
    )


def division(opcode: str, operands: list[str], number: int) -> str:
    target, dividend, divisor = operands
    first, second = f"BRANCH_LABEL_{number}", f"BRANCH_LABEL_{number + 1}"
    unsigned = opcode in ("divu", "remu")
    operation = "divu" if unsigned else "div"
    result = "mfhi" if opcode in ("rem", "remu") else "mflo"
    text = (
        f"\t.set noat\n\t{operation} $0,{dividend},{divisor}\n\tbnez {divisor},{first}\n\tnop\n\tbreak 0x7\n{first}:\n"
    )
    if not unsigned:
        text += (
            f"\taddiu $1,$0,-1\n\tbne {divisor},$1,{second}\n\tlui $1,0x8000\n"
            f"\tbne {dividend},$1,{second}\n\tnop\n\tbreak 0x6\n{second}:\n"
        )
    return text + f"\t{result} {target}\n\t.set at\n"
