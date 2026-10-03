#include "shared/func_800ed810.h"
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
s32 func_800ECE4C();             /* extern */
s32 func_800ED380();   /* extern */
s32 func_800ED5C8();                     





/* extern */

void func_800ED810(func_800ED810_S1 *arg0, s32 arg1, u32 arg2, s32 arg3, func_800ED810_S2 *arg4) {
    switch (arg2) {                                 /* irregular */
    case 0:
        func_800ECE4C(arg0, arg1, arg3, arg4);
        return;
    case 2:
        if (arg0->unk1C == 0) {
            arg4->unk0 = 1;
            arg4->unk8 = (f32) arg0->unkC;
            arg4->unk4 = (f32) arg0->unk14;
            return;
        }
        return;
    case 3:
        func_800ED380(arg0, 0, arg3, 0);
        return;
    case 7:
        func_800ED5C8(arg0, arg1, arg3);
        break;
    }
}
