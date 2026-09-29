# BattleTanx decompilation

A matching decompilation of *BattleTanx* for the Nintendo 64.

> **This repository contains no game content, and never will.** Supply a cartridge image you dumped yourself. The build verifies it against the SHA256 below and refuses anything else. Everything here is derived from that dump and from the toolchain, never from leaked or previously decompiled source.

## Progress

| us (NUS-NBXE-0, North America). NTSC release. SHA256 c5b7cf3523de025e3f18e2c8df2deb0eced5613e7c46cb8c6c5a4f22644ead3f |
|---|
| <pre><code>bytes     [--------------------]   1.26%  9,052 of 718,160</code><br><code>functions [#-------------------]   5.70%  99 of 1,738</code></pre> |

## Development & Contributions

For detailed instructions please see [DEVELOPMENT.md](DEVELOPMENT.md).

### AI Usage Disclaimer

AI is used in the decompilation process. Its use is limited to drafting candidate C and rearranging code that already matches, and its output is objectively verifiable by compiling against the ROM. Future work such as naming functions and describing what the code does will be led by human authors.

## License

The repository's own code is released under [CC0 1.0](LICENSE).

## Dependencies

- [N64DecompTools](https://github.com/melalawi/n64-decomp-tools), the toolkit that builds, proves and measures this decompilation.
- [splat](https://github.com/ethteck/splat) version 0.50.0.
- [m2c](https://github.com/matt-kempster/m2c) at `708d2d2cb2698f091a92492b328f73b24209f72d`.
- [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) at `059609d4aec73eb0650726772954e1ad575825f8`.
- [maspsx](https://github.com/mkst/maspsx) at `7686f845a181700534c83c0419183e38aeb3e49c`.
- [GCC 2.7.2 (KMC)](https://github.com/decompals/mips-gcc-2.7.2) at `43d1cdb67ed135879869b5266f01efaaada5e35a`, the compiler of toolchain `gcc-2.7.2`, assembled by SN ASN64 version 2.81.
- [IDO static recompilation](https://github.com/decompals/ido-static-recomp), the compiler of toolchain `ido-7.1`.

