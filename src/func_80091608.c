#include "shared/func_80091608.h"
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
