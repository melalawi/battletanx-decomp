#!/usr/bin/env python3
"""Compile or assemble a content-keyed object with the declared project recipe."""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import subprocess
import tomllib
from functools import lru_cache
from pathlib import Path
from typing import cast

from cache import Cache, key
import atomic as atomic_files
from atomic import receipt, staging, write
from codegen import (
    Recipe,
    compiler_for,
    dependency_paths,
    prepare,
)
from codegen import (
    assembly_inputs as assembly_inputs,
)
from codegen import (
    codegen_flags as codegen_flags,
)
from codegen import (
    external_branches as external_branches,
)
from codegen import (
    preprocessed_dependencies as preprocessed_dependencies,
)
from compile_identity import assembler_headers, driver_content, selected_pins
from host import resolve_tool


def run(command: list[str], *, cwd: Path | None = None) -> bytes:
    if cwd is None:
        result = subprocess.run(command, capture_output=True)
    else:
        result = subprocess.run(command, capture_output=True, cwd=cwd)
    if result.returncode:
        raise ValueError(
            f"{command[0]} exited {result.returncode}: " + (result.stderr or result.stdout).decode(errors="replace")
        )
    return result.stdout


def cache_root() -> Path:
    explicit = os.environ.get("UNBAKE_POLICY")
    base = Path(os.environ.get("XDG_CONFIG_HOME", Path.home() / ".config"))
    path = Path(explicit) if explicit else base / "unbake/policy.toml"
    with path.open("rb") as source:
        data = tomllib.load(source)
    if "cache_root" not in data:
        raise ValueError(f"{path} cache_root: missing value")
    return Path(data["cache_root"]).expanduser()


def read_recipe(path: Path) -> Recipe:
    return cast(Recipe, json.loads(path.read_text()))


@lru_cache(maxsize=64)
def tool_digest(
    paths: tuple[Path, ...],
    kind: str | None = None,
    sn64: bool = False,
    signatures: tuple[tuple[int, int, int, int, int], ...] = (),
) -> str:
    """Fingerprint immutable build tools once per compiler process."""
    return key(*(driver_content(path, kind, sn64) if path.suffix == ".py" else path for path in paths))


def file_signature(path: Path) -> tuple[int, int, int, int, int]:
    """Observe replacement and same-size edits before reusing file contents."""
    stat = path.stat()
    return stat.st_dev, stat.st_ino, stat.st_size, stat.st_mtime_ns, stat.st_ctime_ns


@lru_cache(maxsize=4096)
def dependency_digest(path: Path, signature: tuple[int, int, int, int, int]) -> str:
    """Retain only digests, never the potentially large shared header bytes."""
    return hashlib.sha256(path.read_bytes()).hexdigest()


def dependency_hash(word: str) -> str:
    path = Path(word)
    return dependency_digest(path, file_signature(path))


@lru_cache(maxsize=16)
def manifest_pins(path: Path, signature: tuple[int, int, int, int, int]) -> dict[str, dict[str, str]]:
    """Parse and group immutable compiler pins once, rather than per object."""
    groups: dict[str, dict[str, str]] = {}
    for line in path.read_text().splitlines():
        fields = line.split(maxsplit=1)
        if len(fields) == 2 and not line.startswith("#"):
            name = fields[1].lstrip("*")
            groups.setdefault(str(Path(name).parent), {})[name] = fields[0]
    return groups


def compile_object(args: argparse.Namespace, data: Recipe | None = None) -> None:
    """Stage dependency output even when an external preprocessor writes it."""
    if args.depfile:
        item = argparse.Namespace(**vars(args))
        item.dep_target = args.dep_target or str(args.output.resolve())
        with staging(args.depfile) as temporary:
            item.depfile = temporary
            _compile_object(item, data)
    else:
        _compile_object(args, data)


def _compile_object(args: argparse.Namespace, data: Recipe | None = None) -> None:
    if data is None:
        data = read_recipe(args.recipe)
    prepared = prepare(args, data, run, resolve_tool)
    out = args.output.resolve()
    ident = data["assembly_compiler"] if args.kind == "as" else compiler_for(data, args.unit)
    compiler = data["compilers"][ident] if ident else None
    manifest = args.recipe.parent / "compiler.sha256"
    pins = manifest_pins(manifest, file_signature(manifest)) if manifest.is_file() else {}
    selected = (
        selected_pins(pins, Path(compiler["cc"]), args.recipe.parent, compiler["kind"])
        if compiler is not None and args.kind == "cc"
        else {}
    )
    # Pin only files belonging to the selected compiler, never helper checksums.
    if compiler is not None:
        prepared.inputs.extend(Path(name) for name in sorted(selected) if Path(name) != Path(compiler["cc"]))
    paths = tuple(prepared.inputs)
    signatures = tuple(file_signature(path) for path in paths)
    sn64 = compiler is not None and compiler["kind"] == "sn64"
    digest = key(
        prepared.content,
        prepared.source_name,
        json.dumps([prepared.generation, prepared.assembler_flags], sort_keys=True),
        tool_digest(
            paths,
            args.kind,
            sn64,
            signatures,
        ),
        *prepared.assembler_inputs,
    )
    cache = Cache(args.cache_root or cache_root())
    if cache.get(args.kind, digest) is None:
        # The previous envelope bound all generator branches. It is stricter
        # than the projected kind identity, and still fingerprints today's
        # actual driver logic, binaries and preprocessed closure. Promotion
        # requires an exact content key; no timestamp or historical SHA alias.
        previous = key(
            prepared.content,
            prepared.source_name,
            json.dumps([prepared.generation, prepared.assembler_flags], sort_keys=True),
            tool_digest(paths, None, False, signatures),
            *prepared.assembler_inputs,
        )
        artifact = cache.get(args.kind, previous)
        if artifact is not None:
            cache.put(args.kind, digest, artifact)
    cached = cache.produce(args.kind, digest, prepared.produce)
    if not out.exists() or out.read_bytes() != cached.read_bytes():
        with staging(out) as pending:
            atomic_files.copyfile(cached, pending)
    if args.depfile and (args.kind == "as" or sn64):
        existing = dependency_paths(args.depfile.read_text()) if args.depfile.is_file() else []
        dependencies = list(
            dict.fromkeys([str(args.source), *existing, *assembler_headers(data, args.version, args.kind)])
        )
        atomic_files.text(args.depfile, (args.dep_target or str(out)) + ": " + " ".join(dependencies) + "\n")
    if args.kind == "cc" and args.depfile and args.depfile.is_file():
        words = dependency_paths(args.depfile.read_text())
        dependency_hashes = {str(Path(word)): dependency_hash(word) for word in words}
        write(out.with_suffix(".inputs.json"), json.dumps(dependency_hashes, sort_keys=True).encode())


def compile_batch(args: argparse.Namespace) -> None:
    """Compile a cold graph chunk in one interpreter, sequentially per Make job."""
    data = read_recipe(args.recipe)
    failures = []
    cancel_file = getattr(args, "cancel_file", None)
    for source in args.batch:
        if cancel_file is not None and cancel_file.exists():
            break
        relative = source.relative_to(args.source)
        output = args.output / relative.with_suffix(".o")
        item = argparse.Namespace(**vars(args))
        item.source = source
        item.unit = str(source)
        item.output = output
        if args.kind == "as" and args.symbols.is_dir():
            item.symbols = args.symbols / relative.with_suffix(".txt")
        item.depfile = output.with_suffix(".d")
        item.dep_target = (
            "$(BUILD)/obj/" + ("asm/" if args.kind == "as" else "src/") + str(relative.with_suffix(".built"))
        )
        try:
            compile_object(item, data)
            receipt(output.with_suffix(".built"))
        except (OSError, ValueError, KeyError) as error:
            failures.append(f"{source}: {error}")
            if cancel_file is not None:
                receipt(cancel_file)
                break
    if failures:
        raise ValueError("batch objects failed:\n" + "\n".join(failures))


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--kind", choices=("cc", "as"), required=True)
    for name in ("recipe", "source", "output", "depfile", "symbols", "cache-root"):
        parser.add_argument("--" + name, type=Path, required=name in ("recipe", "source", "output"))
    parser.add_argument("--non-matching", choices=("0", "1"), required=True)
    parser.add_argument("--version", required=True)
    parser.add_argument("--unit", required=True)
    parser.add_argument("--dep-target")
    parser.add_argument("--cancel-file", type=Path)
    parser.add_argument("--batch", type=Path, nargs="+")
    args = parser.parse_args()
    try:
        if args.batch:
            compile_batch(args)
        else:
            compile_object(args)
    except (OSError, ValueError, KeyError) as error:
        parser.exit(1, f"HELD(compile): {error}\n")


if __name__ == "__main__":
    main()
