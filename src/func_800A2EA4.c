#include "span_1000/code_800A27D0.h"
#include "types.h"

struct func_800A2EA4_S1;
typedef struct func_800A2EA4_S1 func_800A2EA4_S1;
typedef struct func_800A2EA4_S2 func_800A2EA4_S2;

struct func_800A2EA4_S2;





struct func_800A2EA4_S1 {
    s8 unk0;
    char pad0[0x4 - 0x0 - sizeof(s8)];
    f32 unk4;
    f32 unk8;
};
struct func_800A2EA4_S2 {
    char pad0[0x1C];
    f32 unk1C;
    f32 unk20;
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
s32 func_800A27D0();             /* extern */
s32 func_800A2A44();   /* extern */
s32 func_800A2C38();                     





/* extern */

void func_800A2EA4(func_800A2EA4_S2 *arg0, s32 arg1, u32 arg2, s32 arg3, func_800A2EA4_S1 *arg4) {
    switch (arg2) {                                 /* irregular */
    case 0:
        func_800A27D0(arg0, arg1, arg3, arg4);
        return;
    case 2:
        arg4->unk0 = 1;
        arg4->unk8 = (f32) arg0->unk20;
        arg4->unk4 = (f32) arg0->unk1C;
        return;
    case 3:
        func_800A2A44(arg0, 0, arg3, 0);
        break;
        return;
    case 7:
        func_800A2C38(arg0, arg1, arg3);
        return;
    }
}
