#include "span_1000/code_80078E30.h"
#include "types.h"














#include "types.h"


                      /* extern */
s32 func_80079530();                      /* extern */
s32 func_8007F070();                /* extern */
s32 func_8007F204();                         





/* extern */

void func_800793D0(func_800793D0_S1_Shared800793D0 *arg0) {
    u16 temp_v1;

    if (func_8007F204(1) == 0) {
        func_8007F070(1, arg0->unk204->unk40);
        func_8007F070(2, 0);
        if ((arg0->unk1F4 == 0) && (arg0->unk1FC == 1)) {
            func_800794C8(arg0);
        } else {
            temp_v1 = arg0->unk1F4;
            if (temp_v1 & 4) {
                arg0->unk1F4 = (u16) (temp_v1 | 8);
            } else {
                arg0->unk204 = ((void *)0);
            }
        }
    } else {
        arg0->unk1F8 = 1;
    }
    func_80079530(arg0);
}
