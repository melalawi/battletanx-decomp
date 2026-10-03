#include "shared/func_800e6ca4.h"
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
/* Tests whether two points remain within the object's scaled distance threshold. */
f32 func_800E1A20(s32, f32 *);                  



/* extern */

s32 func_800E6CA4(func_800E6CA4_S1 *arg0, s32 arg1) {
    f32 sp10[4];
    f32 temp_f20;
    f32 temp_f4;
    f32 arg0_2;
    f32 temp_f6;
    s32 var_v0;
    float temp_2;

    temp_f4 = arg0->unk4D4;
    sp10[1] = temp_f4;
    temp_f6 = arg0->unk4D0;
    sp10[0] = temp_f6;
    sp10[3] = temp_f4 + (arg0->unk4DC * arg0->unk4E0);
    sp10[2] = temp_f6 + ((arg0_2 = arg0->unk4D8) * arg0->unk4E0);
    temp_f20 = func_800E1A20(arg1, &sp10[0]);
    temp_2 = temp_f20 + func_800E1A20(arg1, &sp10[2]);
    var_v0 = 1;
    if (!(temp_2 < (arg0->unk4E0 * 1.2f))) {
        var_v0 = 0;
    }
    return var_v0;
}
