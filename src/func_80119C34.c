#include "shared/func_80119c34.h"



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
s32 func_80119B60();            /* extern */
s32 func_80119BB4();                 /* extern */

void func_80119C34(void *arg0, void *arg1) {
    s32 temp_s1;
    s32 var_s0;
    void *var_v0;

    var_v0 = arg1;
    do {
        temp_s1 = ((struct Func_80119C34_View0 *)var_v0)->field_c;
        var_v0 = (void *)((s32 *)var_v0 + 1);
    } while (temp_s1 == 0);
    var_s0 = 0;
    if ((s32) ((struct Func_80119C34_View1 *)arg0)->field_34 > 0) {
        do {
            func_80119BB4(arg0, var_s0);
            func_80119B60(arg0, temp_s1, var_s0);
            var_s0 += 1;
        } while (var_s0 < (s32) ((struct Func_80119C34_View1 *)arg0)->field_34);
    }
    if (((struct Func_80119C34_View2 *)arg1)->field_8 != 0) {
        func_80119BB4(arg0, var_s0);
        func_80119B60(arg0, ((struct Func_80119C34_View2 *)arg1)->field_8, 9);
    }
}
