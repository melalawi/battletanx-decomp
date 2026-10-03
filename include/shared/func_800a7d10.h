#ifndef UNBAKE_FUNC_800A7D10_H
#define UNBAKE_FUNC_800A7D10_H
#include "types.h"

struct func_800A7D10_S1;
typedef struct func_800A7D10_S1 func_800A7D10_S1;
typedef struct func_800A7D10_S3 func_800A7D10_S3;

struct func_800A7D10_S3;





struct func_800A7D10_S1 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
};
struct func_800A7D10_S3 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    char pad8[0x10 - 0x8 - sizeof(f32)];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    char pad18[0x20 - 0x18 - sizeof(f32)];
    f32 unk20;
    f32 unk24;
    f32 unk28;
    char pad28[0x30 - 0x28 - sizeof(f32)];
    f32 unk30;
    f32 unk34;
    f32 unk38;
};
#endif
