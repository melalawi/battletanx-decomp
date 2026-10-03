#ifndef UNBAKE_FUNC_800E34B4_H
#define UNBAKE_FUNC_800E34B4_H
#include "types.h"

struct func_800E34B4_S1;
typedef struct func_800E34B4_S1 func_800E34B4_S1;
typedef union func_800E34B4_S1_U8 func_800E34B4_S1_U8;
typedef struct func_800E34B4_S2 func_800E34B4_S2;

union func_800E34B4_S1_U8;

struct func_800E34B4_S2;







union func_800E34B4_S1_U8 {
    u8 v0;
    f32 v1;
};
struct func_800E34B4_S2 {
    char pad0[0x24];
    f32 unk24;
    char pad24[0x4];
    f32 unk2C;
};
struct func_800E34B4_S1 {
    s32 unk0;
    void * unk4;
    func_800E34B4_S1_U8 unk8;
    f32 unkC;
    void * unk10;
    s32 unk14;
};
#endif
