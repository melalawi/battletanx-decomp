#include "common/types.h"
#include "span_1000/code_8010A8A8.h"
#include "types.h"

struct func_8010DCD0_S1;
typedef struct func_8010DCD0_S1 func_8010DCD0_S1;
typedef struct func_8010DCD0_S2 func_8010DCD0_S2;
typedef struct func_8010DCD0_S3 func_8010DCD0_S3;

struct func_8010DCD0_S2;

struct func_8010DCD0_S3;







struct func_8010DCD0_S1 {
    char pad0[0x18];
    s32 unk18;
    s32 unk1C;
    char pad1C[0x24 - 0x1C - sizeof(s32)];
    s32 unk24;
};
struct func_8010DCD0_S2 {
    char pad0[0x8];
    s32 unk8;
};
struct func_8010DCD0_S3 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
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
s32 func_8008B89C();                 /* extern */









/* Checks the pending action and updates its result fields when the timer allows it. */
void func_8010DCD0(func_8010DCD0_S1 *arg0, func_8010DCD0_S2 *arg1, s32 arg2, func_8010DCD0_S3 *arg3) {
    s32 action;
    s32 result;

    if (arg0->unk1C == 0) {
        action = arg1->unk8;
        switch (action) {
        case 0:
            if ((arg0->unk18 + 0x3C) < D_801B4AA8) {
                func_8008B89C(arg0);
                arg3->unk0 = 8;
                arg3->unk4 = 0x1E;
                arg3->unk8 = arg0->unk24;
                return;
            }
            result = 1;
            break;
        case 29:
            func_8008B89C(arg0);
            return;
        default:
            result = 1;
            break;
        }
        arg3->unk0 = result;
    }
}
