#include "span_1000/code_800EECA0.h"
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

#include "types.h"
/* When arg2 and the status field at offset 8 are zero, sets output code 10 and sign-specific data if func_800E3470 succeeds and the corresponding flag is set, otherwise setting code 1. */
#define NULL ((void *)0)

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
#endif

s32 func_800E3470();

extern u8 D_8033B630;
extern u8 D_8033B631;
extern s32 D_8013957C;
extern s32 D_801395B8;





void func_800EECA0(FuncEECA0Object *arg0, FuncEECA0Status *arg1, s32 arg2, void *arg3, FuncEECA0Output *arg4) {
    s32 temp_arg3;
    s32 temp_arg0;

    temp_arg0 = (s32) arg0;
    temp_arg3 = (s32) arg4;

    if ((arg2 == 0) && (arg1->field_8 == 0)) {
        if (func_800E3470(arg1->field_c) != 0) {
            if (((FuncEECA0Object *) temp_arg0)->unk24 < 0.0f) {
                if (D_8033B630 != 0) {
                    ((FuncEECA0Output *) temp_arg3)->code = 0xA;
                    ((FuncEECA0Output *) temp_arg3)->data = &D_8013957C;
                    return;
                }
            } else if (D_8033B631 != 0) {
                ((FuncEECA0Output *) temp_arg3)->code = 0xA;
                ((FuncEECA0Output *) temp_arg3)->data = &D_801395B8;
                return;
            }
        }
        ((FuncEECA0Output *) temp_arg3)->code = 1;
    }
}
