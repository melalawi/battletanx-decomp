# What produced this cartridge

Everything below is a count taken from the image. `docs/evidence/toolchain-evidence.json` holds
the counts, and every number here was taken from that file; the survey that produced it is
`matchkit.provenance`, run over the cartridge against the text intervals the split names. The image is 8388608 bytes, SHA-256 `c5b7cf3523de025e3f18e2c8df2deb0eced5613e7c46cb8c6c5a4f22644ead3f`.

The survey reports a partition of the address space rather than one verdict, because a
cartridge may link objects built by more than one toolchain. Anything it could not
identify is named here as unidentified rather than left out.

## The partition

| region | kind | ROM start | ROM end | bytes | surveyed |
| --- | --- | --- | --- | --- | --- |
| header | header | 0x000000 | 0x000040 | 64 | no |
| bootcode | bin | 0x000040 | 0x001000 | 4032 | no |
| entry | text | 0x001000 | 0x001038 | 56 | yes |
| data | data | 0x001038 | 0x006000 | 20424 | no |
| text | text | 0x006000 | 0x0B5550 | 718160 | yes |
| rodata | rodata | 0x0B5550 | 0x0D7040 | 137968 | no |
| bss | bss | 0x0D7040 | 0x0D7040 | 0 | no |
| assets | bin | 0x0D7040 | 0x800000 | 7507904 | no |

A discriminator counts instructions, so only the regions the split calls code are
surveyed: 2 of 8, 718216 bytes of the 8388608-byte image. The other 6 regions carry no
instructions and no toolchain evidence about them exists in this record.

## What the counts leave standing

Narrowing is by exclusion alone: every label starts standing and falls when an observed
count rules it out. A count merely consistent with a label never promotes it.

| axis | standing after the survey | ruled out |
| --- | --- | --- |
| b-encoding | b-always-beq, b-mixed | b-always-bgez |
| call-delay-slot | call-slot-mixed | call-slot-always-filled, call-slot-never-filled |
| division-check | division-always-checked, division-mixed | division-never-checked |
| fp-calling-convention |  | nothing |
| fp-double-transfer |  | nothing |
| fp-register-file | fp-register-file-64-bit | fp-register-file-32-bit-pairs |
| return-delay-slot | return-slot-mixed | return-slot-always-empty, return-slot-always-filled |
| small-data | no-small-data | small-data-in-use |

`move-encoding` is absent from the table above because its 6635 sites reach no exclusion: both
encodings are present, and the axis carries no label that a mixture rules out. The mixture is still
the most informative thing in this record, but what makes it so is where the two encodings sit, which
is a separate measurement over the intervals rather than a narrowing of an axis. Counted over the
1,276 intervals of the current split with this record's own anchor — `addu`, `or` or `daddu` writing a
non-zero register from one zero source — 667 encode every register-to-register copy as
`addu $d, $s, $zero`, 143 encode every one as `or $d, $s, $zero`, 465 make no such copy, and one
mixes them. The `or`-encoded intervals fall in one span, 0x80110490..0x80124350, and **no
`addu`-encoded interval sits inside it**. The single mixed interval, `func_8010DED4`, is 9,644 bytes
and straddles the end of the span, so it is an interval boundary stated wrongly rather than a
generator that used both forms.

Both installed IDO releases emit `or` and never `addu`, at every optimization level, in all four cross
combinations of their four stages, and GNU `as` agrees at six ISA settings. So this image was built by
two code generators and only one of them is installed; the installed one built the 0x80110490 span.
`multu`-versus-`mult` says the same thing independently: the cartridge has 207 `mult` sites and
neither release emits `mult` for any 32-bit multiply. What that costs the share is measured in
docs/pinned-compiler-reach.md: 82.465% of the denominator carries the `addu` copy and is out of the
installed compiler's reach whatever the C.

These are structural claims about the code, not a compiler name. **No mapping from a
label set to a named compiler and release has been written**, here or in the toolkit,
so this table does not say "IDO 5.3" and cannot be read as saying it.

## What the counts were allowed to see

A count is taken only from words a region proves to be code. The rule is
`return-bounded-body`: a span counts when it ends at `jr $ra` and carries its delay slot,
and every other word is set aside by name. This gate exists because data inside a text
region decodes cleanly -- a jump table of vram addresses reads as a column of byte loads
with no undefined word to give it away -- so a decoder that counts everything it can read
will count the table as code. Nothing below is counted from a word outside a closed span.

| region | words | admissible | inadmissible | closed bodies | counted |
| --- | --- | --- | --- | --- | --- |
| entry | 14 | 0 | 14 | 0 | no |
| text | 179540 | 176143 | 3397 | 1775 | yes |

A region with no closed span is counted by nothing. Where that happens every
discriminator abstains there by name rather than reporting zero, because zero would
read as a measurement and there was no measurement:

- `entry` -- 14 of its 14 words are inadmissible, and all 9 discriminators abstain.

Read in 64 KB windows the same gate sets aside:

- `0x80071000`-`0x80071038` -- 14 of 14 words inadmissible.
- `0x80076000`-`0x80086000` -- 456 of 16384 words inadmissible.
- `0x80086000`-`0x80096000` -- 58 of 16384 words inadmissible.
- `0x80096000`-`0x800A6000` -- 11 of 16384 words inadmissible.
- `0x800A6000`-`0x800B6000` -- 4794 of 16384 words inadmissible.
- `0x800B6000`-`0x800C6000` -- 232 of 16384 words inadmissible.
- `0x800C6000`-`0x800D6000` -- 1712 of 16384 words inadmissible.
- `0x800D6000`-`0x800E6000` -- 32 of 16384 words inadmissible.
- `0x800E6000`-`0x800F6000` -- 298 of 16384 words inadmissible.
- `0x800F6000`-`0x80106000` -- 55 of 16384 words inadmissible.
- `0x80106000`-`0x80116000` -- 3074 of 16384 words inadmissible.
- `0x80116000`-`0x80125550` -- 113 of 15700 words inadmissible.

## The counts

| discriminator | sites | outcomes |
| --- | --- | --- |
| b-encoding | 516 | beq-zero-zero 514, bgez-zero 2 |
| call-delay-slot | 7790 | empty 1749, filled 6041 |
| division-trap-pair | 115 | checked 102, unchecked 13 |
| double-operand-register-parity | 1718 | even-register-double-operand 1701, odd-register-double-operand 17 |
| double-transfer-form | 8215 | double-in-one-access 1077, single-word-access 7138 |
| float-argument-registers | 257 | beyond-first-two-argument-registers 2, first-two-argument-registers 255 |
| gp-relative-accesses | 0 | none |
| move-encoding | 6635 | addu 5694, or 941 |
| stack-release-position | 1775 | frameless 523, released-before-empty-slot 1119, released-before-filled-slot 12, released-in-delay-slot 121 |

The axis the return counts land on is `return-slot-mixed`, not `return-slot-always-empty`. The
cartridge does both, and a description of it as uniformly leaving the return delay slot empty is
wrong on 133 of its 1775 returns.

## Discriminators that decided nothing

Recorded here rather than listed as evidence, because a property that excludes nothing
is not evidence.

- `double-transfer-form` -- no outcome it can report excludes any label.
  ldc1 and sdc1 move 64 bits in one access under either register file: with a 32-bit file the access writes the even/odd pair, with a 64-bit file it writes one register. Their presence dates the instruction set at MIPS II or later and says nothing about register width, and every N64 target is MIPS III, so the count separates no two toolchains in this corpus.
- `float-argument-registers` -- no outcome it can report excludes any label.
  A float register written in the four instructions before a call is not necessarily an argument. Under o32 the callee-clobbered temporaries $f4-$f11 and $f16-$f19 are exactly the registers a compiler spends just before a call, and $f13, $f15 and $f17 carry the low word of a double held in the pair below them. Nothing at the call site distinguishes an argument from a dead temporary, because what makes a register an argument is the callee reading it, which is not in the window.
- `move-encoding` -- it found 6635 sites and none of its outcomes reached an exclusion.

## Regions that disagree

The text was surveyed a second time in 65536-byte windows, to localise any region built
differently from the rest. That run reports 12 windows: 11 narrowed an axis, 1 narrowed
nothing, 0 holding a contradiction.

Every surveyed region that narrowed an axis at all narrowed it the same way. No
region disagrees with the rest of the image on any axis in this set.

These windows narrowed nothing and are unidentified. Most are short or hold little
code; they are listed because an unidentified region is an open finding, not noise:
- `0x80071000`-`0x80071038`, 0 instructions

## Readings that no longer stand

`docs/evidence/toolchain-evidence-previous.json` is a superseded record of the same survey, kept
because the record above withdraws three of its readings. Nothing in it is current:

- `small-data` stood at small-data-in-use and now stands at no-small-data.
- `fp-calling-convention` stood at fp-args-extended and now narrows nothing.
- `fp-register-width` stood at fp-registers-64-bit and the axis is withdrawn.

## What this does not answer

**whether the survey can separate one IDO release from another -- it cannot.** No discriminator in the set separates one IDO release from another. Every label the survey carries is a structural axis, and no mapping from a label set to a named compiler release has been written. Which release built this cartridge is settled under *Which IDO release* below, by compiling the authored sources against both and comparing with the image word for word. That is a different kind of evidence and it is not a count over the image.

**which compiler the surviving label set names -- unwritten.** The survey reports structural claims such as move-always-addu. Turning a set of those into a compiler name needs a mapping measured from known-provenance images, and no such mapping exists yet.

Two further limits are worth stating plainly. A byte-identical image is not evidence
about a compiler: unmatched intervals relink from the cartridge's own extracted
assembly, so the image verifies whether or not any C compiles. And a handful of matched
leaf functions is not evidence either, because short functions are dominated by the
shape of the C, which is free until the source is known.

## Which IDO release

This section is not part of the survey. The survey counts instructions in the image and
narrows structural axes; it separates no two releases of one compiler. What follows is a
different kind of evidence, and it is named as such: the authored sources were compiled
against both releases and compared with the image word for word.

Both releases were installed from their pinned digests and every authored source was compiled with each at the same flag line, then compared word for word with the image. This is a count over compiled functions, not a count over the image, so it stands apart from the survey above and narrows no structural axis.

The flag line is `-c -G0 -non_shared -mips2 -O2`.

| source set | functions | reproduced under 5.3 | reproduced under 7.1 |
| --- | --- | --- | --- |
| sources that already reproduced | 17 | 17 | 17 |
| candidates that did not reproduce under 5.3 | 10 | 0 | 2 |

Three code-generation properties separate the candidates from the image. Only one of
them is a property of the release.

| property | the cartridge | IDO 5.3 | IDO 7.1 | moved by a flag |
| --- | --- | --- | --- | --- |
| intermediate register | threads the value through $v0 | allocates $t6 | threads the value through $v0 | no |
| return delay slot | both, mixed | filled at -O2 | filled at -O2 | yes |
| zero return | addu $v0,$zero,$zero (0x00001021) | or $v0,$zero,$zero (0x00001025) | or $v0,$zero,$zero (0x00001025) | no |

- `intermediate register` -- func_800E3460 wants xori $v0,$v0,2 / sltiu $v0,$v0,1. 5.3 emits xori $t6,$v0,2 / sltiu $v0,$t6,1 at every flag line that compiles, and 7.1 emits the cartridge's form at every one. This is the discriminator: it separates the two releases and no flag moves it.
- `return delay slot` -- func_800A42A4 wants lw / jr / nop. Neither release leaves the slot empty at the configured flags. -O0 empties it on both, and -mips1 empties it on both, so the property is reachable by flags rather than by release; neither was adopted, because both change the 17 sources that already reproduce.
- `zero return` -- func_80096760 and func_800AB614 are two words, a return and a cleared $v0 encoded as addu. Every flag line that compiles, on both releases, emits or. Nothing measured here moves it and it stays open.

Each flag was perturbed on its own, against both releases, and what each one moved is
recorded here. None was adopted.

| perturbation | what it moved |
| --- | --- |
| `-O0` | return delay slot empties on both releases |
| `-O1` | nothing |
| `-O3` | nothing on 7.1; 5.3 refuses the flag |
| `-mips1` | return delay slot empties on both releases |
| `-mips3` | nothing; both releases refuse the flag |
| `-G0 removed` | nothing |
| `-non_shared removed` | nothing |
| `no -mips flag` | return delay slot empties on 5.3, nothing on 7.1 |

Two of the three properties are not answered by the release. The empty return delay slot and the addu-encoded zero return are still unreproduced at the configured flags, and the eight candidates that turn on them are not authored. The flag line is unchanged: a perturbation that wins those eight loses the nineteen that reproduce, which is a worse record, and the flag line is not evidence to be traded for matches.

The version configuration names IDO 7.1, and the measurement above is what it rests on.
The earlier argument for 5.3 over 7.1 rested on eight `$at`-routed word copies inside a
single 64 KB window; the survey does not count that property.
