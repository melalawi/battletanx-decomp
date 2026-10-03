#ifndef UNBAKE_FUNC_8010DCD0_H
#define UNBAKE_FUNC_8010DCD0_H
#include "types.h"

struct func_8010DCD0_S1;
typedef struct func_8010DCD0_S1 func_8010DCD0_S1;
typedef struct func_8010DCD0_S2 func_8010DCD0_S2;
typedef struct func_8010DCD0_S3 func_8010DCD0_S3;

struct func_8010DCD0_S2;

struct func_8010DCD0_S3;







struct func_8010DCD0_S1 {
    char pad0[0x18];
    s32 unk18;
    s32 unk1C;
    char pad1C[0x24 - 0x1C - sizeof(s32)];
    s32 unk24;
};
struct func_8010DCD0_S2 {
    char pad0[0x8];
    s32 unk8;
};
struct func_8010DCD0_S3 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};
#endif
