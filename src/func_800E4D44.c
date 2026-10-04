#include "span_1000/code_800E3F90.h"
#include "types.h"

struct Func_800E4D44_Lists;


struct Func_800E4D44_Lists {
    s16 initial_ids[3];
    u16 initial_count;
    s16 extra_ids[15];
    u16 extra_count;
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
s32 func_800A03B8();                         /* extern */
s32 func_800A6688();                             /* extern */

void func_800E4D44(void *arg0, s16 arg1) {
    s16 temp_a0;
    s32 temp_v0;
    s32 var_s2;
    s32 var_v0;

    temp_v0 = func_800A6688(arg1 & 0xFFFF);
    ((struct Func_800E4D44_Lists *)arg0)->initial_ids[((struct Func_800E4D44_Lists *)arg0)->initial_count] = arg1;
    ((struct Func_800E4D44_Lists *)arg0)->initial_count = (u16) (((struct Func_800E4D44_Lists *)arg0)->initial_count + 1);
    for (var_s2 = 0; (u32) (var_s2 & 0xFFFF) < 5U; var_s2++) {
        var_v0 = var_s2 & 0xFFFF;
        temp_a0 = ((s16 *)temp_v0)[var_v0];
        func_800A03B8(temp_a0);
        ((struct Func_800E4D44_Lists *)arg0)->extra_ids[((struct Func_800E4D44_Lists *)arg0)->extra_count] = temp_a0;
        ((struct Func_800E4D44_Lists *)arg0)->extra_count = (u16) (((struct Func_800E4D44_Lists *)arg0)->extra_count + 1);
    }
}
