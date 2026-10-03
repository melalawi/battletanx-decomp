#ifndef UNBAKE_FUNC_800E9894_H
#define UNBAKE_FUNC_800E9894_H
#include "types.h"

struct func_800E9894_S1;
typedef struct func_800E9894_S1 func_800E9894_S1;
typedef struct func_800E9894_S2 func_800E9894_S2;
typedef struct func_800E9894_S3 func_800E9894_S3;
typedef struct func_800E9894_S4 func_800E9894_S4;

struct func_800E9894_S2;

struct func_800E9894_S3;

struct func_800E9894_S4;









struct func_800E9894_S1 {
    void * unk0;
    void * unk4;
    struct func_800E9894_S3 * unk8;
    void * unkC;
    void * unk10;
    s32 unk14;
    s16 unk18;
    s16 unk1A;
    u8 unk1C;
    char pad1C[0x40 - 0x1C - sizeof(u8)];
    s32 unk40;
    s32 unk44;
};
struct func_800E9894_S2 {
    char pad0[0x4];
    u8 unk4;
};
struct func_800E9894_S3 {
    char pad0[0x4];
    u8 unk4;
    char pad5[0x9C - 0x5];
    u8 unk9C;
    char pad9D[0xCC - 0x9D];
    u8 unkCC;
};
struct func_800E9894_S4 {
    char pad0[0x1AE];
    u8 unk1AE;
};
#endif
