#include "common/types.h"
#include "span_1000/code_800A51E8.h"
#include "types.h"

struct FuncA51E8State;
typedef struct FuncA51E8State FuncA51E8State;



struct FuncA51E8State {
    char pad0[0x1A6];
    u8 unk1A6;
    char pad1A7[0x218 - 0x1A7];
    s32 unk218;
    s32 unk21C;
    char pad220[0x260 - 0x220];
    s32 unk260;
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
s32 func_800796F0();            /* extern */
const f32 D_80072DE4 = 30.0f;
extern s16 D_801260A8[];
extern s32 D_801B4AA8;



void func_800A51E8(FuncA51E8State *arg0, s32 arg1, f32 arg2) {
    s32 temp_a0;
    void *temp_s2;
    f32 product;
    s32 current;

    if ((arg0->unk1A6 == 0) && ((temp_s2 = (void *) ((arg1 << 2) + (u32) arg0), temp_a0 = ((FuncA51E8State *) temp_s2)->unk260, (temp_a0 == 0)) || ((temp_a0 + D_801260A8[arg1]) < D_801B4AA8))) {
        if (arg1 == 1) {
            func_800796F0(0x2C, 0);
        }
        product = arg2 * D_80072DE4;
        current = D_801B4AA8;
        arg0->unk218 = arg1;
        arg0->unk21C = current + (s32) product;
        ((FuncA51E8State *) temp_s2)->unk260 = current;
    }
}
