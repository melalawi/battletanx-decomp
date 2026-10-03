#ifndef UNBAKE_FUNC_800793D0_H
#define UNBAKE_FUNC_800793D0_H
#include "types.h"

struct func_800793D0_S1;
typedef struct func_800793D0_S1 func_800793D0_S1;
typedef struct func_800793D0_S2 func_800793D0_S2;

struct func_800793D0_S2;





struct func_800793D0_S1 {
    char pad0[0x1F4];
    u16 unk1F4;
    char pad1F4[0x1F8 - 0x1F4 - sizeof(u16)];
    s32 unk1F8;
    s32 unk1FC;
    char pad1FC[0x204 - 0x1FC - sizeof(s32)];
    struct func_800793D0_S2 * unk204;
};
struct func_800793D0_S2 {
    char pad0[0x40];
    s32 unk40;
};
#endif
