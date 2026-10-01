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
BASEROM := baserom.$(VERSION).z64
ROM := $(BUILD)/battletanx.$(VERSION).z64
ELF := $(BUILD)/battletanx.elf
LD_SCRIPT := $(BUILD)/battletanx.ld
TOOLS := tools
SRC := src
ASM := asm/$(VERSION)
resolve-tool = $(or $(shell python3 $(TOOLS)/host.py $(1)),$(error HELD(build): missing tool $(1)))
LD = $(call resolve-tool,policy:mips_ld)
OBJCOPY = $(call resolve-tool,policy:mips_objcopy)
SPLAT = $(call resolve-tool,policy:splat)
PINS := tools/compiler.sha256
RECIPE := $(TOOLS)/build.json
DRIVERS := $(TOOLS)/compile.py $(TOOLS)/cache.py $(TOOLS)/elf.py $(TOOLS)/host.py $(TOOLS)/sn64_cc.py $(TOOLS)/asn64.py $(TOOLS)/resolve_external_branches.py
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
SPLIT := versions/us/battletanx.yaml
SYMBOLS := versions/us/symbol_addrs.txt
endif

all: $(ROM)
ifeq ($(COMPARE),1)
	@sed 's|  .*|  $(ROM)|' versions/$(VERSION)/battletanx.sha1 | sha1sum -c -
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

$(BUILD)/.split.mk: $(wildcard $(SRC)/*.c) $(BASEROM) $(SPLIT) $(SYMBOLS) $(TOOLS)/extract.py $(RECIPE)
	@mkdir -p $(BUILD)
	python3 $(TOOLS)/extract.py --split $(SPLIT) --symbols $(SYMBOLS) --baserom $(BASEROM) --build $(BUILD) --asm $(ASM) --src $(SRC) --name battletanx --splat $(SPLAT) --recipe $(RECIPE) --non-matching $(NON_MATCHING)

$(BUILD)/.split: $(BUILD)/.split.mk
	@touch $@

$(LD_SCRIPT) $(LINK_SCRIPTS) $(BUILD)/symbol-addresses.txt: | $(BUILD)/.split
	@test -f $@ || { printf '%s\n' 'HELD(extract): missing $@; remove $(BUILD)/.split.mk and make extract'; exit 1; }

# Group only missing receipts. Existing objects retain their individual rules,
# including header dependency tracking and unchanged-object timestamp behavior.
C_COLD := $(filter-out $(wildcard $(C_OBJECTS:.o=.built)),$(C_OBJECTS:.o=.built))
define compile-chunk
$(1) &: $(patsubst $(BUILD)/obj/src/%.built,$(SRC)/%.c,$(1)) $(RECIPE) $(DRIVERS) | verify
	python3 $(TOOLS)/compile.py --kind cc --non-matching $(NON_MATCHING) --recipe $(RECIPE) --version $(VERSION) --unit batch --source $(SRC) --output $(BUILD)/obj/src --batch $(patsubst $(BUILD)/obj/src/%.built,$(SRC)/%.c,$(1))
endef
define compile-chunks
$(if $(strip $(1)),$(eval $(call compile-chunk,$(wordlist 1,128,$(1))))$(call compile-chunks,$(wordlist 129,$(words $(1)),$(1))))
endef
$(call compile-chunks,$(C_COLD))

$(BUILD)/obj/src/%.built: $(SRC)/%.c $(RECIPE) $(DRIVERS) | verify
	@mkdir -p $(@D)
	python3 $(TOOLS)/compile.py --kind cc --non-matching $(NON_MATCHING) --recipe $(RECIPE) --version $(VERSION) --unit $(SRC)/$*.c --source $< --output $(@:.built=.o) --depfile $(@:.built=.d) --dep-target='$$(BUILD)/obj/src/$*.built'
	@touch $@

$(BUILD)/obj/src/%.o: $(BUILD)/obj/src/%.built
	@test -f $@

$(BUILD)/obj/asm/%.built: $(ASM)/%.s $(RECIPE) $(DRIVERS) $(BUILD)/symbol-addresses.txt | verify
	@mkdir -p $(@D)
	python3 $(TOOLS)/compile.py --kind as --non-matching $(NON_MATCHING) --recipe $(RECIPE) --version $(VERSION) --unit $* --source $< --output $(@:.built=.o) --symbols $(BUILD)/symbol-addresses.txt --depfile $(@:.built=.d) --dep-target='$$(BUILD)/obj/asm/$*.built'
	@touch $@

$(BUILD)/obj/asm/%.o: $(BUILD)/obj/asm/%.built
	@test -f $@

$(BUILD)/obj/assets/%.bin.o: $(ASM)/assets/%.bin
	@mkdir -p $(@D)
	$(OBJCOPY) -I binary -O elf32-tradbigmips -B mips $< $@

$(ELF): $(OBJECTS) $(LD_SCRIPT) $(LINK_SCRIPTS) $(TOOLS)/layout.py $(TOOLS)/rodata.py
	@mkdir -p $(@D)
	python3 $(TOOLS)/layout.py --script $(LD_SCRIPT) --output $(BUILD)/battletanx.link.ld --build $(BUILD) --ranges $(BUILD)/unit-ranges.json --recipe $(RECIPE) --version $(VERSION) --baserom $(BASEROM) --non-matching $(NON_MATCHING)
	cd $(BUILD) && LC_ALL=C $(LD) $$(cat battletanx.link.flags) -T battletanx.link.ld $(addprefix -T ,$(abspath $(LINK_SCRIPTS))) -Map battletanx.map -o battletanx.elf $(patsubst $(BUILD)/%,%,$(OBJECTS))

$(ROM): $(ELF)
	$(OBJCOPY) -O binary --pad-to $(ROM_BYTES) $< $@

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
	@sed 's|  .*|  $(ROM)|' versions/$(VERSION)/battletanx.sha1 | sha1sum -c -
endif

.PHONY: all check verify setup extract clean distclean

endif
