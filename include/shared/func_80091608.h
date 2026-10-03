#ifndef UNBAKE_FUNC_80091608_H
#define UNBAKE_FUNC_80091608_H
#include "types.h"

struct func_80091608_Object;
typedef struct func_80091608_Object func_80091608_Object;
typedef struct func_80091608_Output func_80091608_Output;
typedef struct func_80091608_Status func_80091608_Status;

struct func_80091608_Output;

struct func_80091608_Status;







struct func_80091608_Object {
    char pad0[0x18];
    s32 unk18;
    char pad18[4];
    u8 unk20;
    char pad20[0xB];
    s32 unk2C;
};
struct func_80091608_Output {
    s32 code;
    s32 value;
};
struct func_80091608_Status {
    char pad0[8];
    s32 unk8;
    s32 unkC;
};
#endif
