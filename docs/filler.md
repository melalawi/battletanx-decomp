# The filler mirror distance, measured

`[split].filler_mirror_distance` in `config.toml` is `0xB8000`. This is the measurement behind it.

## What the key means

`decomp/filler.py` states the criterion once. An interval cannot hold a function body when nothing in
the interval population reaches its start **and** either it is shorter than eight bytes, or every one
of its words is zero or equals the word `filler_mirror_distance` later in the ROM file without being
`jr $ra` or a frame allocation, with at least one word a non-zero echo. The key is the only
project-stated input to that second clause, so it decides which intervals leave the function
denominator.

## How the distance was taken

The interval population was built from `versions/us/battletanx.yaml` through the toolkit's own
`decomp.intervals.functions`, with `vram`, `rom` and `function_prefix` read from `config.toml`.
`decomp.filler.reached` gave the reached set. For every unreached, word-aligned interval of eight
bytes or more, **every** forward distance in the whole 8,388,608-byte image at which the toolkit's
clause (b) would hold was enumerated, by indexing the image's 2,097,152 words by value and verifying
each candidate alignment. The totals below are `decomp measure`'s: it re-measures the filler set from
the cartridge on every call, and reports it as `unreachable_filler`.

Result over the 1,276 function intervals of the current split:

| | count |
|---|---|
| unreached, word-aligned intervals | 165 |
| of those, under eight bytes (carried by length alone) | 12 |
| of those, needing an echo | 153 |
| echo-needing intervals that **any** distance admits | 7 |
| distinct distances admitting at least one | 7 |
| distances admitting more than one | **1** |

That one distance is `0xB8000`, and it admits all seven. Five of the seven are admitted by `0xB8000`
and by nothing else in the image: their eight- and twelve-byte patterns occur exactly twice in 8 MB,
and the second occurrence is `0xB8000` later. The other two also echo at distances of their own —
`func_80090ED8` at `0xB69E4`, `func_800AC2C8` at five further distances — and no distance but
`0xB8000` admits more than one interval.

The seven runs it names:

| interval | ROM offset | bytes | content |
|---|---|---|---|
| `func_80090ED8` | `0x020ED8` | 8 | `49004F00 4E005300` |
| `func_80096E74` | `0x026E74` | 12 | `CED20100 E645004E 00410000` |
| `func_800A03F8` | `0x0303F8` | 8 | `004F0050 00530000` |
| `func_800A5FE4` | `0x035FE4` | 12 | `6808000F CE520097 43000000` |
| `func_800A7648` | `0x037648` | 8 | `02D05AC0 A6580000` |
| `func_800A9C14` | `0x039C14` | 12 | `05000300 9C954005 000300A0` |
| `func_800AC2C8` | `0x03C2C8` | 8 | `53005400 41004E00` |

None of them decodes as a function. Each sits between two functions in the text — `0x020ED8` follows
a `jr $ra` and its empty delay slot and is followed by `addiu $sp, $sp, -0x18`, a prologue — and each
is a run of wide characters. Their mirrors all land past `0x0D7040`, the end of the loaded run, inside
the untyped tail, where the same wide-character runs sit in packed string data.

The relationship is not a verbatim block copy. Over `0x020000..0x040000` the byte-agreement rate at
delta `0xB8000` is 8.27%, which twelve randomly chosen controls bracket (0.39% to 11.31%, mean 4.79%),
so the later region is a repacking of the same string data in which these particular runs survive
byte-for-byte rather than a second image of the first.

## What other distances would give

Run through the same criterion on this image, `0x1000` admits **no** echo-needing interval at all —
the filler set collapses to the twelve intervals length alone carries, 48 bytes. So do `0x800`,
`0x2000`, `0x4000` and `0x10000`. Any of them would leave seven intervals of this cartridge's string
data inside the function denominator.

| distance | filler intervals | filler bytes |
|---|---|---|
| `0x800` | 12 | 48 |
| `0x1000` | 12 | 48 |
| `0x2000` | 12 | 48 |
| `0x4000` | 12 | 48 |
| `0x10000` | 12 | 48 |
| **`0xB8000`** | **19** | **116** |

## What it makes the denominator

1,276 function intervals, 718,160 bytes. Nineteen of them are filler over 116 bytes, so 1,257
intervals can hold a function body and the byte share's ceiling is 99.983848%. Five percent of the
byte denominator is **35,908 bytes**.
