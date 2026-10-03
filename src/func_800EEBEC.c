#include "shared/func_800eebec.h"
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
s32 func_800E3470();                             /* extern */
extern u8 D_8033B630;
extern u8 D_8033B631;
extern s32 D_8013957C;                          /* unable to generate initializer: unknown type; const */
extern s32 D_801395B8;                          /* unable to generate initializer: unknown type; const */





void func_800EEBEC(FuncEEBECObject *arg0, FuncEEBECStatus *arg1, void *arg2, FuncEEBECOutput *arg3) {
    if (arg1->field_8 == 0) {
        if (func_800E3470(arg1->field_c) != 0) {
            if (arg0->unk24 < 0.0f) {
                if (D_8033B630 != 0) {
                    arg3->code = 0xA;
                    arg3->data = &D_8013957C;
                    return;
                }
                goto block_7;
            }
            if (D_8033B631 != 0) {
                arg3->code = 0xA;
                arg3->data = &D_801395B8;
                return;
            }
            goto block_7;
        }
block_7:
        arg3->code = 1;
    }
}
