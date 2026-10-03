#ifndef UNBAKE_FUNC_80097B7C_H
#define UNBAKE_FUNC_80097B7C_H
#include "types.h"

struct func_80097B7C_S1;
typedef struct func_80097B7C_S1 func_80097B7C_S1;



struct func_80097B7C_S1 {
    char pad0[0x1];
    u8 unk1;
    char pad1[0x458 - 0x1 - sizeof(u8)];
    s32 unk458;
    s32 unk45C;
    char pad45C[0x4F0 - 0x45C - sizeof(s32)];
    s32 unk4F0;
};
#endif
