#include "span_1000/code_8007C6D8.h"
#include "types.h"

struct func_8007D384_S1;
typedef struct func_8007D384_S1 func_8007D384_S1;
typedef struct func_8007D384_S2 func_8007D384_S2;

struct func_8007D384_S2;





struct func_8007D384_S1 {
    char pad0[0x218];
    s32 unk218;
};
struct func_8007D384_S2 {
    char pad0[0x10];
    s32 unk10;
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
void *func_800A6688();                       /* extern */
extern s32 D_801B4AAC;





extern func_8007D384_S1 *D_801B4ABC;

s32 func_8007D384(s32 *arg0) {
    s32 temp_a0;
    func_8007D384_S2 *temp_v0;

    temp_v0 = func_800A6688(0);
    temp_a0 = D_801B4ABC->unk218 * 0x1E;
    *arg0 = temp_a0;
    if (temp_v0->unk10 != 0) {
        if (D_801B4AAC < temp_a0) {
            return (((temp_a0 - D_801B4AAC) / 30) * 0x64) + 0xFA0;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}
