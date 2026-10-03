#ifndef UNBAKE_FUNC_80079EFC_H
#define UNBAKE_FUNC_80079EFC_H
#include "types.h"

struct Func79EFCArg;
typedef struct Func79EFCArg Func79EFCArg;



struct Func79EFCArg {
    s32 unk0;
    s32 unk4;
    s8 unk8;
    s8 unk9;
    s8 padA[2];
    union {
        s32 values[4];
        struct {
            s32 unkC;
            s32 unk10;
            s32 unk14;
            s32 unk18;
        } fields;
    } tail;
};
#endif
