"""SN64 decimal literal conversion with seventeen significant digits."""

from __future__ import annotations

import re
import struct


def literal_words(text: str, double: bool) -> str:
    match = re.fullmatch(r"([+-]?)(\d*)(?:\.(\d*))?(?:[eE]([+-]?\d+))?", text)
    if match is None or not (match[2] or match[3]):
        raise ValueError(f"unsupported floating literal {text!r}")
    fraction = match[3] or ""
    digits = (match[2] + fraction).lstrip("0")
    exponent = int(match[4] or "0") - len(fraction)
    kept = digits[:17]
    exponent += len(digits) - len(kept)
    trimmed = kept.rstrip("0")
    exponent += len(kept) - len(trimmed)
    integer = int(trimmed or "0")
    shift = max(integer.bit_length() - 53, 0)
    if shift:
        integer = ((integer + (1 << (shift - 1))) >> shift) << shift
    value = float(integer)
    if value:
        if exponent > 308:
            value *= 1e216
            exponent -= 216
        elif exponent < -308:
            value /= 1e216
            exponent += 216
        power = 1.0
        remaining = abs(exponent)
        for step in (216, 108, 54, 27, 14, 8, 4, 1):
            while remaining >= step:
                power *= 10.0**step
                remaining -= step
        value = value / power if exponent < 0 else value * power
    if match[1] == "-" and value:
        value = -value
    data = struct.pack(">d" if double else ">f", value)
    return "\n".join(f"\t.word 0x{int.from_bytes(data[i : i + 4], 'big'):08x}" for i in range(0, len(data), 4))
