#include "shared/func_800a7d10.h"
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







/* Transforms a vector by the supplied matrix and translation. */
void func_800A7D10(func_800A7D10_S3 *arg0, func_800A7D10_S1 *arg1, func_800A7D10_S1 *arg2) {
    arg2->unk0 = (f32) ((arg1->unk0 * arg0->unk0) + (arg1->unk4 * arg0->unk10) + (arg1->unk8 * arg0->unk20) + arg0->unk30);
    arg2->unk4 = (f32) ((arg1->unk0 * arg0->unk4) + (arg1->unk4 * arg0->unk14) + (arg1->unk8 * arg0->unk24) + arg0->unk34);
    arg2->unk8 = (f32) ((arg1->unk0 * arg0->unk8) + (arg1->unk4 * arg0->unk18) + (arg1->unk8 * arg0->unk28) + arg0->unk38);
}
