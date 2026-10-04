#include "span_1000/code_8008F248.h"
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

#include "types.h"
#define NULL ((void *)0)


#ifndef M2C_MACROS_H
#define M2C_MACROS_H

/* Unknown types */

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */

/* Bitwise (reinterpret) cast */

/* Unaligned reads */

/* Unhandled instructions */

/* Carry/overflow bits from partially-implemented instructions */

/* Memcpy patterns */

/* Sh2 control register loads/stores */

#endif
s32 func_8008B89C();                      /* extern */
s32 func_8009FBE4();                             /* extern */
s32 func_800E3460();                             /* extern */





void func_80091608(func_80091608_Object *arg0, func_80091608_Status *arg1, void *arg2, func_80091608_Output *arg3) {
    if (arg0->unk20 == 0) {
        if ((arg1->unk8 == 0) && ((func_8009FBE4(arg1->unkC) & 0xFF) != arg0->unk2C) && (func_800E3460(arg1->unkC) == 0)) {
            arg3->code = 3;
            arg3->value = (s32) arg0->unk18;
            arg0->unk20 = 1U;
            func_8008B89C(arg0);
            return;
        }
        goto block_6;
    }
block_6:
    arg3->code = 1;
}
