#ifndef UNBAKE_FUNC_800A51E8_H
#define UNBAKE_FUNC_800A51E8_H
#include "types.h"

struct FuncA51E8State;
typedef struct FuncA51E8State FuncA51E8State;



struct FuncA51E8State {
    char pad0[0x1A6];
    u8 unk1A6;
    char pad1A7[0x218 - 0x1A7];
    s32 unk218;
    s32 unk21C;
    char pad220[0x260 - 0x220];
    s32 unk260;
};
#endif
