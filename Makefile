# BATTLETANX matching decompilation.
# make setup; make extract; make; make clean; make distclean
# VERSION: us. COMPARE=0 skips comparison.
.DEFAULT_GOAL := all
.SUFFIXES:
.DELETE_ON_ERROR:
.SECONDARY:
VERSIONS := us
COMPARE ?= 1
NON_MATCHING ?= 0
ifeq ($(filter $(NON_MATCHING),0 1),)
$(error HELD(build): NON_MATCHING must be 0 or 1)
endif
ifeq ($(NON_MATCHING),1)
override COMPARE := 0
BUILD ?= build/$(VERSION).nonmatching
else
BUILD ?= build/$(VERSION)
endif
ROM := $(BUILD)/BattleTanx.$(VERSION).z64
ELF := $(BUILD)/BattleTanx.elf
LD_SCRIPT := $(BUILD)/BattleTanx.ld
TOOLS := tools
SRC := src
ASM := asm/$(VERSION)
resolve-tool = $(or $(shell python3 $(TOOLS)/host.py $(1)),$(error HELD(build): missing tool $(1)))
LD = $(call resolve-tool,policy:mips_ld)
OBJCOPY = $(call resolve-tool,policy:mips_objcopy)
SPLAT = $(call resolve-tool,policy:splat)
PINS := tools/compiler.sha256
RECIPE := $(TOOLS)/build.json
LINK_RECIPE := $(TOOLS)/link.json
EXTRACT_RECIPE := $(TOOLS)/extract.json

ifeq ($(strip $(VERSION)),)
ifneq ($(origin BUILD),file)
$(error HELD(build): BUILD requires VERSION)
endif
GOALS := $(filter-out distclean,$(if $(MAKECMDGOALS),$(MAKECMDGOALS),all))
$(foreach goal,$(GOALS),$(eval $(goal): $(addprefix $(goal)-,$(VERSIONS))))
define dispatch
$(1)-$(2):
	+$$(MAKE) VERSION=$(2) $(1)
.PHONY: $(1)-$(2)
endef
$(foreach goal,$(GOALS),$(foreach version,$(VERSIONS),$(eval $(call dispatch,$(goal),$(version)))))

distclean:
	rm -rf -- build asm

.PHONY: $(GOALS) distclean
else
ifeq ($(filter $(VERSION),$(VERSIONS)),)
$(error HELD(build): unknown VERSION=$(VERSION))
endif
ifeq ($(VERSION),us)
SPLIT := versions/us/BattleTanx.yaml
SYMBOLS := versions/us/symbol_addrs.txt
BASEROM := roms/baserom.us.z64
endif

all: $(ROM)
ifeq ($(COMPARE),1)
	@sed 's|  .*|  $(ROM)|' versions/$(VERSION)/BattleTanx.sha1 | sha1sum -c -
endif

verify:
	@sha256sum -c $(PINS) > /dev/null

setup: verify
	sha1sum -c versions/$(VERSION)/baserom.sha1

extract: $(BUILD)/.split

ifeq ($(BUILD),build/$(VERSION))
prepare-build:
	python3 $(TOOLS)/extract.py prepare-build --build $(BUILD)

$(BUILD)/.split.mk: | prepare-build
.PHONY: prepare-build
endif

ifneq ($(filter-out setup clean distclean,$(if $(MAKECMDGOALS),$(MAKECMDGOALS),all)),)
include $(BUILD)/.split.mk
endif

# Partial builds select guarded C rows during extraction. Matching builds use
# the split alone for ownership; editing C only invalidates its object receipt.
ifeq ($(NON_MATCHING),1)
$(BUILD)/.split.mk: $(wildcard $(SRC)/*.c)
endif
$(BUILD)/.split.mk: $(BASEROM) $(SPLIT) $(SYMBOLS) $(TOOLS)/extract.py $(TOOLS)/rodata.py $(EXTRACT_RECIPE)
	@mkdir -p $(BUILD)
	python3 $(TOOLS)/extract.py --split $(SPLIT) --symbols $(SYMBOLS) --baserom $(BASEROM) --build $(BUILD) --asm $(ASM) --src $(SRC) --name BattleTanx --splat $(SPLAT) --recipe $(EXTRACT_RECIPE) --non-matching $(NON_MATCHING)

$(BUILD)/.split: $(BUILD)/.split.mk
	python3 $(TOOLS)/atomic.py --touch $@

$(LD_SCRIPT) $(LINK_SCRIPTS) $(BUILD)/symbol-addresses.txt $(BUILD)/unit-ranges.json: | $(BUILD)/.split
	@test -f $@ || { printf '%s\n' 'HELD(extract): missing $@; remove $(BUILD)/.split.mk and make extract'; exit 1; }

# Executable mtimes and manifest rows are publication metadata. Compare actual
# bytes once before evaluating object prerequisites; unchanged stamps keep mtimes.
ifneq ($(filter-out setup clean distclean,$(if $(MAKECMDGOALS),$(MAKECMDGOALS),all)),)
IDENTITY_STATUS := $(shell python3 $(TOOLS)/compile_identity.py --recipe $(RECIPE) --build $(BUILD) --version $(VERSION) || echo failed)
ifneq ($(strip $(IDENTITY_STATUS)),)
$(error HELD(identity): compiler identity refresh failed)
endif
endif

$(filter-out $(BUILD)/obj/src/func_80119568_us.built $(BUILD)/obj/src/func_8007967C.built $(BUILD)/obj/src/func_80079684.built $(BUILD)/obj/src/func_8007C298.built $(BUILD)/obj/src/func_8007C33C.built $(BUILD)/obj/src/func_800805D0.built $(BUILD)/obj/src/func_80085460.built $(BUILD)/obj/src/func_80085468.built $(BUILD)/obj/src/func_800917C4.built $(BUILD)/obj/src/func_80093F34.built $(BUILD)/obj/src/func_800949B8.built $(BUILD)/obj/src/func_80096784.built $(BUILD)/obj/src/func_80097C24.built $(BUILD)/obj/src/func_8009E39C.built $(BUILD)/obj/src/func_800A424C.built $(BUILD)/obj/src/func_800A42BC.built $(BUILD)/obj/src/func_800A4D1C.built $(BUILD)/obj/src/func_800A66C0.built $(BUILD)/obj/src/func_800A7548.built $(BUILD)/obj/src/func_800A76A0.built $(BUILD)/obj/src/func_800AB200.built $(BUILD)/obj/src/func_800ABFA0.built $(BUILD)/obj/src/func_800E3460.built $(BUILD)/obj/src/func_800E3470.built $(BUILD)/obj/src/func_800E3480.built $(BUILD)/obj/src/func_800E349C.built $(BUILD)/obj/src/func_800E3C18.built $(BUILD)/obj/src/func_800E480C.built $(BUILD)/obj/src/func_800E4814_us.built $(BUILD)/obj/src/func_800E5198.built $(BUILD)/obj/src/func_800E566C.built $(BUILD)/obj/src/func_800E99D4.built $(BUILD)/obj/src/func_800EA1B0.built $(BUILD)/obj/src/func_800EBBB4_us.built $(BUILD)/obj/src/func_80106D00.built $(BUILD)/obj/src/func_80106D08_us.built $(BUILD)/obj/src/func_80107168_us.built $(BUILD)/obj/src/func_80107704_us.built $(BUILD)/obj/src/func_80109354.built $(BUILD)/obj/src/func_8010BC08.built $(BUILD)/obj/src/func_801109B8_us.built $(BUILD)/obj/src/func_80110AAC_us.built $(BUILD)/obj/src/func_80110CA0.built $(BUILD)/obj/src/func_801145D0.built $(BUILD)/obj/src/func_801147A0.built $(BUILD)/obj/src/func_80114828.built $(BUILD)/obj/src/func_80115474.built $(BUILD)/obj/src/func_8011588C.built $(BUILD)/obj/src/func_80115C80.built $(BUILD)/obj/src/func_8011954C.built $(BUILD)/obj/src/func_80119570_us.built $(BUILD)/obj/src/func_80119B60.built $(BUILD)/obj/src/func_80119BB4.built $(BUILD)/obj/src/func_80119C34.built $(BUILD)/obj/src/func_80119CE8_us.built $(BUILD)/obj/src/func_80119F70.built $(BUILD)/obj/src/func_8011A134.built $(BUILD)/obj/src/func_8011AB74_us.built $(BUILD)/obj/src/func_8011B1A0.built $(BUILD)/obj/src/func_8011B2A4.built $(BUILD)/obj/src/func_8011B7BC.built $(BUILD)/obj/src/func_8011B8F0.built $(BUILD)/obj/src/func_8011B9E0.built $(BUILD)/obj/src/func_8011BDE4.built $(BUILD)/obj/src/func_8011C150.built $(BUILD)/obj/src/func_8011C180.built $(BUILD)/obj/src/func_8011C300.built $(BUILD)/obj/src/func_8011C39C_us.built $(BUILD)/obj/src/func_8011C3A4_us.built $(BUILD)/obj/src/func_8011D0E0.built $(BUILD)/obj/src/func_8011D100.built $(BUILD)/obj/src/func_8011D3DC.built $(BUILD)/obj/src/func_8011D6D0.built $(BUILD)/obj/src/func_8011DC00_us.built $(BUILD)/obj/src/func_8011DC60.built $(BUILD)/obj/src/func_8011DC98.built $(BUILD)/obj/src/func_8011DD40_us.built $(BUILD)/obj/src/func_8011E3F0.built $(BUILD)/obj/src/func_8011E434.built $(BUILD)/obj/src/func_8011E488.built $(BUILD)/obj/src/func_8011E564.built $(BUILD)/obj/src/func_8011E6B0_us.built $(BUILD)/obj/src/func_8011ECA4.built $(BUILD)/obj/src/func_8011F7F0.built $(BUILD)/obj/src/func_80121F10.built,$(C_OBJECTS:.o=.built)): tools/compile/drivers/codegen.cc.sn64.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/drivers/sn64_cc.py.sha256 tools/compile/$(VERSION)/gcc-2.7.2-kmc.json tools/compile/binaries/gcc-2.7.2-kmc.sha256 tools/compile/binaries/ca67ca64971528f9b4a433e2ace0f01b92884ba5bd18ccb821572f73453c8568.sha256 tools/compile/drivers/abumasn64.sha256 tools/compile/binaries/b40315d7362b63c3acc0a64baddeec030dc998eaf28729a2df892e3bb7eb143e.sha256
$(BUILD)/obj/src/func_80119568_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8007967C.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80079684.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8007C298.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8007C33C.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800805D0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80085460.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80085468.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800917C4.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80093F34.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800949B8.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80096784.built: tools/compile/drivers/codegen.cc.sn64.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/drivers/sn64_cc.py.sha256 tools/compile/$(VERSION)/gcc-2.8.1-sn64.json tools/compile/binaries/gcc-2.8.1-sn64.sha256 tools/compile/binaries/ca67ca64971528f9b4a433e2ace0f01b92884ba5bd18ccb821572f73453c8568.sha256 tools/compile/drivers/abumasn64.sha256 tools/compile/binaries/b40315d7362b63c3acc0a64baddeec030dc998eaf28729a2df892e3bb7eb143e.sha256
$(BUILD)/obj/src/func_80097C24.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8009E39C.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800A424C.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800A42BC.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800A4D1C.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800A66C0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800A7548.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800A76A0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800AB200.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800ABFA0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800E3460.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800E3470.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800E3480.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800E349C.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800E3C18.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800E480C.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800E4814_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800E5198.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800E566C.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800E99D4.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800EA1B0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_800EBBB4_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80106D00.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80106D08_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80107168_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80107704_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80109354.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8010BC08.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_801109B8_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80110AAC_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80110CA0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_801145D0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_801147A0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80114828.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80115474.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011588C.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80115C80.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011954C.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80119570_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80119B60.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80119BB4.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80119C34.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80119CE8_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80119F70.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011A134.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011AB74_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011B1A0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011B2A4.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011B7BC.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011B8F0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011B9E0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011BDE4.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011C150.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011C180.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011C300.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011C39C_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011C3A4_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011D0E0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011D100.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011D3DC.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011D6D0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011DC00_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011DC60.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011DC98.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011DD40_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011E3F0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011E434.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011E488.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011E564.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011E6B0_us.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-5.3.json tools/compile/binaries/ido-5.3.sha256
$(BUILD)/obj/src/func_8011ECA4.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_8011F7F0.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80121F10.built: tools/compile/drivers/codegen.cc.native.sha256 tools/compile/drivers/elf.py.sha256 tools/compile/$(VERSION)/ido-7.1.json tools/compile/binaries/ido-7.1.sha256
$(BUILD)/obj/src/func_80076038.built: tools/compile/units/func_80076038.json
$(BUILD)/obj/src/func_8007627C.built: tools/compile/units/func_8007627C.json
$(BUILD)/obj/src/func_800767E4_us.built: tools/compile/units/func_800767E4_us.json
$(BUILD)/obj/src/func_80077930.built: tools/compile/units/func_80077930.json
$(BUILD)/obj/src/func_80077A38.built: tools/compile/units/func_80077A38.json
$(BUILD)/obj/src/func_80078D90.built: tools/compile/units/func_80078D90.json
$(BUILD)/obj/src/func_80078F60_us.built: tools/compile/units/func_80078F60_us.json
$(BUILD)/obj/src/func_800793D0.built: tools/compile/units/func_800793D0.json
$(BUILD)/obj/src/func_8007967C.built: tools/compile/units/func_8007967C.json
$(BUILD)/obj/src/func_80079684.built: tools/compile/units/func_80079684.json
$(BUILD)/obj/src/func_800799C0_us.built: tools/compile/units/func_800799C0_us.json
$(BUILD)/obj/src/func_80079A5C.built: tools/compile/units/func_80079A5C.json
$(BUILD)/obj/src/func_80079EFC.built: tools/compile/units/func_80079EFC.json
$(BUILD)/obj/src/func_8007A26C_us.built: tools/compile/units/func_8007A26C_us.json
$(BUILD)/obj/src/func_8007AAA0.built: tools/compile/units/func_8007AAA0.json
$(BUILD)/obj/src/func_8007AAB0.built: tools/compile/units/func_8007AAB0.json
$(BUILD)/obj/src/func_8007AAC0.built: tools/compile/units/func_8007AAC0.json
$(BUILD)/obj/src/func_8007AAE4_us.built: tools/compile/units/func_8007AAE4_us.json
$(BUILD)/obj/src/func_8007AAF4_us.built: tools/compile/units/func_8007AAF4_us.json
$(BUILD)/obj/src/func_8007B1DC_us.built: tools/compile/units/func_8007B1DC_us.json
$(BUILD)/obj/src/func_8007C298.built: tools/compile/units/func_8007C298.json
$(BUILD)/obj/src/func_8007C33C.built: tools/compile/units/func_8007C33C.json
$(BUILD)/obj/src/func_8007C6D8.built: tools/compile/units/func_8007C6D8.json
$(BUILD)/obj/src/func_8007D1F8.built: tools/compile/units/func_8007D1F8.json
$(BUILD)/obj/src/func_8007D384.built: tools/compile/units/func_8007D384.json
$(BUILD)/obj/src/func_8007E140_us.built: tools/compile/units/func_8007E140_us.json
$(BUILD)/obj/src/func_8007EC38.built: tools/compile/units/func_8007EC38.json
$(BUILD)/obj/src/func_8007ECE8.built: tools/compile/units/func_8007ECE8.json
$(BUILD)/obj/src/func_8007ED98.built: tools/compile/units/func_8007ED98.json
$(BUILD)/obj/src/func_8007EE48.built: tools/compile/units/func_8007EE48.json
$(BUILD)/obj/src/func_8007F030_us.built: tools/compile/units/func_8007F030_us.json
$(BUILD)/obj/src/func_8007F060.built: tools/compile/units/func_8007F060.json
$(BUILD)/obj/src/func_8007FF68.built: tools/compile/units/func_8007FF68.json
$(BUILD)/obj/src/func_8008001C_us.built: tools/compile/units/func_8008001C_us.json
$(BUILD)/obj/src/func_800805C0_us.built: tools/compile/units/func_800805C0_us.json
$(BUILD)/obj/src/func_800805D0.built: tools/compile/units/func_800805D0.json
$(BUILD)/obj/src/func_800805DC.built: tools/compile/units/func_800805DC.json
$(BUILD)/obj/src/func_80081A30.built: tools/compile/units/func_80081A30.json
$(BUILD)/obj/src/func_80081A40_us.built: tools/compile/units/func_80081A40_us.json
$(BUILD)/obj/src/func_80081AC0_us.built: tools/compile/units/func_80081AC0_us.json
$(BUILD)/obj/src/func_80085330.built: tools/compile/units/func_80085330.json
$(BUILD)/obj/src/func_80085460.built: tools/compile/units/func_80085460.json
$(BUILD)/obj/src/func_80085468.built: tools/compile/units/func_80085468.json
$(BUILD)/obj/src/func_80090F10.built: tools/compile/units/func_80090F10.json
$(BUILD)/obj/src/func_80091608.built: tools/compile/units/func_80091608.json
$(BUILD)/obj/src/func_800916B8.built: tools/compile/units/func_800916B8.json
$(BUILD)/obj/src/func_800917C4.built: tools/compile/units/func_800917C4.json
$(BUILD)/obj/src/func_800917D8.built: tools/compile/units/func_800917D8.json
$(BUILD)/obj/src/func_80091D04.built: tools/compile/units/func_80091D04.json
$(BUILD)/obj/src/func_80092534_us.built: tools/compile/units/func_80092534_us.json
$(BUILD)/obj/src/func_80093F34.built: tools/compile/units/func_80093F34.json
$(BUILD)/obj/src/func_800949B8.built: tools/compile/units/func_800949B8.json
$(BUILD)/obj/src/func_80096760.built: tools/compile/units/func_80096760.json
$(BUILD)/obj/src/func_80096784.built: tools/compile/units/func_80096784.json
$(BUILD)/obj/src/func_800968FC.built: tools/compile/units/func_800968FC.json
$(BUILD)/obj/src/func_80097B7C.built: tools/compile/units/func_80097B7C.json
$(BUILD)/obj/src/func_80097C24.built: tools/compile/units/func_80097C24.json
$(BUILD)/obj/src/func_80099CD8.built: tools/compile/units/func_80099CD8.json
$(BUILD)/obj/src/func_8009E39C.built: tools/compile/units/func_8009E39C.json
$(BUILD)/obj/src/func_800A2EA4.built: tools/compile/units/func_800A2EA4.json
$(BUILD)/obj/src/func_800A3D30.built: tools/compile/units/func_800A3D30.json
$(BUILD)/obj/src/func_800A424C.built: tools/compile/units/func_800A424C.json
$(BUILD)/obj/src/func_800A4254.built: tools/compile/units/func_800A4254.json
$(BUILD)/obj/src/func_800A42A4.built: tools/compile/units/func_800A42A4.json
$(BUILD)/obj/src/func_800A42B0.built: tools/compile/units/func_800A42B0.json
$(BUILD)/obj/src/func_800A42BC.built: tools/compile/units/func_800A42BC.json
$(BUILD)/obj/src/func_800A42C4_us.built: tools/compile/units/func_800A42C4_us.json
$(BUILD)/obj/src/func_800A4368_us.built: tools/compile/units/func_800A4368_us.json
$(BUILD)/obj/src/func_800A4A64.built: tools/compile/units/func_800A4A64.json
$(BUILD)/obj/src/func_800A4D10_us.built: tools/compile/units/func_800A4D10_us.json
$(BUILD)/obj/src/func_800A4D1C.built: tools/compile/units/func_800A4D1C.json
$(BUILD)/obj/src/func_800A51E8.built: tools/compile/units/func_800A51E8.json
$(BUILD)/obj/src/func_800A52AC.built: tools/compile/units/func_800A52AC.json
$(BUILD)/obj/src/func_800A59E8.built: tools/compile/units/func_800A59E8.json
$(BUILD)/obj/src/func_800A66C0.built: tools/compile/units/func_800A66C0.json
$(BUILD)/obj/src/func_800A6E10.built: tools/compile/units/func_800A6E10.json
$(BUILD)/obj/src/func_800A72C8.built: tools/compile/units/func_800A72C8.json
$(BUILD)/obj/src/func_800A74AC.built: tools/compile/units/func_800A74AC.json
$(BUILD)/obj/src/func_800A7548.built: tools/compile/units/func_800A7548.json
$(BUILD)/obj/src/func_800A7550.built: tools/compile/units/func_800A7550.json
$(BUILD)/obj/src/func_800A76A0.built: tools/compile/units/func_800A76A0.json
$(BUILD)/obj/src/func_800A7D10.built: tools/compile/units/func_800A7D10.json
$(BUILD)/obj/src/func_800A81F0.built: tools/compile/units/func_800A81F0.json
$(BUILD)/obj/src/func_800A979C.built: tools/compile/units/func_800A979C.json
$(BUILD)/obj/src/func_800A9B44.built: tools/compile/units/func_800A9B44.json
$(BUILD)/obj/src/func_800A9B70.built: tools/compile/units/func_800A9B70.json
$(BUILD)/obj/src/func_800AA280.built: tools/compile/units/func_800AA280.json
$(BUILD)/obj/src/func_800AA328.built: tools/compile/units/func_800AA328.json
$(BUILD)/obj/src/func_800AB200.built: tools/compile/units/func_800AB200.json
$(BUILD)/obj/src/func_800AB614.built: tools/compile/units/func_800AB614.json
$(BUILD)/obj/src/func_800AB95C.built: tools/compile/units/func_800AB95C.json
$(BUILD)/obj/src/func_800ABFA0.built: tools/compile/units/func_800ABFA0.json
$(BUILD)/obj/src/func_800ABFD0.built: tools/compile/units/func_800ABFD0.json
$(BUILD)/obj/src/func_800B8750.built: tools/compile/units/func_800B8750.json
$(BUILD)/obj/src/func_800CE4B0.built: tools/compile/units/func_800CE4B0.json
$(BUILD)/obj/src/func_800DD9E8_us.built: tools/compile/units/func_800DD9E8_us.json
$(BUILD)/obj/src/func_800DDA00_us.built: tools/compile/units/func_800DDA00_us.json
$(BUILD)/obj/src/func_800DDCA4.built: tools/compile/units/func_800DDCA4.json
$(BUILD)/obj/src/func_800E0B00.built: tools/compile/units/func_800E0B00.json
$(BUILD)/obj/src/func_800E1A08_us.built: tools/compile/units/func_800E1A08_us.json
$(BUILD)/obj/src/func_800E2614_us.built: tools/compile/units/func_800E2614_us.json
$(BUILD)/obj/src/func_800E2620_us.built: tools/compile/units/func_800E2620_us.json
$(BUILD)/obj/src/func_800E3460.built: tools/compile/units/func_800E3460.json
$(BUILD)/obj/src/func_800E3470.built: tools/compile/units/func_800E3470.json
$(BUILD)/obj/src/func_800E3480.built: tools/compile/units/func_800E3480.json
$(BUILD)/obj/src/func_800E349C.built: tools/compile/units/func_800E349C.json
$(BUILD)/obj/src/func_800E34B4.built: tools/compile/units/func_800E34B4.json
$(BUILD)/obj/src/func_800E3C18.built: tools/compile/units/func_800E3C18.json
$(BUILD)/obj/src/func_800E480C.built: tools/compile/units/func_800E480C.json
$(BUILD)/obj/src/func_800E4814_us.built: tools/compile/units/func_800E4814_us.json
$(BUILD)/obj/src/func_800E4D44.built: tools/compile/units/func_800E4D44.json
$(BUILD)/obj/src/func_800E5198.built: tools/compile/units/func_800E5198.json
$(BUILD)/obj/src/func_800E51B8_us.built: tools/compile/units/func_800E51B8_us.json
$(BUILD)/obj/src/func_800E566C.built: tools/compile/units/func_800E566C.json
$(BUILD)/obj/src/func_800E6A70_us.built: tools/compile/units/func_800E6A70_us.json
$(BUILD)/obj/src/func_800E6C14.built: tools/compile/units/func_800E6C14.json
$(BUILD)/obj/src/func_800E6CA4.built: tools/compile/units/func_800E6CA4.json
$(BUILD)/obj/src/func_800E6FA0_us.built: tools/compile/units/func_800E6FA0_us.json
$(BUILD)/obj/src/func_800E6FA8_us.built: tools/compile/units/func_800E6FA8_us.json
$(BUILD)/obj/src/func_800E7718_us.built: tools/compile/units/func_800E7718_us.json
$(BUILD)/obj/src/func_800E78BC_us.built: tools/compile/units/func_800E78BC_us.json
$(BUILD)/obj/src/func_800E78C8_us.built: tools/compile/units/func_800E78C8_us.json
$(BUILD)/obj/src/func_800E78D4_us.built: tools/compile/units/func_800E78D4_us.json
$(BUILD)/obj/src/func_800E78E0_us.built: tools/compile/units/func_800E78E0_us.json
$(BUILD)/obj/src/func_800E78EC_us.built: tools/compile/units/func_800E78EC_us.json
$(BUILD)/obj/src/func_800E78F8_us.built: tools/compile/units/func_800E78F8_us.json
$(BUILD)/obj/src/func_800E7904_us.built: tools/compile/units/func_800E7904_us.json
$(BUILD)/obj/src/func_800E7910_us.built: tools/compile/units/func_800E7910_us.json
$(BUILD)/obj/src/func_800E791C_us.built: tools/compile/units/func_800E791C_us.json
$(BUILD)/obj/src/func_800E7928_us.built: tools/compile/units/func_800E7928_us.json
$(BUILD)/obj/src/func_800E9894.built: tools/compile/units/func_800E9894.json
$(BUILD)/obj/src/func_800E99D4.built: tools/compile/units/func_800E99D4.json
$(BUILD)/obj/src/func_800E9A20_us.built: tools/compile/units/func_800E9A20_us.json
$(BUILD)/obj/src/func_800E9A28_us.built: tools/compile/units/func_800E9A28_us.json
$(BUILD)/obj/src/func_800E9DA4.built: tools/compile/units/func_800E9DA4.json
$(BUILD)/obj/src/func_800EA1B0.built: tools/compile/units/func_800EA1B0.json
$(BUILD)/obj/src/func_800EA1FC.built: tools/compile/units/func_800EA1FC.json
$(BUILD)/obj/src/func_800EACEC_us.built: tools/compile/units/func_800EACEC_us.json
$(BUILD)/obj/src/func_800EB07C_us.built: tools/compile/units/func_800EB07C_us.json
$(BUILD)/obj/src/func_800EB1E8_us.built: tools/compile/units/func_800EB1E8_us.json
$(BUILD)/obj/src/func_800EB440_us.built: tools/compile/units/func_800EB440_us.json
$(BUILD)/obj/src/func_800EB4A4_us.built: tools/compile/units/func_800EB4A4_us.json
$(BUILD)/obj/src/func_800EB6D4_us.built: tools/compile/units/func_800EB6D4_us.json
$(BUILD)/obj/src/func_800EB71C_us.built: tools/compile/units/func_800EB71C_us.json
$(BUILD)/obj/src/func_800EB764_us.built: tools/compile/units/func_800EB764_us.json
$(BUILD)/obj/src/func_800EB7AC_us.built: tools/compile/units/func_800EB7AC_us.json
$(BUILD)/obj/src/func_800EBBB4_us.built: tools/compile/units/func_800EBBB4_us.json
$(BUILD)/obj/src/func_800EBBBC_us.built: tools/compile/units/func_800EBBBC_us.json
$(BUILD)/obj/src/func_800EBD74_us.built: tools/compile/units/func_800EBD74_us.json
$(BUILD)/obj/src/func_800EBE6C_us.built: tools/compile/units/func_800EBE6C_us.json
$(BUILD)/obj/src/func_800ED810.built: tools/compile/units/func_800ED810.json
$(BUILD)/obj/src/func_800EEBEC.built: tools/compile/units/func_800EEBEC.json
$(BUILD)/obj/src/func_800EECA0.built: tools/compile/units/func_800EECA0.json
$(BUILD)/obj/src/func_800F2120_us.built: tools/compile/units/func_800F2120_us.json
$(BUILD)/obj/src/func_800F3014.built: tools/compile/units/func_800F3014.json
$(BUILD)/obj/src/func_800F5128.built: tools/compile/units/func_800F5128.json
$(BUILD)/obj/src/func_800F5178.built: tools/compile/units/func_800F5178.json
$(BUILD)/obj/src/func_80106D00.built: tools/compile/units/func_80106D00.json
$(BUILD)/obj/src/func_80106D08_us.built: tools/compile/units/func_80106D08_us.json
$(BUILD)/obj/src/func_80106D10_us.built: tools/compile/units/func_80106D10_us.json
$(BUILD)/obj/src/func_80107168_us.built: tools/compile/units/func_80107168_us.json
$(BUILD)/obj/src/func_80107704_us.built: tools/compile/units/func_80107704_us.json
$(BUILD)/obj/src/func_80109354.built: tools/compile/units/func_80109354.json
$(BUILD)/obj/src/func_8010BC08.built: tools/compile/units/func_8010BC08.json
$(BUILD)/obj/src/func_8010DCD0.built: tools/compile/units/func_8010DCD0.json
$(BUILD)/obj/src/func_801109B8_us.built: tools/compile/units/func_801109B8_us.json
$(BUILD)/obj/src/func_80110AAC_us.built: tools/compile/units/func_80110AAC_us.json
$(BUILD)/obj/src/func_80110CA0.built: tools/compile/units/func_80110CA0.json
$(BUILD)/obj/src/func_801145D0.built: tools/compile/units/func_801145D0.json
$(BUILD)/obj/src/func_801147A0.built: tools/compile/units/func_801147A0.json
$(BUILD)/obj/src/func_80114828.built: tools/compile/units/func_80114828.json
$(BUILD)/obj/src/func_80115474.built: tools/compile/units/func_80115474.json
$(BUILD)/obj/src/func_8011588C.built: tools/compile/units/func_8011588C.json
$(BUILD)/obj/src/func_80115C80.built: tools/compile/units/func_80115C80.json
$(BUILD)/obj/src/func_8011954C.built: tools/compile/units/func_8011954C.json
$(BUILD)/obj/src/func_80119568_us.built: tools/compile/units/func_80119568_us.json
$(BUILD)/obj/src/func_80119570_us.built: tools/compile/units/func_80119570_us.json
$(BUILD)/obj/src/func_80119B60.built: tools/compile/units/func_80119B60.json
$(BUILD)/obj/src/func_80119BB4.built: tools/compile/units/func_80119BB4.json
$(BUILD)/obj/src/func_80119C34.built: tools/compile/units/func_80119C34.json
$(BUILD)/obj/src/func_80119CE8_us.built: tools/compile/units/func_80119CE8_us.json
$(BUILD)/obj/src/func_80119F70.built: tools/compile/units/func_80119F70.json
$(BUILD)/obj/src/func_8011A134.built: tools/compile/units/func_8011A134.json
$(BUILD)/obj/src/func_8011AB74_us.built: tools/compile/units/func_8011AB74_us.json
$(BUILD)/obj/src/func_8011B1A0.built: tools/compile/units/func_8011B1A0.json
$(BUILD)/obj/src/func_8011B2A4.built: tools/compile/units/func_8011B2A4.json
$(BUILD)/obj/src/func_8011B7BC.built: tools/compile/units/func_8011B7BC.json
$(BUILD)/obj/src/func_8011B8F0.built: tools/compile/units/func_8011B8F0.json
$(BUILD)/obj/src/func_8011B9E0.built: tools/compile/units/func_8011B9E0.json
$(BUILD)/obj/src/func_8011BDE4.built: tools/compile/units/func_8011BDE4.json
$(BUILD)/obj/src/func_8011C150.built: tools/compile/units/func_8011C150.json
$(BUILD)/obj/src/func_8011C180.built: tools/compile/units/func_8011C180.json
$(BUILD)/obj/src/func_8011C300.built: tools/compile/units/func_8011C300.json
$(BUILD)/obj/src/func_8011C39C_us.built: tools/compile/units/func_8011C39C_us.json
$(BUILD)/obj/src/func_8011C3A4_us.built: tools/compile/units/func_8011C3A4_us.json
$(BUILD)/obj/src/func_8011D0E0.built: tools/compile/units/func_8011D0E0.json
$(BUILD)/obj/src/func_8011D100.built: tools/compile/units/func_8011D100.json
$(BUILD)/obj/src/func_8011D3DC.built: tools/compile/units/func_8011D3DC.json
$(BUILD)/obj/src/func_8011D6D0.built: tools/compile/units/func_8011D6D0.json
$(BUILD)/obj/src/func_8011DC00_us.built: tools/compile/units/func_8011DC00_us.json
$(BUILD)/obj/src/func_8011DC60.built: tools/compile/units/func_8011DC60.json
$(BUILD)/obj/src/func_8011DC98.built: tools/compile/units/func_8011DC98.json
$(BUILD)/obj/src/func_8011DD40_us.built: tools/compile/units/func_8011DD40_us.json
$(BUILD)/obj/src/func_8011E3F0.built: tools/compile/units/func_8011E3F0.json
$(BUILD)/obj/src/func_8011E434.built: tools/compile/units/func_8011E434.json
$(BUILD)/obj/src/func_8011E488.built: tools/compile/units/func_8011E488.json
$(BUILD)/obj/src/func_8011E564.built: tools/compile/units/func_8011E564.json
$(BUILD)/obj/src/func_8011E6B0_us.built: tools/compile/units/func_8011E6B0_us.json
$(BUILD)/obj/src/func_8011ECA4.built: tools/compile/units/func_8011ECA4.json
$(BUILD)/obj/src/func_8011F7F0.built: tools/compile/units/func_8011F7F0.json
$(BUILD)/obj/src/func_80121F10.built: tools/compile/units/func_80121F10.json
$(BUILD)/obj/src/func_80123978_us.built: tools/compile/units/func_80123978_us.json
$(ASM_OBJECTS:.o=.built): tools/compile/drivers/codegen.as.native.sha256 tools/compile/$(VERSION)/assembly.json tools/compile/binaries/ca67ca64971528f9b4a433e2ace0f01b92884ba5bd18ccb821572f73453c8568.sha256

# Group only missing receipts. Existing objects retain their individual rules,
# including header dependency tracking and unchanged-object timestamp behavior.
C_COLD := $(filter-out $(wildcard $(C_OBJECTS:.o=.built)),$(C_OBJECTS:.o=.built))
define compile-chunk
$(1) &: $(patsubst $(BUILD)/obj/src/%.built,$(SRC)/%.c,$(1)) | verify
	python3 $(TOOLS)/compile.py --kind cc --non-matching $(NON_MATCHING) --recipe $(RECIPE) --version $(VERSION) --unit batch --source $(SRC) --output $(BUILD)/obj/src --batch $(patsubst $(BUILD)/obj/src/%.built,$(SRC)/%.c,$(1))
endef
define compile-chunks
$(if $(strip $(1)),$(eval $(call compile-chunk,$(wordlist 1,128,$(1))))$(call compile-chunks,$(wordlist 129,$(words $(1)),$(1))))
endef
$(call compile-chunks,$(C_COLD))

ASM_COLD := $(filter-out $(wildcard $(ASM_OBJECTS:.o=.built)),$(ASM_OBJECTS:.o=.built))
define assemble-chunk
$(1) &: $(patsubst $(BUILD)/obj/asm/%.built,$(ASM)/%.s,$(1)) | verify
	python3 $(TOOLS)/compile.py --kind as --non-matching $(NON_MATCHING) --recipe $(RECIPE) --version $(VERSION) --unit batch --source $(ASM) --output $(BUILD)/obj/asm --symbols $(BUILD)/asm-symbols --batch $(patsubst $(BUILD)/obj/asm/%.built,$(ASM)/%.s,$(1))
endef
define assemble-chunks
$(if $(strip $(1)),$(eval $(call assemble-chunk,$(wordlist 1,128,$(1))))$(call assemble-chunks,$(wordlist 129,$(words $(1)),$(1))))
endef
$(call assemble-chunks,$(ASM_COLD))

$(BUILD)/obj/src/%.built: $(SRC)/%.c | verify
	@mkdir -p $(@D)
	python3 $(TOOLS)/compile.py --kind cc --non-matching $(NON_MATCHING) --recipe $(RECIPE) --version $(VERSION) --unit $(SRC)/$*.c --source $< --output $(@:.built=.o) --depfile $(@:.built=.d) --dep-target='$$(BUILD)/obj/src/$*.built'
	python3 $(TOOLS)/atomic.py --touch $@

$(BUILD)/obj/src/%.o: $(BUILD)/obj/src/%.built
	$(if $(wildcard $@),,$(error HELD(compile): missing $@; remove $(@:.o=.built) and rebuild))

$(BUILD)/obj/asm/%.built: $(ASM)/%.s | verify
	@mkdir -p $(@D)
	python3 $(TOOLS)/compile.py --kind as --non-matching $(NON_MATCHING) --recipe $(RECIPE) --version $(VERSION) --unit $* --source $< --output $(@:.built=.o) --symbols $(BUILD)/asm-symbols/$*.txt --depfile $(@:.built=.d) --dep-target='$$(BUILD)/obj/asm/$*.built'
	python3 $(TOOLS)/atomic.py --touch $@

$(BUILD)/obj/asm/%.o: $(BUILD)/obj/asm/%.built
	$(if $(wildcard $@),,$(error HELD(compile): missing $@; remove $(@:.o=.built) and rebuild))

$(BUILD)/obj/assets/%.bin.o: $(ASM)/assets/%.bin $(OBJCOPY) $(TOOLS)/atomic.py
	@mkdir -p $(@D)
	python3 $(TOOLS)/atomic.py --output $@ -- $(OBJCOPY) -I binary -O elf32-tradbigmips -B mips $< $@

$(ELF): $(SYMBOLS) $(OBJECTS) $(LD_SCRIPT) $(LINK_SCRIPTS) $(TOOLS)/layout.py $(TOOLS)/link_inputs.py $(TOOLS)/rodata.py $(TOOLS)/literal_layout.py $(TOOLS)/pool_slices.py $(TOOLS)/elf.py $(TOOLS)/extract.py $(TOOLS)/atomic.py $(LINK_RECIPE) $(BASEROM) $(BUILD)/unit-ranges.json $(LD)
	@mkdir -p $(@D)
	python3 $(TOOLS)/layout.py --script $(LD_SCRIPT) --output $(BUILD)/BattleTanx.link.ld --build $(BUILD) --ranges $(BUILD)/unit-ranges.json --recipe $(LINK_RECIPE) --version $(VERSION) --baserom $(BASEROM) --non-matching $(NON_MATCHING)
	cd $(BUILD) && LC_ALL=C python3 $(abspath $(TOOLS))/atomic.py --output BattleTanx.elf --output BattleTanx.map -- $(LD) $$(cat BattleTanx.link.flags) -T BattleTanx.link.ld $(addprefix -T ,$(abspath $(LINK_SCRIPTS))) -Map BattleTanx.map -o BattleTanx.elf $(patsubst $(BUILD)/%,%,$(OBJECTS))

$(ROM): $(ELF) $(OBJCOPY) $(TOOLS)/atomic.py
	python3 $(TOOLS)/atomic.py --output $@ -- $(OBJCOPY) -O binary --pad-to $(ROM_BYTES) $< $@

clean:
	@test -n '$(BUILD)' && test '$(BUILD)' != / && test '$(BUILD)' != .
	rm -rf -- '$(BUILD)'

distclean: clean
	rm -rf -- asm/$(VERSION)

ifneq ($(filter-out setup clean distclean,$(if $(MAKECMDGOALS),$(MAKECMDGOALS),all)),)
-include $(DEPFILES)
endif
check: $(ROM)
ifeq ($(NON_MATCHING),1)
	@printf '%s\n' 'HELD(check): NON_MATCHING=1 cannot verify a matching cartridge'; exit 1
else
	@sed 's|  .*|  $(ROM)|' versions/$(VERSION)/BattleTanx.sha1 | sha1sum -c -
endif

.PHONY: all check verify setup extract clean distclean

endif
