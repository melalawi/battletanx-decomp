"""Byte-producing compile logic, independent of cache and publication services."""

from __future__ import annotations

import argparse
import re
import shutil
import tempfile
from collections.abc import Callable
from dataclasses import dataclass
from pathlib import Path
from typing import TypedDict

from compile_identity import driver_names

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


def compiler_for(data: Recipe, unit: str) -> str:
    ident = data["units"].get(Path(unit).stem, data["default_compiler"])
    if ident not in data["compilers"]:
        raise ValueError(f"[units].{unit}: unknown compiler {ident}")
    return ident


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


@dataclass
class Prepared:
    content: bytes
    source_name: str
    generation: list[str]
    assembler_flags: list[str]
    assembler_inputs: list[str | bytes]
    inputs: list[Path]
    produce: Callable[[Path], None]


def prepare(
    args: argparse.Namespace,
    data: Recipe,
    execute: Callable[..., bytes],
    resolve_tool: Callable[[str], str],
) -> Prepared:
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
                content = execute([data["cpp"], *cppflags, *preprocess, *dependencies, temporary.name])
                if args.depfile:
                    text = args.depfile.read_text().replace(temporary.name, str(args.source))
                    args.depfile.write_text(text)
        else:
            content = execute(
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
            text = execute([cc, *preprocess_flags, "-M", str(args.source)]).decode()
        else:
            text = ""
        combined = ["-MD", "-MF", str(args.depfile)] if args.depfile and not ido else []
        content = execute([cc, *preprocess_flags, "-E", *combined, str(args.source)])
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

    inputs = [args.recipe.parent / name for name in driver_names(args.kind, sn64)]
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
    assembler_flags, assembler_inputs = assembly_inputs(asflags) if assembly or sn64 else ([], [])
    if compiler is not None:
        if not assembly:
            inputs.append(Path(compiler["cc"]))
        if sn64:
            compiler["as"] = resolve_tool(compiler["as"])
            inputs.append(Path(compiler["as"]))
    source_name = Path(args.unit).stem + (".s" if assembly else ".i")

    def produce(destination: Path) -> None:
        with tempfile.TemporaryDirectory(prefix=".object-", dir=out.parent) as temporary:
            work = Path(temporary)
            # Only a stable unit-relative spelling reaches cc1/as and STT_FILE.
            # The working directory stays randomly isolated for concurrent jobs.
            source = work / source_name
            source.write_bytes(content)
            if sn64:
                assert compiler is not None
                from abumasn64.assemble import assemble

                from sn64_cc import gnu_as_flags

                if not assembly:
                    generated = work / "source.s"
                    execute(
                        [str(Path(compiler["cc"]).resolve()), "-quiet", *codeflags, source.name, "-o", str(generated)],
                        cwd=work,
                    )
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
                # Include roots were interpreted relative to the project before chdir.
                absolute_flags = []
                include_next = False
                for flag in asflags:
                    if include_next:
                        absolute_flags.append(str(Path(flag).resolve()))
                        include_next = False
                    elif flag == "-I":
                        absolute_flags.append(flag)
                        include_next = True
                    elif flag.startswith("-I"):
                        absolute_flags.append("-I" + str(Path(flag[2:]).resolve()))
                    else:
                        absolute_flags.append(flag)
                command = [data["as"], *absolute_flags]
                if args.depfile:
                    command.extend(["--MD", str(args.depfile)])
                execute([*command, "-o", str(destination), source.name], cwd=work)
                if args.depfile:
                    text = args.depfile.read_text()
                    args.depfile.write_text(
                        (args.dep_target or str(out))
                        + ":"
                        + " "
                        + " ".join(
                            str(args.source) if word in {str(source), source.name} else word
                            for word in dependency_paths(text)
                        )
                        + "\n"
                    )
            else:
                assert compiler is not None
                execute(
                    [str(Path(compiler["cc"]).resolve()), *generation, "-c", source.name, "-o", str(destination)],
                    cwd=work,
                )
                from elf import Object

                Object(destination).trim_text()

    return Prepared(content, source_name, generation, assembler_flags, assembler_inputs, inputs, produce)
