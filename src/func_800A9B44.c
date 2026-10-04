#include "span_1000/code_800A8940.h"
#include "types.h"

/* func_800A9B44 -- sums the bytes from offset 4 to 0xFF of a block. */

int func_800A9B44(unsigned char *arg0) {
    int sum = 0;
    int i;
    for (i = 4; i < 0x100; i++) {
        sum += arg0[i];
    }
    return sum;
}

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
s32 func_80116A10();                 /* extern */
s32 func_80119240(); /* extern */
s32 func_801193E0(); /* extern */
extern s32 D_802DF3A0;
extern s32 D_802DF5B0;
extern s32 D_802E17A0;

/* Selects a record, runs its operation between begin and end notifications, and returns the result. */
s32 func_800A9B70(s32 arg0, s32 arg1) {
    s32 temp_s0;

    func_80119240(&D_802DF5B0, &D_802E17A0, 1);
    temp_s0 = func_80116A10((s8 *)(&D_802DF3A0) + ((arg0 - 1) * 0x68), arg1);
    func_801193E0(&D_802DF5B0, &D_802E17A0, 0);
    return temp_s0;
}
