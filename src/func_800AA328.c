#include "abi.h"
#include "span_1000/code_800A9FC4.h"
#include "types.h"








/* Original packets use the classic F3DEX command encoding. */
#undef F3DEX_GBI_2

#include "n64sdk.h"
#include "gbi.h"
#include "types.h"


void *func_8007F060();                              







/* extern */

/* Emits two display-list commands through the secondary display-list pointer when ready. */
void func_800AA328(s32 arg0, s32 arg1, s32 arg2) {
    Gfx *temp_a0;
    func_800AA328_S1_Shared800AA328 *temp_v0;
    Gfx *temp_v1;

    temp_v0 = func_8007F060();
    if (temp_v0->unk14 == 0) {
        temp_v1 = temp_v0->unk4;
        temp_v0->unk4 = (void *)(temp_v1 + 1);
        gSPClearGeometryMode(temp_v1, G_CULL_BOTH);
        temp_a0 = temp_v0->unk4;
        temp_v0->unk4 = (void *)(temp_a0 + 1);
        temp_a0->words.w0 = 0xBF000000; /* GBI_RAW: unsupported opcode 0xBF; classic triangle builder absent from installed SDK. */
        temp_a0->words.w1 = (s32)((((arg0 * 2) & 0xFE) << 16) | ((arg1 << 9) & 0xFE00) | ((arg2 * 2) & 0xFE)); /* GBI_RAW: unsupported opcode 0xBF; classic triangle builder absent from installed SDK. */
    }
}
