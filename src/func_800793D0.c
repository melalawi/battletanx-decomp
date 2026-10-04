#include "span_1000/code_80077620.h"
#include "types.h"

struct func_800793D0_S1;
typedef struct func_800793D0_S1 func_800793D0_S1;
typedef struct func_800793D0_S2 func_800793D0_S2;

struct func_800793D0_S2;





struct func_800793D0_S1 {
    char pad0[0x1F4];
    u16 unk1F4;
    char pad1F4[0x1F8 - 0x1F4 - sizeof(u16)];
    s32 unk1F8;
    s32 unk1FC;
    char pad1FC[0x204 - 0x1FC - sizeof(s32)];
    struct func_800793D0_S2 * unk204;
};
struct func_800793D0_S2 {
    char pad0[0x40];
    s32 unk40;
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
s32 func_800794C8();                      /* extern */
s32 func_80079530();                      /* extern */
s32 func_8007F070();                /* extern */
s32 func_8007F204();                         





/* extern */

void func_800793D0(func_800793D0_S1 *arg0) {
    u16 temp_v1;

    if (func_8007F204(1) == 0) {
        func_8007F070(1, arg0->unk204->unk40);
        func_8007F070(2, 0);
        if ((arg0->unk1F4 == 0) && (arg0->unk1FC == 1)) {
            func_800794C8(arg0);
        } else {
            temp_v1 = arg0->unk1F4;
            if (temp_v1 & 4) {
                arg0->unk1F4 = (u16) (temp_v1 | 8);
            } else {
                arg0->unk204 = NULL;
            }
        }
    } else {
        arg0->unk1F8 = 1;
    }
    func_80079530(arg0);
}
