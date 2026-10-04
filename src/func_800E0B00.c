#include "common/types.h"
#include "span_1000/code_800DE664.h"
#include "types.h"

struct Func_800E0B00_View0;
struct Func_800E0B00_View1;




struct Func_800E0B00_View0 {
    char pad_0[0x8];
    u16 field_8;
    char pad_a[0x2];
    s32 field_c;
};
struct Func_800E0B00_View1 {
    f32 field_0;
    f32 field_4;
};

#include "types.h"














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
s32 func_800E1818();           /* extern */
const f32 D_80074428 = 2.0f;
extern void *D_80135834;

void func_800E0B00(s32 arg0, void *arg1) {
    u16 sp10;
    u16 sp12;
    void *var_a1;
    void *var_v1;

    func_800E1818(arg0 & 0xFFFF, &sp10, &sp12);
    var_a1 = NULL;
    if ((sp10 < (u16) ((struct Func_800E0B00_View0 *)D_80135834)->field_8) && (sp10 != 0)) {
        var_a1 = ((struct Func_800E0B00_View0 *)D_80135834)->field_c + (sp10 * 8);
    }
    if (sp12 >= (u16) ((struct Func_800E0B00_View0 *)D_80135834)->field_8) {
        var_v1 = NULL;
    } else if (sp12 == 0) {
        var_v1 = NULL;
    } else {
        var_v1 = ((struct Func_800E0B00_View0 *)D_80135834)->field_c + (sp12 * 8);
    }
    ((struct Func_800E0B00_View1 *)arg1)->field_4 = (f32) ((((struct Func_800E0B00_View1 *)var_a1)->field_4 + ((struct Func_800E0B00_View1 *)var_v1)->field_4) / D_80074428);
    ((struct Func_800E0B00_View1 *)arg1)->field_0 = (f32) ((((struct Func_800E0B00_View1 *)var_a1)->field_0 + ((struct Func_800E0B00_View1 *)var_v1)->field_0) / D_80074428);
}
