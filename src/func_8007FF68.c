#include "span_1000/code_8007EB64.h"
#include "types.h"

struct Func_8007FF68_View0;
struct Func_8007FF68_View1;




struct Func_8007FF68_View0 {
    char pad_0[0x88];
    s32 field_88;
};
struct Func_8007FF68_View1 {
    char pad_0[0x140];
    s32 field_140;
};



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
s32 func_8007AAA0();                                /* extern */
s32 func_80081A30();                                /* extern */
s32 func_800821C0();                                /* extern */
s32 func_8008228C();                         /* extern */
s32 func_80083394();                         /* extern */
s32 func_80083F04();                         /* extern */
void *func_800A424C();                        /* extern */
void *func_800A6688();                           /* extern */

/* Initialize resources and game objects. */
void func_8007FF68(void) {
    s32 temp_v0;
    s32 temp_v0_4;
    s32 var_s1;
    void *temp_v0_2;
    void *temp_v0_3;

    temp_v0 = func_8007AAA0();
    var_s1 = 0;
    if (temp_v0 > 0) {
        do {
            temp_v0_2 = func_800A6688(var_s1 & 0xFFFF);
            temp_v0_3 = func_800A424C(temp_v0_2);
            var_s1 += 1;
            ((struct Func_8007FF68_View0 *)temp_v0_3)->field_88 = 0;
            ((struct Func_8007FF68_View1 *)temp_v0_2)->field_140 = 0;
        } while ((var_s1 & 0xFFFF) < temp_v0);
    }
    temp_v0_4 = func_800821C0();
    if (temp_v0_4 != 0) {
        func_8008228C(temp_v0_4);
        if (func_80081A30() & 0xFF) {
            func_80083394(temp_v0_4);
            return;
        }
        func_80083F04(temp_v0_4);
    }
}
