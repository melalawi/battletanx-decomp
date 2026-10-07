#include "span_1000/code_80077930.h"
#include "types.h"














#include "types.h"

s32 func_800A7650();
s32 func_800A7744();
s32 func_800EC7A8();




/* note: Dispatches by the object's state to the appropriate update routine. */
void func_80078D90(func_80078D90_S1_Shared80078D90 *arg0, s32 arg1, s32 arg2, func_80078D90_S2_Shared80078D90 *arg3, s32 arg4) {
    u8 temp_v1;
    s32 state;
    if (arg2 == 1) {
        temp_v1 = arg0->unkC;
        state = temp_v1;
        if (temp_v1 != arg2) {
            if (state < 2) {
                if (temp_v1 != 0) {
                    return;
                }
            } else if (state >= 4) {
                return;
            }
            func_800A7650(arg4);
            func_800A7744(arg4, arg0->unk14, 0, arg0->unk10, (s32) arg0->unkE);
        } else {
            func_800EC7A8(arg4, arg3->unk4);
        }
    }
}
