#include "shared/func_800916b8.h"



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

void func_800916B8(void *arg0, void *arg1, s32 arg2, void *arg3, void *arg4) {
    s32 temp_v0;
    s32 local_arr[1];

    local_arr[0] = (s32) arg1;
    if (arg2 == 0) {
        if ((((struct Func_800916B8_View0 *)arg0)->field_20 == 0) && (((struct Func_800916B8_View1 *)arg1)->field_8 == 0) && ((func_8009FBE4(((struct Func_800916B8_View1 *)arg1)->field_c) & 0xFF) != ((struct Func_800916B8_View0 *)arg0)->field_2c) && (func_800E3460(((struct Func_800916B8_View1 *)arg1)->field_c) == 0)) {
            ((struct Func_800916B8_View2 *)arg4)->field_0 = 3;
            temp_v0 = (s32) ((struct Func_800916B8_View0 *)arg0)->field_18;
            ((struct Func_800916B8_View2 *)arg4)->field_4 = temp_v0;
            ((struct Func_800916B8_View0 *)arg0)->field_20 = 1U;
            func_8008B89C(arg0);
            return;
        }
        ((struct Func_800916B8_View2 *)arg4)->field_0 = 1;
    }
}
