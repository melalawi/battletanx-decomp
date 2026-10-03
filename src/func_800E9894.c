#include "shared/func_800e9894.h"
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
void *func_800A6688();                            /* extern */
extern s32 D_8033A980;










/* Initializes an object from the selected resource and its metadata. */
void func_800E9894(func_800E9894_S1 *arg0, s16 arg1) {
    s16 temp_a1;
    u8 temp_v1;
    func_800E9894_S3 *temp_a0;
    func_800E9894_S2 *temp_v0;
    func_800E9894_S4 *temp_v0_2;

    temp_a1 = arg1 & 0xFF;
    arg0->unk14 = 2;
    arg0->unk18 = temp_a1;
    temp_v0 = func_800A03B8(arg1, temp_a1);
    arg0->unk8 = temp_v0;
    arg0->unk1A = (s16) temp_v0->unk4;
    temp_v0_2 = func_800A6688(arg0->unk8->unk4);
    arg0->unk4 = temp_v0_2;
    temp_v1 = temp_v0_2->unk1AE;
    temp_a0 = arg0->unk8;
    arg0->unk40 = 0;
    arg0->unk44 = 0;
    arg0->unk1C = temp_v1;
    arg0->unk0 = (void *) ((s8 *)(&D_8033A980) + ((temp_v1 & 0xFF) * 0x52));
    arg0->unkC = (void *)&temp_a0->unk9C;
    arg0->unk10 = (void *)&temp_a0->unkCC;
}
