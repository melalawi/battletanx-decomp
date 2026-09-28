# How much of this cartridge the pinned compiler can reach

**Most of this cartridge was not built by either installed IDO release**, so the share has a ceiling
far below 100% until the other code generator is available. This is the measurement.

Every figure below is against the denominator `decomp measure` reports, 718,160 bytes over 1,276
function intervals. Five percent of it is **35,908 bytes**. The per-interval tallies were taken over
that population with the `move-encoding` anchor in `matchkit/provenance/discriminators.json` — `addu`,
`or` or `daddu` writing a non-zero register from one zero source — counted over every word of an
interval rather than only the words the survey's admissibility gate admits.

## Three divergences, each measured on the installed compilers

All probes compiled with the project's own flags, `-c -G0 -non_shared -mips2 -O2` unless stated, against
both `artifacts/ido/7.1/cc` and `artifacts/ido/5.3/cc`.

### 1. A register-to-register copy is `or`, never `addu`

`int g(int a) { int b = a; return f(b) + b; }` gives `or $d, $s, $zero` at `-O1` and no copy at all at
`-O0` or `-O2`. Zero `addu $d, $s, $zero` at any level on either release. Driving `cfe`, `uopt`, `ugen`
and `as1` by hand in all four cross combinations of the two releases gives `or` every time, and GNU
`as` gives `or` at `-march` r3000, r4000, mips1, mips2, mips3 and vr4300.

Over the cartridge, the two encodings are **segregated by address**: of 1,276 intervals, 667 use only
`addu`, 143 use only `or`, 465 make no register-to-register copy at all, and one uses both. The `or`
form occupies one contiguous span, `0x80110490`..`0x80124350` — 143 `or`-encoded intervals over 65,272
bytes, inside a span holding 264 intervals and 81,600 bytes — with **not one `addu`-encoded interval
inside it**. The one interval that mixes the forms, `func_8010DED4`, is 9,644 bytes and runs up to the
start of that span: it carries `addu` copies in its first 0x8C0 bytes and `or` copies at +0x13D0 and
+0x1418, so it is a split interval that swallows functions on both sides of the boundary rather than a
generator that used both forms. Repairing that boundary is the check on this reading, and it is the
only interval in the cartridge that needs one.

This cartridge was built by two code generators. Only one of them is installed, and the block it built
is the libultra-shaped one.

**The other one is identified: GCC 2.7.2, the release the KMC N64 build ships, assembled by SN
Systems' ASN64 2.81.** It was first read as GCC 2.8.1 for mips-nintendo-nu64, and that reading does not
survive C written for the `addu` region: `func_8007627C`, written from its own assembly, reproduces 66
of 69 words under the pinned 2.8.1 cc1 and all 69 under 2.7.2, and the three words are the epilogue --
2.8.1 always releases the frame in the return's delay slot, and this region leaves it before an empty
slot 987 times. Over 24 intervals of different shapes (leaf, calls, loops, floats, a jump table, `mult`,
`div`), each compiled from C under every public candidate with no change to the source:

| chain | intervals reproduced in full |
|---|---|
| GCC 2.7.2 (KMC's output, built from public source) + ASN64 2.81 | 23 of 24; the 24th at 14 of 15 words |
| SN's own cc1n64 2.7.2 (builds 0004 and 0006) + ASN64 2.81 | 9 of 24 |
| SN64-gcc 2.7.2-970404 + ASN64 2.81 | 0 of 24 |
| GCC 2.7.2 + GNU as 2.44 at `-O1`, `move` spelled `addu` | 19 of 24 |
| GCC 2.7.2 + GNU as 2.6, the KMC kit's own | 10 of 24 |

So the assembler is decided as well: GNU as 2.6 moves the frame release into the return's slot, and
GNU as 2.44 places `li.s` constants inline where the cartridge loads them from `.rdata`. The three
fingerprints above are the compiler's and agree with it: every `or`-region function has `frame − ra_offset
≡ 4 (mod 8)` while 263 `addu`-region functions are ≡ 0 and 250 never write the top frame word; the `addu`
region has 193 `mult` against 64 `multu` where the `or` region has 0 against 29.

### 2. A 32-bit multiply is `multu`, never `mult`

`int*int`, `unsigned*unsigned`, `short*short` and `x*2400` in one file give three `multu` and zero
`mult`, at `-O1` and `-O2`, on both releases. The cartridge has **207 `mult` sites against 95 `multu`**,
and the 75 intervals holding a `mult` are 91,064 bytes, 12.680% of the denominator.

Constant-multiply synthesis differs too: the cartridge lowers `x*2400` in five instructions
(`sll 2; addu; sll 4; subu; sll 5`) where IDO takes seven, and lowers `x*24` as `(2x+x)*8` where IDO
gives `(4x-x)*8`.

### 3. A value live across a call reaches `$s0..$s7` only inside a loop

Four values live across three calls with no loop: no callee-saved register at any of `-O0`, `-O1`,
`-O2`, everything spilled to its frame slot. The same values inside a `for` loop: `$s0..$s3` at `-O2`
and `$s0` at `-O1`. `cc -v` shows the pipeline complete and `uopt` running with `-O2`, so this is the
allocator's rule and not a missing stage. `-O3` is not an alternative: `cc` warns that `-c` should not
be used with ucode `-O3` on a single file and then fails, `can't find or exec: /usr/lib/ujoin`;
`-Olimit` and `-Wo,` are rejected as unknown options by this driver.

## Which compiler built each object is stated per object

Every object names the compiler that built it: `data/object-toolchains.json` names `ido-7.1` for the
span `0x80110490`..`0x80124350` and for every interval already landed under IDO, and `gcc-2.7.2` for the
rest, and `config.toml` pins each as its own `[toolchains]` block. Every step -- the build, a trial, a
search, a landing, the classifier and the draft -- asks for the object's own compiler, so the idiom
record read for an interval is that compiler's record, not a guess from its signals. The narrower case
inside the `or` region, where `func_8011A17C`, `func_8011E6B0` and `func_8011A1F0` reproduce under IDO
5.3 while `func_800E3460` and `func_800E3470` need 7.1, is now expressible the same way, as a third block.

## Which release: 7.1, measured

The two installs are not interchangeable. With the IDO block's `installed` pointing at `artifacts/ido/5.3`
instead of `artifacts/ido/7.1`, the image stops being the cartridge: `func_800E3460` and
`func_800E3470` each gain two differing words, and nothing else in 8,388,608 bytes changes. 7.1 emits

    lbu $v0, 0x350($a0) / xori $v0, $v0, 2 / jr $ra / sltiu $v0, $v0, 1

which is the cartridge's own four words, and 5.3 routes the same value through `$t6`
(`xori $t6, $v0, 2` then `sltiu $v0, $t6, 1`). Both sources are two lines of C and unchanged between
the two builds, so the difference is the release. The IDO block's `installed` and `pins` name 7.1, and
that is a measurement rather than a decision. The two releases are otherwise indistinguishable
on every property in the three divergences above.

## The ceiling the `addu` copy sets

This was the ceiling while IDO 7.1 was the only compiler the description could name, and it is kept as
the measurement that showed a second one was needed. With GCC 2.7.2 pinned for the objects it built,
the `addu` copy is that compiler's ordinary output and bounds nothing.

Over the 1,276 intervals:

| | intervals | bytes | of 718,160 |
|---|---|---|---|
| uses the `addu` copy, so out of the pinned compiler's reach whatever the C | 667 | 592,232 | **82.465%** |
| does not, so the copy at least is expressible | 609 | 125,928 | **17.535%** |

Five percent of the denominator is 35,908 bytes, which is 28.5% of the second row. The first row
cannot be reached at all until the other code generator is available.

**The bound is by signal, not by address, and a landing proves it.** `func_800E3C18` sits at
`0x800E3C18`, inside the `addu` span, and its 28 bytes contain no register-to-register copy of either
encoding. It is landed and byte-identical under the pinned IDO, as are `func_800E3480`,
`func_800E566C` and `func_8010BC08` on the same footing. Bounding reach by the `or` span's addresses
would have to read each of those as a counter-example; bounding it by whether the interval carries the
`addu` copy predicted them. Intervals outside the `or` span that carry no `addu` copy are the cheapest
remaining work under the current toolchain.

A finer ceiling — splitting the reachable intervals by whether they also need a callee-saved register
outside a loop, which divergence 3 says the pinned compiler will not emit — was measured once against
the 1,270-interval population and is not restated here: the classification it rested on is recorded
nowhere in this repository, so it cannot be re-taken. `decomp measure` reports the ceiling the filler
set sets, 99.983848%, and that one is re-measured from the cartridge on every call.

## What else is measurable inside the reachable block

- **The optimization level alternates per object.** `func_80121F10` is byte-identical at `-O1` and
  badly wrong at `-O2`; so is `func_8011540C` (104 bytes, 57 of 57 words wrong at `-O2`).
  `[toolchain].object_options` is where that belongs, and it now keys seven functions to `["-O1"]`;
  each entry reproduces its whole interval at that level and at no other. A function that only
  reproduces its body at `-O1` is not entered until it reproduces its interval, because a key stating
  an unproved option would be a guess.
- **Symbols the split does not name — the largest single blocker after the two code generators.** A
  candidate is linked against `[split].symbols` plus `[split].generated_symbols` and nothing else, so a
  datum whose only definition is a `dlabel` inside the extracted data assembly resolves nowhere and the
  trial refuses the function outright. The float and double literal pool is entirely of that kind:
  `D_80071E94` (`.float 4`), `D_80072640`, `D_8007443C`, `D_80074718` and their neighbours are defined
  in `artifacts/us/extracted/asm/data/data.data.s` and named by no table. Measured across four drafting
  batches, this refused 60 of 102, 51 of 101, 49 of 104 and 24 of 52 targets — essentially every
  interval that loads a floating-point constant, which is most of the large ones. Naming those labels in
  a symbol table is the cheapest single thing that would widen the reachable set, and it is not free:
  a new symbol renames intervals during extraction, so it churns every object and must be done when no
  other lane is building. Beyond the pool, the same cause covers `D_80145DF0` (defined in the
  extracted `rodata` section), `D_80137900`, `D_801257D0`, `jtbl_80073110`, and the compiler's own
  runtime helpers `__ll_div` and `__ll_mul`.
- **Intervals wider than the function in them.** Where a split interval carries trailing
  inter-function alignment or a second function, a candidate can be byte-exact over the function and
  still differ over the interval. Measured pairs (interval/function): `func_8011E2E0` 272/48,
  `func_800E09B0` 152/68, `func_80121F90` 192/184, `func_800DCCC0` 1616/780, `func_800D1BA0` 896/796.
  These are interval boundaries stated wrongly, not hard targets, and repairing a boundary is cheaper
  than drafting against it.
- **Intervals no C can express.** `func_8011BAE0` executes `mfc0`/`mtc0`; `func_80113790` adds `tlbwi`;
  `func_801124C0` and `func_801226A0` use `cache`. Cited by the instructions they contain, not by any
  label.
- **The four 64-bit runtime helpers are in the image and addressable.** `long long` arithmetic at
  `-mips2` compiles to calls, and the bodies sit at `0x801131A0`..`0x80113460`. Identified from the
  cartridge's own `jal` words and confirmed by linking a probe per operation against them:
  `__ull_rem = 0x801131CC`, `__ull_div = 0x80113208`, `__ll_div = 0x801132AC`, `__ll_mul = 0x80113308`.
  These are four addresses the project has not stated, not a class of non-C code.

## The two facts a drafter is handed automatically

`decomp/ido/idioms.json` in the toolkit records the first and third divergences as
`register-copy-is-or-not-addu` and `callee-saved-only-across-a-call-inside-a-loop`, each with the signal
over this disassembly, the population it fires on, the interval that attests it, and its exception.
`matchkit classify` carries them to whoever asks about an interval. Nothing was read across from
`decomp/sn64/idioms.json`, whose eighteen entries are about a different compiler.
