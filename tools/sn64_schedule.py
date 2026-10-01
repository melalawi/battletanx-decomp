"""Normalize SN64 instruction scheduling and macros for GNU MIPS assembly."""

from __future__ import annotations

from sn64_macros import HEADER, division, floating, memory

BRANCHES: set[str] = {
    "bc1f",
    "bc1fl",
    "bc1t",
    "bc1tl",
    "beq",
    "beql",
    "bgez",
    "bgezal",
    "bgezall",
    "bgezl",
    "bgtz",
    "bgtzl",
    "blez",
    "blezl",
    "bltz",
    "bltzal",
    "bltzall",
    "bltzl",
    "bne",
    "bnel",
    "j",
    "jal",
    "jalr",
    "jr",
    "blt",
    "ble",
    "bgt",
    "bge",
}
COP1_BRANCHES: set[str] = {"bc1f", "bc1fl", "bc1t", "bc1tl"}
COMPARES: set[str] = {"c.lt.s", "c.le.s", "c.eq.s", "c.lt.d", "c.le.d", "c.eq.d"}
LOAD_STORES: set[str] = {
    "lb",
    "lbu",
    "lh",
    "lhu",
    "lw",
    "lwu",
    "ld",
    "sb",
    "sh",
    "sw",
    "sd",
    "lwc1",
    "swc1",
    "ldc1",
    "sdc1",
    "l.s",
    "l.d",
    "s.s",
    "s.d",
}


def tokens_for(line: str) -> list[str]:
    stripped: str = line.strip().split("#")[0].strip()
    return [s.strip() for s in stripped.split()]


def schedule(text: str) -> str:
    input_lines = text.splitlines(keepends=True)
    preprocessed: list[str] = [HEADER]
    line: str
    is_reorder: bool = True
    generated_symbol_count: int = 0
    mfhilo_delay_count: int = 0
    mfhilo_delay_location: int = 0
    prev_mul: bool = False
    comm_symbols: list[tuple[str, str]] = []
    lcomm_symbols: list[tuple[str, str]] = []
    delay_slot: bool = False
    file_count: int = 0
    prev_instruction_index: int = 0
    last_file_directive: int = -1
    local_symbols: set[str] = set()
    for line_index, line in enumerate(input_lines):
        tokens: list[str] = tokens_for(line)
        if line[1:5] == "#nop":
            prev_instruction_tokens: list[str] = tokens_for(input_lines[prev_instruction_index])
            if prev_instruction_tokens and prev_instruction_tokens[0] in COMPARES:
                line = "\tnop\n"
        if len(tokens) == 0:
            preprocessed.append(line)
            continue
        identifier: str = tokens[0]
        operands: list[str]
        new_prev_mul: bool = False
        is_branch: bool = False
        if identifier[0] == ".":
            directive: str = identifier[1:]
            if directive == "set":
                setting: str = tokens[1]
                if setting == "noreorder":
                    is_reorder = False
                    continue
                elif setting == "reorder":
                    is_reorder = True
                    continue
            elif directive == "local":
                local_symbols.add(tokens[1])
            elif directive == "comm":
                comm_symbol: str
                comm_size: str
                comm_symbol, comm_size = [s.strip() for s in tokens[1].split(",")][:2]
                if comm_symbol in local_symbols:
                    lcomm_symbols.append((comm_symbol, comm_size))
                else:
                    comm_symbols.append((comm_symbol, comm_size))
                line = ""
            elif directive == "lcomm":
                lcomm_symbol: str
                lcomm_size: str
                lcomm_symbol, lcomm_size = [s.strip() for s in tokens[1].split(",")]
                lcomm_symbols.append((lcomm_symbol, lcomm_size))
                line = ""
            elif directive == "file":
                file_count += 1
                line = f"\t.file\t{file_count + 1} {tokens[2]}\n"
                last_file_directive = len(preprocessed)
            elif directive in ["def", "begin", "bend"]:
                line = ""
            elif directive == "word":
                if tokens[1][0] == "$":
                    line = f"\t.word\t.{tokens[1][1:]}\n"
        elif identifier[-1] == ":":
            pass
        else:
            if identifier in BRANCHES:
                is_branch = True
                if identifier in COP1_BRANCHES:
                    previous = next(
                        (
                            item.strip()
                            for item in reversed("".join(preprocessed).splitlines())
                            if item.strip()
                            and (not item.strip().startswith(("#", ".")))
                            and (not item.strip().endswith(":"))
                        ),
                        "",
                    )
                    if previous.split() and previous.split()[0] in COMPARES:
                        preprocessed.append("\tnop\n")
                if is_reorder:
                    line += "\tnop\n"
            elif identifier in LOAD_STORES and len(tokens) >= 2 and ("," in tokens[1]):
                operands = [s.strip() for s in tokens[1].split(",", 1)]
                line = memory(identifier, tokens[1], line)
            elif identifier == "li":
                operands = tokens[1].split(",")
                value = int(operands[1], 0)
                if -32768 <= value <= 32767:
                    line = f"\taddiu {operands[0]},$0,{value}\n"
            elif identifier in ("li.s", "li.d"):
                operands = [part.strip() for part in tokens[1].split(",")]
                if operands[0].startswith("$f"):
                    line = floating(identifier, operands, generated_symbol_count)
                    generated_symbol_count += 1
            elif identifier in ("div", "divu", "rem", "remu"):
                while mfhilo_delay_count > 0:
                    preprocessed.append("\tnop\n")
                    mfhilo_delay_count -= 1
                operands = [part.strip() for part in tokens[1].split(",")]
                if operands[0] != "$0":
                    line = division(identifier, operands, generated_symbol_count)
                    generated_symbol_count += 1 if identifier in ("divu", "remu") else 2
                    mfhilo_delay_count = 3
                    mfhilo_delay_location = len(preprocessed) + 1
            elif identifier in ["mflo", "mfhi"]:
                mfhilo_delay_count = 3
                mfhilo_delay_location = len(preprocessed) + 1
            elif identifier == "mult":
                if delay_slot and (not is_reorder) and (mfhilo_delay_count <= 0):
                    preprocessed.insert(len(preprocessed) - 1, line)
                    line = "\tnop\n"
                while mfhilo_delay_count > 0:
                    if delay_slot:
                        preprocessed.insert(mfhilo_delay_location, "\tnop\n")
                    else:
                        preprocessed.append("\tnop\n")
                    mfhilo_delay_count -= 1
                if prev_mul:
                    line = "\tnop\n" + line
                new_prev_mul = True
            elif identifier in ["mul.s", "mul.d"]:
                if delay_slot and (not is_reorder) and (mfhilo_delay_count <= 0):
                    preprocessed.insert(len(preprocessed) - 1, line)
                    line = "\tnop\n"
                if prev_mul:
                    line = "\tnop\n" + line
                new_prev_mul = True
            if mfhilo_delay_count > 0:
                mfhilo_delay_count -= 1
            prev_mul = new_prev_mul
            delay_slot = is_branch
            prev_instruction_index = line_index
        preprocessed.append(line)
    if len(comm_symbols) > 0 or len(lcomm_symbols) > 0:
        preprocessed.append("\t.section\t.bss\n")
    for symbol, size in lcomm_symbols:
        if int(size) > 4:
            preprocessed.append("\t.align 3\n")
        preprocessed.append(f"\t.globl {symbol}\n{symbol}:\n\t.space {size}\n")
    for symbol, size in comm_symbols:
        if int(size) > 4:
            preprocessed.append("\t.align 3\n")
        preprocessed.append(f"\t.globl {symbol}\n{symbol}:\n\t.space {size}\n")
    if last_file_directive != -1:
        file_directive_tokens: list[str] = tokens_for(preprocessed[last_file_directive])
        line_directive: str = f"\t.file\t1 {file_directive_tokens[2]}\n"
        preprocessed[last_file_directive] = ""
        preprocessed.insert(0, line_directive)
    return "".join(preprocessed)
