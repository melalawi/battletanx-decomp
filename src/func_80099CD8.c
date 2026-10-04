#include "span_1000/code_80097038.h"
#include "types.h"

struct Func_80099CD8_View0;


struct Func_80099CD8_View0 {
    char pad_0[0x3b4];
    f32 field_3b4;
    char pad_3b8[0xac];
    u8 field_464;
};

#include "types.h"







#include "types.h"
/* checks field conditions and calls handler with scaled float parameter */
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
s32 func_800796F0();                /* extern */
s32 func_800799D0();                    /* extern */
s32 func_800E3470();                                /* extern */
const f64 D_800723B0 = 0.3;
const f32 D_800723B8 = 0.5f;
const f32 D_800723BC = 28672.0f;

void func_80099CD8(void *arg0, s32 arg1) {
    s32 temp_a0;

    if ((((struct Func_80099CD8_View0 *)arg0)->field_464 == 0) && (D_800723B0 < (f64) ((struct Func_80099CD8_View0 *)arg0)->field_3b4) && (func_800E3470() != 0)) {
        temp_a0 = func_800796F0(arg1, 0);
        if (((struct Func_80099CD8_View0 *)arg0)->field_3b4 < D_800723B8) {
            func_800799D0(temp_a0, (s16) (s32) (2.0f * ((struct Func_80099CD8_View0 *)arg0)->field_3b4 * D_800723BC));
        }
        ((struct Func_80099CD8_View0 *)arg0)->field_464 = 0x20U;
    }
}
