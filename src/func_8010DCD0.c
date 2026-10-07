#include "span_1000/code_8010BFDC.h"
#include "types.h"




















#include "types.h"


s32 func_8008B89C();                 /* extern */









/* Checks the pending action and updates its result fields when the timer allows it. */
void func_8010DCD0(func_8010DCD0_S1_Shared8010DCD0 *arg0, func_8010DCD0_S2_Shared8010DCD0 *arg1, s32 arg2, func_8010DCD0_S3_Shared8010DCD0 *arg3) {
    s32 action;
    s32 result;

    if (arg0->unk1C == 0) {
        action = arg1->unk8;
        switch (action) {
        case 0:
            if ((arg0->unk18 + 0x3C) < D_801B4AA8) {
                func_8008B89C(arg0);
                arg3->unk0 = 8;
                arg3->unk4 = 0x1E;
                arg3->unk8 = arg0->unk24;
                return;
            }
            result = 1;
            break;
        case 29:
            func_8008B89C(arg0);
            return;
        default:
            result = 1;
            break;
        }
        arg3->unk0 = result;
    }
}
