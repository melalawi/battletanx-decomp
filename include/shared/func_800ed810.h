#ifndef UNBAKE_FUNC_800ED810_H
#define UNBAKE_FUNC_800ED810_H
#include "types.h"

struct func_800ED810_S1;
typedef struct func_800ED810_S1 func_800ED810_S1;
typedef struct func_800ED810_S2 func_800ED810_S2;

struct func_800ED810_S2;





struct func_800ED810_S1 {
    char pad0[0xC];
    f32 unkC;
    char padC[0x14 - 0xC - sizeof(f32)];
    f32 unk14;
    char pad14[0x1C - 0x14 - sizeof(f32)];
    u8 unk1C;
};
struct func_800ED810_S2 {
    s8 unk0;
    char pad0[0x4 - 0x0 - sizeof(s8)];
    f32 unk4;
    f32 unk8;
};
#endif
