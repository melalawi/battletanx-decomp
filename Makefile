# BattleTanx (N64) matching decompilation.
#
# This file forwards to the decompilation toolkit, which holds the build graph. The project is
# described by config.toml in this directory and by nothing else: no build logic, no copy of the
# toolkit and no environment variable lives here. Run `decomp --help` for the goals below and for
# the ones this file does not forward.
#
#   make bootstrap  create artifacts/toolchain/ and artifacts/roms/ and say what belongs in each
#   make setup      check the compiler you supplied, the cross binutils, Python and splat
#   make            extract, compile, link and verify the image against the cartridge
#   make check      judge the built tree
#   make test       this project's own controls; it keeps none, so it says so and passes
#   make progress   the share of the cartridge that is authored C
#   make readme     rewrite README.md, the decomp.dev progress reports and their workflow
#   make decomp-yaml  rewrite decomp.yaml from config.toml
#   make versions   list the cartridges this project describes
#   make clean      remove this cartridge's build products; your ROM and toolchain stay
#   make distclean  remove everything under artifacts/ except your ROM and toolchain
#
# VERSION picks a cartridge; left unset, config.toml's reference is used, so the choice stays a
# project fact rather than a default written here.
SHELL := /bin/sh
.DEFAULT_GOAL := build

ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

# The toolkit is installed, not vendored. Refuse by name when it is not on PATH rather than let a
# goal fail somewhere inside make with nothing pointing at the cause.
DECOMP := $(shell command -v decomp 2>/dev/null)
ifeq ($(strip $(DECOMP)),)
$(error HELD(toolkit): `decomp` is not on PATH; install the decompilation toolkit and try again)
endif

# VERSION is passed only when the caller set it, so an unset VERSION reaches the toolkit as absent
# and it reads the reference out of config.toml.
VERSION_ARG := $(if $(strip $(VERSION)),--version $(VERSION),)

GOALS := bootstrap setup build check test progress readme development decomp-yaml versions clean distclean
.PHONY: $(GOALS)

$(GOALS):
	@$(DECOMP) --project $(ROOT) $(VERSION_ARG) $@
