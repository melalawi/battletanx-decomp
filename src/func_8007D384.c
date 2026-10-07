#include "span_1000/code_8007C700.h"
#include "types.h"














#include "types.h"


void *func_800A6688();                       /* extern */
extern s32 D_801B4AAC;





extern func_8007D384_S1_Shared8007D384 *D_801B4ABC;

s32 func_8007D384(s32 *arg0) {
    s32 temp_a0;
    func_8007D384_S2_Shared8007D384 *temp_v0;

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
