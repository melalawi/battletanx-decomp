#include "shared/func_800a7550.h"
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
void *func_8008AD10();     /* extern */
s32 func_80106D18(); 



/* extern */

void func_800A7550(f32 arg0, f32 arg1, s32 arg2) {
    s32 temp_a3;
    func_800A7550_S1 *temp_v0;

    temp_v0 = func_8008AD10(0, 0x1F, 0x18);
    if (temp_v0 != NULL) {
        temp_a3 = -arg2;
        temp_v0->unkC = func_80106D18(temp_v0, (s32) arg0, (s32) arg1, temp_a3, arg2, temp_a3, arg2, 2, 0);
        temp_v0->unk14 = arg0;
        temp_v0->unk10 = arg1;
    }
}
