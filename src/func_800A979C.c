#include "shared/func_800a979c.h"

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
s32 func_80116110(); /* extern */
s32 func_80119240(); /* extern */
s32 func_801193E0(); /* extern */
extern s32 D_802DF3A0;
extern s32 D_802DF5B0;
extern s32 D_802E17A0;

s32 func_800A979C(s32 arg0, void *arg1) {
    s32 temp_s0;

    func_80119240(&D_802DF5B0, &D_802E17A0, 1);
    temp_s0 = func_80116110((s8 *)(&D_802DF3A0) + ((arg0 - 1) * 0x68), ((struct Func_800A979C_View0 *)arg1)->field_8, ((struct Func_800A979C_View0 *)arg1)->field_4, ((struct Func_800A979C_View0 *)arg1)->field_e, ((struct Func_800A979C_View0 *)arg1)->field_a);
    func_801193E0(&D_802DF5B0, &D_802E17A0, 0);
    return temp_s0;
}
