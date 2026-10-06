# BattleTanx decompilation

A matching decompilation of *BattleTanx* for the Nintendo 64.

> **This repository contains no game content.** You must supply a legally acquired cartridge dump. Builds are verified against its SHA256.

## Progress

| us (NUS-NBXE-0, North America). NTSC release. SHA256 `c5b7cf3523de025e3f18e2c8df2deb0eced5613e7c46cb8c6c5a4f22644ead3f` |
|---|
| <pre><code>bytes     [▒░░░░░░░░░░░░░░░░░░░]   2.61% (~3.22%)  18,448 of 705,956</code><br><code>functions [██░░░░░░░░░░░░░░░░░░]   10.60%  182 of 1,717</code></pre> |

## Development & Contributions

Contributions and corrections are welcome. Run `make check` before opening a pull request.

For detailed instructions please see [CONTRIBUTING.md](CONTRIBUTING.md).

## AI Usage

### Workflow

AI is used in the decompilation process and every function is verified by compiling it against the original ROM. A match can still be a fakematch or use odd C semantics. I try to mark these in source as they are discovered.

I turned these efforts into a repeatable process with [AbuCakeUnbake64](https://github.com/melalawi/abu-cake-unbake-64). It is built so AI can drive it against any N64 ROM.

### Personal Thoughts

AI suits decompilation well. Every function is checked deterministically against the original ROM so correctness is always provable. Decompiled code is plain source built with the original toolchain so nothing opaque runs on the player's machine and the only attack surface is the build tooling. Readable source can be ported, fixed and preserved long after its tools are gone.

While recompilations can be a fine short-term way to play a favourite game, I believe AI-driven recomps are junk and should be avoided entirely. Used this way AI carries more security risk and is more likely to leave the scene littered with broken and abandoned ports. For games as compact as most N64 titles it makes more sense to point AI at a proper decompilation instead.

## License

[CC0 1.0](LICENSE)

## Dependencies

- [AbuCakeUnbake64](https://github.com/melalawi/abu-cake-unbake-64) at `952cffe232b2584de3dbc07d8e054baf71eb0e67`
- [GCC 2.7.2 (KMC)](https://github.com/decompals/mips-gcc-2.7.2) at `43d1cdb67ed135879869b5266f01efaaada5e35a`, the compiler of toolchain `gcc-2.7.2`, assembled by SN ASN64 version 2.81
- [IDO static recompilation](https://github.com/decompals/ido-static-recomp), the compiler of toolchain `ido-7.1`
