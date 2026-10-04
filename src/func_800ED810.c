#include "span_1000/code_800EC700.h"
#include "types.h"

struct func_800ED810_S1;
typedef struct func_800ED810_S1 func_800ED810_S1;
typedef struct func_800ED810_S2 func_800ED810_S2;

struct func_800ED810_S2;





struct func_800ED810_S1 {
    char pad0[0xC];
    f32 unkC;
    char padC[0x14 - 0xC - sizeof(f32)];
    f32 unk14;
    char pad14[0x1C - 0x14 - sizeof(f32)];
    u8 unk1C;
};
struct func_800ED810_S2 {
    s8 unk0;
    char pad0[0x4 - 0x0 - sizeof(s8)];
    f32 unk4;
    f32 unk8;
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
s32 func_800ECE4C();             /* extern */
s32 func_800ED380();   /* extern */
s32 func_800ED5C8();                     





/* extern */

void func_800ED810(func_800ED810_S1 *arg0, s32 arg1, u32 arg2, s32 arg3, func_800ED810_S2 *arg4) {
    switch (arg2) {                                 /* irregular */
    case 0:
        func_800ECE4C(arg0, arg1, arg3, arg4);
        return;
    case 2:
        if (arg0->unk1C == 0) {
            arg4->unk0 = 1;
            arg4->unk8 = (f32) arg0->unkC;
            arg4->unk4 = (f32) arg0->unk14;
            return;
        }
        return;
    case 3:
        func_800ED380(arg0, 0, arg3, 0);
        return;
    case 7:
        func_800ED5C8(arg0, arg1, arg3);
        break;
    }
}
