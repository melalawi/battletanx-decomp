#include "shared/func_80097b7c.h"
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
s32 func_800798C0();                         /* extern */
void *func_800A03B8();                           



/* Resets the active entries and releases their associated resources. */

void func_80097B7C(void) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 var_s1;
    func_80097B7C_S1 *temp_v0;

    var_s1 = 0;
    do {
        temp_v0 = func_800A03B8((s16)var_s1);
        if (temp_v0->unk1 != 0) {
            temp_a0 = temp_v0->unk458;
            if (temp_a0 != -1) {
                func_800798C0(temp_a0);
                temp_v0->unk458 = -1;
            }
            temp_a0_2 = temp_v0->unk45C;
            if (temp_a0_2 != -1) {
                func_800798C0(temp_a0_2);
                temp_v0->unk45C = -1;
            }
            temp_a0_3 = temp_v0->unk4F0;
            if (temp_a0_3 != -1) {
                func_800798C0(temp_a0_3);
                temp_v0->unk4F0 = -1;
            }
        }
        var_s1 += 1;
    } while (var_s1 < 0x14);
}
