#include "span_1000/code_8007EBA0.h"
#include "types.h"

struct Func8007ECE8Catalog;
typedef struct Func8007ECE8Catalog Func8007ECE8Catalog;
typedef struct Func8007ECE8Entry Func8007ECE8Entry;
typedef struct func_8007ECE8_S1 func_8007ECE8_S1;
typedef union func_8007ECE8_S1_UE8 func_8007ECE8_S1_UE8;

struct Func8007ECE8Entry;

struct func_8007ECE8_S1;

union func_8007ECE8_S1_UE8;









struct Func8007ECE8Entry {
    s32 threshold;
    char pad4[0x14];
};
union func_8007ECE8_S1_UE8 {
    u32 v0;
    s32 v1;
};
struct Func8007ECE8Catalog {
    char pad0[0xA4];
    Func8007ECE8Entry entries[1];
};
struct func_8007ECE8_S1 {
    char pad0[0xD0];
    u16 unkD0;
    char padD0[0xDC - 0xD0 - sizeof(u16)];
    void * unkDC;
    char padDC[0xE8 - 0xDC - sizeof(void*)];
    func_8007ECE8_S1_UE8 unkE8;
};

/* The target command is classic G_MTX: opcode 0x01, 64-byte matrix,
 * eight flag bits at 16. Select the existing classic SDK builder. */
#undef F3DEX_GBI_2
#define F3DEX_GBI
#include "n64sdk.h"
#include "gbi.h"
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
s32 func_801146A0();                /* extern */
extern void *D_801257D0[4]; 









/* const */

s32 func_8007ECE8(s32 unused, s32 arg1) {
    s32 var_a2 = 0;
    u32 temp_a1;
    Gfx *temp_a0;
    func_8007ECE8_S1 *temp_s0;

    temp_s0 = *D_801257D0;
    do {
        if ((u32) (temp_a1 = temp_s0->unkE8.v0) >= (u32) (((Func8007ECE8Catalog *) ((temp_s0->unkD0 * sizeof(Func8007ECE8Entry)) + (u32)temp_s0))->entries[0].threshold + 0xC000)) {
            break;
        }
        func_801146A0(unused, temp_a1, var_a2);
        temp_a0 = temp_s0->unkDC;
        temp_s0->unkDC = (void *)(temp_a0 + 1);
        gSPMatrix(temp_a0, temp_s0->unkE8.v1 - 0x80000000U, arg1);
        var_a2 = temp_s0->unkE8.v1;
        temp_s0->unkE8.v1 = (s32) (var_a2 + 0x40);
    } while (0);
    return var_a2;
}
