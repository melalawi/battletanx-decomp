#include "span_1000/code_800A7ABC.h"
#include "types.h"

struct func_800A7D10_S1;
typedef struct func_800A7D10_S1 func_800A7D10_S1;
typedef struct func_800A7D10_S3 func_800A7D10_S3;

struct func_800A7D10_S3;





struct func_800A7D10_S1 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
};
struct func_800A7D10_S3 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    char pad8[0x10 - 0x8 - sizeof(f32)];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    char pad18[0x20 - 0x18 - sizeof(f32)];
    f32 unk20;
    f32 unk24;
    f32 unk28;
    char pad28[0x30 - 0x28 - sizeof(f32)];
    f32 unk30;
    f32 unk34;
    f32 unk38;
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







/* Transforms a vector by the supplied matrix and translation. */
void func_800A7D10(func_800A7D10_S3 *arg0, func_800A7D10_S1 *arg1, func_800A7D10_S1 *arg2) {
    arg2->unk0 = (f32) ((arg1->unk0 * arg0->unk0) + (arg1->unk4 * arg0->unk10) + (arg1->unk8 * arg0->unk20) + arg0->unk30);
    arg2->unk4 = (f32) ((arg1->unk0 * arg0->unk4) + (arg1->unk4 * arg0->unk14) + (arg1->unk8 * arg0->unk24) + arg0->unk34);
    arg2->unk8 = (f32) ((arg1->unk0 * arg0->unk8) + (arg1->unk4 * arg0->unk18) + (arg1->unk8 * arg0->unk28) + arg0->unk38);
}
