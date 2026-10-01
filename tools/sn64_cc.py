#!/usr/bin/env python3
"""Preprocess C, run the supplied SN64 cc1, then assemble its output."""

from __future__ import annotations


def partition_flags(flags: list[str]) -> tuple[list[str], list[str]]:
    preprocess, compile = [], []
    previous = False
    for flag in flags:
        if previous:
            preprocess.append(flag)
            previous = False
        elif flag in {"-I", "-D", "-U", "-include"}:
            preprocess.append(flag)
            previous = True
        elif flag.startswith(("-I", "-D", "-U")):
            preprocess.append(flag)
        elif flag.startswith(("-G", "-m", "-f", "-O", "-g", "-d")):
            compile.append(flag)
        elif flag != "-c":
            raise ValueError(f"unsupported [compilers].cflags value {flag}")
    if previous:
        raise ValueError("[compilers].cflags ends with a preprocessor option missing its value")
    return preprocess, compile
