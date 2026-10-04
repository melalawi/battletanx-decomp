#include "span_1000/code_800E21E4.h"
#include "types.h"

struct func_800E34B4_S1;
typedef struct func_800E34B4_S1 func_800E34B4_S1;
typedef union func_800E34B4_S1_U8 func_800E34B4_S1_U8;
typedef struct func_800E34B4_S2 func_800E34B4_S2;

union func_800E34B4_S1_U8;

struct func_800E34B4_S2;







union func_800E34B4_S1_U8 {
    u8 v0;
    f32 v1;
};
struct func_800E34B4_S2 {
    char pad0[0x24];
    f32 unk24;
    char pad24[0x4];
    f32 unk2C;
};
struct func_800E34B4_S1 {
    s32 unk0;
    void * unk4;
    func_800E34B4_S1_U8 unk8;
    f32 unkC;
    void * unk10;
    s32 unk14;
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
void *func_800A03B8();                      /* extern */
s32 func_800E52A0();                        






/* extern */

void func_800E34B4(func_800E34B4_S1 *arg0, s16 arg1, s16 arg2) {
    func_800E34B4_S2 *temp_v0;
    f32 *ordered_value;

    if (arg2 != 0xFF) {
        func_800A03B8(arg1);
        (void)(arg2 << 0x10);
        temp_v0 = func_800A03B8(arg2);
        arg0->unk10 = temp_v0;
        arg0->unk14 = func_800E52A0(arg1, arg2);
        arg0->unkC = (f32) temp_v0->unk24;
        ordered_value = &arg0->unk8.v1;
        *ordered_value = (f32) temp_v0->unk2C;
        arg0->unk4 = (void *)&arg0->unk8.v0;
        arg0->unk0 = 1;
        return;
    }
    arg0->unk0 = 0;
    arg0->unk4 = NULL;
}
