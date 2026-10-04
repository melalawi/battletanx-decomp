#include "span_1000/code_800A9FC4.h"
#include "types.h"

struct func_800AA280_S1;
typedef struct func_800AA280_S1 func_800AA280_S1;



struct func_800AA280_S1 {
    void * unk0;
    char pad0[0x14 - 0x0 - sizeof(void*)];
    u16 unk14;
};

/* Original packets use the classic F3DEX command encoding. */
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
void *func_8007F060();                              







/* extern */

/* Emits two display-list commands when the display-list state is ready. */
void func_800AA280(s32 arg0, s32 arg1, s32 arg2) {
    Gfx *temp_a0;
    func_800AA280_S1 *temp_v0;
    Gfx *temp_v1;

    temp_v0 = func_8007F060();
    if (temp_v0->unk14 == 0) {
        temp_v1 = temp_v0->unk0;
        temp_v0->unk0 = (void *)(temp_v1 + 1);
        gSPClearGeometryMode(temp_v1, G_CULL_BOTH);
        temp_a0 = temp_v0->unk0;
        temp_v0->unk0 = (void *)(temp_a0 + 1);
        temp_a0->words.w0 = 0xBF000000; /* GBI_RAW: unsupported opcode 0xBF; classic triangle builder absent from installed SDK. */
        temp_a0->words.w1 = (s32)((((arg0 * 2) & 0xFE) << 16) | ((arg1 << 9) & 0xFE00) | ((arg2 * 2) & 0xFE)); /* GBI_RAW: unsupported opcode 0xBF; classic triangle builder absent from installed SDK. */
    }
}
