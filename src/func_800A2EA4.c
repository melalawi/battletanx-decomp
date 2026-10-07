#include "span_1000/code_800A27D0.h"
#include "types.h"














#include "types.h"


s32 func_800A27D0();             /* extern */
s32 func_800A2A44();   /* extern */
s32 func_800A2C38();                     





/* extern */

void func_800A2EA4(func_800A2EA4_S2_Shared800A2EA4 *arg0, s32 arg1, u32 arg2, s32 arg3, func_800A2EA4_S1_Shared800A2EA4 *arg4) {
    switch (arg2) {                                 /* irregular */
    case 0:
        func_800A27D0(arg0, arg1, arg3, arg4);
        return;
    case 2:
        arg4->unk0 = 1;
        arg4->unk8 = (f32) arg0->unk20;
        arg4->unk4 = (f32) arg0->unk1C;
        return;
    case 3:
        func_800A2A44(arg0, 0, arg3, 0);
        break;
        return;
    case 7:
        func_800A2C38(arg0, arg1, arg3);
        return;
    }
}
