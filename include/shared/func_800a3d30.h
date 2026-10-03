#ifndef UNBAKE_FUNC_800A3D30_H
#define UNBAKE_FUNC_800A3D30_H
#include "types.h"

struct FuncA3D30Table;
typedef struct FuncA3D30Table FuncA3D30Table;
typedef struct func_800A3D30_S1 func_800A3D30_S1;
typedef struct func_800A3D30_S2 func_800A3D30_S2;

struct func_800A3D30_S1;

struct func_800A3D30_S2;







struct FuncA3D30Table {
    s32 value[3];
};
struct func_800A3D30_S1 {
    char pad0[0x20];
    s16 unk20;
    char pad20[0x22];
    u16 unk44;
};
struct func_800A3D30_S2 {
    char pad0[1];
    u8 unk1;
    char pad1[0x18 - 2];
    s32 unk18;
    char pad18[0x504 - 0x1C];
    s32 unk504;
};
#endif
