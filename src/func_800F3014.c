#include "shared/func_800f3014.h"

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

void func_800F3014(s8 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, s32 arg6, s32 arg7) {
    void *temp_v0;

    temp_v0 = func_8008AD10(1, 0x20, 0x20);
    if (temp_v0 != NULL) {
        ((struct Func_800F3014_View0 *)temp_v0)->field_c = arg0;
        ((struct Func_800F3014_View0 *)temp_v0)->field_d = arg1;
        ((struct Func_800F3014_View0 *)temp_v0)->field_e = arg2;
        ((struct Func_800F3014_View0 *)temp_v0)->field_f = arg3;
        ((struct Func_800F3014_View0 *)temp_v0)->field_10 = arg4;
        ((struct Func_800F3014_View0 *)temp_v0)->field_11 = arg5;
        ((struct Func_800F3014_View0 *)temp_v0)->field_14 = arg6;
        ((struct Func_800F3014_View0 *)temp_v0)->field_18 = 0;
        ((struct Func_800F3014_View0 *)temp_v0)->field_1c = arg7;
    }
}
