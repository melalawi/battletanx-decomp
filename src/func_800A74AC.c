#include "shared/func_800a74ac.h"
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
void *func_800A6688();                            /* extern */
s32 func_800A6E30();                  













/* extern */

/* Releases linked resources when the selected object matches the active one. */
void func_800A74AC(func_800A74AC_S4 *arg0, func_800A74AC_S1 *arg1, s32 arg2) {
    func_800A74AC_S3 *temp_s0;
    void *temp_s0_2;
    func_800A74AC_S2 *temp_s1;
    func_800A74AC_S6 *var_a0;

    if ((arg2 == 0) && (arg1->unk8 == 0)) {
        temp_s1 = arg1->unkC;
        temp_s0 = func_800A6688(temp_s1->unk4);
        if (temp_s0->unk1AE == (((func_800A74AC_S3 *)(func_800A6688(arg0->unkC)))->unk1AE)) {
            var_a0 = temp_s1->unk98;
            if (var_a0 != NULL) {
                do {
                    temp_s0_2 = var_a0->unk2C;
                    func_800A6E30(var_a0, arg0->unkC);
                    var_a0 = temp_s0_2;
                } while (var_a0 != NULL);
            }
            temp_s1->unk98 = NULL;
        }
    }
}
