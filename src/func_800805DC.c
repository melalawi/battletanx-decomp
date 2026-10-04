#include "span_1000/code_8007EB64.h"
#include "types.h"

struct func_800805DC_S1;
typedef struct func_800805DC_S1 func_800805DC_S1;



struct func_800805DC_S1 {
    char pad0[0x2680];
    s8 unk2680;
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
s32 func_80110C00();          /* extern */
extern s32 D_801B6C10;
extern s32 D_801B6C14;
extern s32 D_801B6C18;
extern s32 D_801B6C1C;
extern s32 D_801C0840;
extern s16 D_80125800;
extern u8 D_80125802;




void func_800805DC(void) {
    D_801B6C10 = 0;
    D_801B6C14 = 0;
    D_801B6C18 = 0;
    D_801B6C1C = 0;
    func_80110C00(&D_801C0840, 0x380);
    func_80110C00(&((func_800805DC_S1 *)(&D_801C0840))->unk2680, 0x80);
    D_80125800 = 0;
    D_80125802 = (D_80125802 + 1) % 3;
}
