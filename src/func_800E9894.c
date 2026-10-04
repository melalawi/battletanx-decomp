#include "common/types.h"
#include "span_1000/code_800E9538.h"
#include "types.h"

struct func_800E9894_S1;
typedef struct func_800E9894_S1 func_800E9894_S1;
typedef struct func_800E9894_S2 func_800E9894_S2;
typedef struct func_800E9894_S3 func_800E9894_S3;
typedef struct func_800E9894_S4 func_800E9894_S4;

struct func_800E9894_S2;

struct func_800E9894_S3;

struct func_800E9894_S4;









struct func_800E9894_S1 {
    void * unk0;
    void * unk4;
    struct func_800E9894_S3 * unk8;
    void * unkC;
    void * unk10;
    s32 unk14;
    s16 unk18;
    s16 unk1A;
    u8 unk1C;
    char pad1C[0x40 - 0x1C - sizeof(u8)];
    s32 unk40;
    s32 unk44;
};
struct func_800E9894_S2 {
    char pad0[0x4];
    u8 unk4;
};
struct func_800E9894_S3 {
    char pad0[0x4];
    u8 unk4;
    char pad5[0x9C - 0x5];
    u8 unk9C;
    char pad9D[0xCC - 0x9D];
    u8 unkCC;
};
struct func_800E9894_S4 {
    char pad0[0x1AE];
    u8 unk1AE;
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
void *func_800A6688();                            /* extern */











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
