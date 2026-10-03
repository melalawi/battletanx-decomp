#ifndef UNBAKE_FUNC_800EECA0_H
#define UNBAKE_FUNC_800EECA0_H
#include "types.h"

struct FuncEECA0Object;
typedef struct FuncEECA0Object FuncEECA0Object;
typedef struct FuncEECA0Output FuncEECA0Output;
typedef struct FuncEECA0Status FuncEECA0Status;

struct FuncEECA0Output;

struct FuncEECA0Status;







struct FuncEECA0Object {
    char pad0[0x24];
    f32 unk24;
};
struct FuncEECA0Output {
    s32 code;
    s32 *data;
};
struct FuncEECA0Status {
    char pad_0[8];
    s32 field_8;
    s32 field_c;
};
#endif
