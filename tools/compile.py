#!/usr/bin/env python3
"""Compile or assemble a content-keyed object with the declared project recipe."""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import shutil
import subprocess
import tempfile
import tomllib
from functools import lru_cache
from pathlib import Path
from typing import TypedDict, cast

from cache import Cache, key
from compile_identity import LEGACY_DRIVER, OPTIMIZED_SHA256
from host import resolve_tool

Compiler = TypedDict("Compiler", {"kind": str, "cc": str, "cflags": list[str], "as": str})


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
    ident = data["units"].get(Path(unit).stem, data["default_compiler"])
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


def read_recipe(path: Path) -> Recipe:
    return cast(Recipe, json.loads(path.read_text()))


@lru_cache(maxsize=64)
def tool_digest(paths: tuple[Path, ...]) -> str:
    """Fingerprint immutable build tools once per compiler process."""
    driver = paths[0].read_bytes()
    # This reviewed optimization preserves the old cache envelope. Any later
    # driver edit falls back to fingerprinting its actual bytes.
    if hashlib.sha256(driver).hexdigest() == OPTIMIZED_SHA256:
        return key(LEGACY_DRIVER.encode(), *paths[1:])
    return key(*paths)


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


def codegen_flags(flags: list[str]) -> list[str]:
    """Remove preprocessing options from a compiler invocation on a .i file."""
    result = []
    previous = False
    for flag in flags:
        if previous:
            previous = False
        elif flag in {"-I", "-D", "-U", "-include", "-imacros", "-isystem", "-iquote"}:
            previous = True
        elif not flag.startswith(("-I", "-D", "-U")) and flag != "-c":
            result.append(flag)
    if previous:
        raise ValueError("preprocessor option missing its value")
    return result


def assembly_inputs(asflags: list[str]) -> tuple[list[str], list[str | bytes]]:
    """Identify assembler include contents, independently of directory spelling."""
    flags: list[str] = []
    inputs: list[str | bytes] = []
    previous = False
    for flag in asflags:
        if previous or flag.startswith("-I"):
            if flag == "-I" and not previous:
                previous = True
                continue
            root = Path(flag if previous else flag[2:])
            previous = False
            files = sorted(path for path in root.rglob("*") if path.is_file())
            inputs.append("include-directory")
            for path in files:
                inputs.extend((str(path.relative_to(root)), path.read_bytes()))
        else:
            flags.append(flag)
    if previous:
        raise ValueError("assembler include option missing its value")
    return flags, inputs


def dependency_paths(text: str) -> list[str]:
    """Combine compiler dependency rules, including IDO's separate header rule."""
    return list(
        dict.fromkeys(
            word
            for line in text.replace("\\\n", " ").splitlines()
            if ":" in line
            for word in line.split(":", 1)[1].split()
        )
    )


def preprocessed_dependencies(content: bytes, source: Path) -> list[str]:
    """IDO's -E line markers name the same inputs as its separate -M rules."""
    names = re.findall(rb'^#[ \t]*(?:line[ \t]+)?[0-9]+[ \t]+"([^"\n]+)"', content, re.M)
    return list(dict.fromkeys([str(source), *(name.decode() for name in names if not name.startswith(b"<"))]))


def compile_object(args: argparse.Namespace, data: Recipe | None = None) -> None:
    if data is None:
        data = read_recipe(args.recipe)
    out = args.output.resolve()
    out.parent.mkdir(parents=True, exist_ok=True)
    version = args.version
    if version not in data["macros"]:
        raise ValueError(f"version.{version}: unknown VERSION")
    assembly = args.kind == "as"
    ident = data["assembly_compiler"] if assembly else compiler_for(data, args.unit)
    compiler = data["compilers"][ident] if ident else None
    sn64 = compiler is not None and compiler["kind"] == "sn64"
    if sn64:
        data["cpp"] = resolve_tool(data["cpp"])
    elif assembly:
        data["as"] = resolve_tool(data["as"])
    asflags = [
        *(data["sn64_asflags"] if sn64 and not assembly else data["asflags"]),
        "-I" + str(Path(data["asm"]) / version / "include"),
    ]
    flags: list[str] = []
    if not assembly:
        assert compiler is not None
        flags = [
            *("-I" + p for p in data["include"]),
            *compiler["cflags"],
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
            content = run(
                [
                    data["cpp"],
                    *("-I" + p for p in data["include"]),
                    *cppflags,
                    *preprocess,
                    *dependencies,
                    str(args.source),
                ]
            )
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
        preprocess_flags = [f for f in flags if f != "-c"]
        ido = compiler["kind"] == "ido"
        # IDO's recompiled driver rejects -MD/-MF; -MDupdate calls an
        # unimplemented fcntl. Its ordinary -E markers already list inputs.
        # Retain -M only when the recipe explicitly suppresses those markers.
        separate_dependencies = ido and "-P" in preprocess_flags
        if args.depfile and separate_dependencies:
            text = run([cc, *preprocess_flags, "-M", str(args.source)]).decode()
        else:
            text = ""
        combined = ["-MD", "-MF", str(args.depfile)] if args.depfile and not ido else []
        content = run([cc, *preprocess_flags, "-E", *combined, str(args.source)])
        if args.depfile:
            words = (
                dependency_paths(text)
                if separate_dependencies
                else preprocessed_dependencies(content, args.source)
                if ido
                else dependency_paths(args.depfile.read_text())
            )
            target = args.dep_target or str(out)
            args.depfile.write_text(target + ": " + " ".join(words) + "\n")

    manifest = args.recipe.parent / "compiler.sha256"
    pins = manifest_pins(manifest, file_signature(manifest)) if manifest.is_file() else {}
    selected = pins.get(str(Path(compiler["cc"]).parent), {}) if ident and compiler is not None else {}
    driver_names = (
        (
            "compile.py",
            "elf.py",
            "sn64_cc.py",
            "resolve_external_branches.py",
        )
        if sn64
        else ("compile.py", "elf.py")
    )
    inputs = [args.recipe.parent / name for name in driver_names]
    if sn64:
        import abumasn64

        assert abumasn64.__file__ is not None
        inputs.extend(sorted(Path(abumasn64.__file__).parent.glob("*.py")))
    if assembly and not sn64:
        inputs.extend(p for p in includes if p.is_file())
        assembler = shutil.which(data["as"]) if "/" not in data["as"] else data["as"]
        if not assembler:
            raise ValueError(f"[build].as: missing executable {data['as']}")
        inputs.append(Path(assembler))
    # A .i input is already preprocessed. Macro definitions, CPP options and
    # include directory names cannot affect code generation at this point.
    generation = codeflags if sn64 else codegen_flags(flags)
    assembler_flags, assembler_inputs = assembly_inputs(asflags)
    if compiler is not None:
        inputs.append(Path(compiler["cc"]))
        if sn64:
            compiler["as"] = resolve_tool(compiler["as"])
            inputs.append(Path(compiler["as"]))
    digest = key(
        content,
        json.dumps([selected, generation, assembler_flags], sort_keys=True),
        tool_digest(tuple(inputs)),
        *assembler_inputs,
    )

    def produce(destination: Path) -> None:
        with tempfile.TemporaryDirectory(prefix=".object-", dir=out.parent) as temporary:
            work = Path(temporary)
            source = work / ("source.s" if assembly else "source.i")
            source.write_bytes(content)
            if sn64:
                assert compiler is not None
                from abumasn64.assemble import assemble

                from sn64_cc import gnu_as_flags

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
                    gnu_as_flags(asflags),
                    asn64_version="2.81",
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
                run([compiler["cc"], *generation, "-c", str(source), "-o", str(destination)])
                from elf import Object

                Object(destination).trim_text()

    cached = Cache(args.cache_root or cache_root()).produce(args.kind, digest, produce)
    if not out.exists() or out.read_bytes() != cached.read_bytes():
        temporary = out.with_name(out.name + ".partial")
        shutil.copyfile(cached, temporary)
        temporary.replace(out)
    if assembly and args.depfile and not args.depfile.exists():
        args.depfile.write_text((args.dep_target or str(out)) + ": " + str(args.source) + "\n")

    if args.kind == "cc" and args.depfile and args.depfile.is_file():
        words = dependency_paths(args.depfile.read_text())
        dependency_hashes = {str(Path(word)): dependency_hash(word) for word in words}
        out.with_suffix(".inputs.json").write_text(json.dumps(dependency_hashes, sort_keys=True))


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
        item.depfile = output.with_suffix(".d")
        item.dep_target = (
            "$(BUILD)/obj/" + ("asm/" if args.kind == "as" else "src/") + str(relative.with_suffix(".built"))
        )
        try:
            compile_object(item, data)
            output.with_suffix(".built").touch()
        except (OSError, ValueError, KeyError) as error:
            failures.append(f"{source}: {error}")
            if cancel_file is not None:
                cancel_file.touch()
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
