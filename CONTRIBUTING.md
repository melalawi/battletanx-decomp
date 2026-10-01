# Contributing to BATTLETANX

Install Python 3, splat, GNU Make, SHA checksum utilities, and the MIPS binutils
named in the Makefile. Supply the compiler files under `tools` and verify them
against `tools/compiler.sha256`.

Place your own big-endian cartridge dump at `baserom.<version>.z64` in this
repository. Supported versions: us.

Plain `make` and `make check` build and verify every VERSION. Pass
`VERSION=<version>` to build just one.

- `make setup VERSION=<version>` verifies your dump and compiler.
- `make extract VERSION=<version>` splits the dump once.
- `make VERSION=<version>` builds and checks the cartridge SHA-1.
- `make check VERSION=<version>` checks the rebuilt cartridge SHA-1.
- `make clean VERSION=<version>` removes that version's build.
- `make distclean` removes every build and the extracted assembly.

`BUILD=<directory>` selects a separate output directory. `COMPARE=0` skips
comparison; use the default `COMPARE=1` to prove a match. Each function has its
own C or assembly object, selected by that version's split file.

Unmatched drafts live in `src/` under `#ifdef NON_MATCHING`. Run
`make NON_MATCHING=1` to build those drafts with comparison disabled.
