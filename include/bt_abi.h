#ifndef BT_ABI_H
#define BT_ABI_H
#include "acmd.h"
/* ABI1 audio command fields. Reference: n64decomp/sm64 include/PR/abi.h.
 * Use the shared eight-byte Acmd layout; these are audio, not RDP commands. */
#define aSetBuffer(pkt, flags, input, output, count) do { \
    Acmd *bt_audio = (Acmd *)(pkt); \
    bt_audio->words.w0 = 0x08000000U | (((u32)(flags) & 255U) << 16) | ((u32)(input) & 65535U); \
    bt_audio->words.w1 = (((u32)(output) & 65535U) << 16) | ((u32)(count) & 65535U); \
} while (0)
#define aResample(pkt, flags, pitch, state) do { \
    Acmd *bt_audio = (Acmd *)(pkt); \
    bt_audio->words.w0 = 0x05000000U | (((u32)(flags) & 255U) << 16) | ((u32)(pitch) & 65535U); \
    bt_audio->words.w1 = (u32)(state); \
} while (0)
#endif
