#include "abi.h"
#include "span_1000/code_8007EBA0.h"
#include "types.h"


























/* The target command is classic G_MTX: opcode 0x01, 64-byte matrix,
 * eight flag bits at 16. Select the existing classic SDK builder. */
#undef F3DEX_GBI_2

#include "n64sdk.h"
#include "gbi.h"
#include "types.h"


s32 func_801146A0();                /* extern */
extern void *D_801257D0[4]; 









/* const */

s32 func_8007EE48(s32 unused, s32 arg1) {
    s32 var_a2 = 0;
    u32 temp_a1;
    Gfx *temp_a0;
    func_8007ECE8_S1_Shared8007ECE8 *temp_s0;

    temp_s0 = *D_801257D0;
    do {
        if ((u32) (temp_a1 = temp_s0->unkE8.v0) >= (u32) (((Func8007EC38Catalog_Shared8007EC38 *) ((temp_s0->unkD0 * sizeof(Func8007EC38Entry_Shared8007EC38)) + (u32)temp_s0))->entries[0].threshold + 0xC000)) {
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
