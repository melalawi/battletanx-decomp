#!/usr/bin/env python3
"""Resolve named host tools from operator policy or the process environment."""

from __future__ import annotations

import os
import shutil
import sys
import tomllib
from pathlib import Path


def resolve_tool(value: str) -> str:
    name = value
    if value.startswith("policy:"):
        name = value.removeprefix("policy:")
        explicit = os.environ.get("UNBAKE_POLICY")
        base = Path(os.environ.get("XDG_CONFIG_HOME", Path.home() / ".config"))
        path = Path(explicit) if explicit else base / "unbake" / "policy.toml"
        try:
            with path.open("rb") as source:
                data = tomllib.load(source)
        except (OSError, ValueError) as error:
            raise ValueError(f"policy.{name}: {error}") from error
        configured = data.get(name)
        if not isinstance(configured, str) or not configured:
            raise ValueError(f"policy.{name}: missing executable")
        value = str(Path(configured).expanduser())
    executable = shutil.which(value)
    if executable is None:
        raise ValueError(f"{name}: missing executable")
    return str(Path(executable).resolve())


if __name__ == "__main__":
    try:
        print(resolve_tool(sys.argv[1]))
    except (OSError, ValueError, IndexError) as error:
        sys.exit(f"HELD(build): {error}")
