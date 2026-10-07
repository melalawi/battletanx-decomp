#include "span_1000/code_800A27D0.h"
#include "span_1000/code_800EC380.h"
#include "types.h"














#include "types.h"


s32 func_800ECE4C();             /* extern */
s32 func_800ED380();   /* extern */
s32 func_800ED5C8();                     





/* extern */

void func_800ED810(func_800ED810_S1_Shared800ED810 *arg0, s32 arg1, u32 arg2, s32 arg3, func_800A2EA4_S1_Shared800A2EA4 *arg4) {
    switch (arg2) {                                 /* irregular */
    case 0:
        func_800ECE4C(arg0, arg1, arg3, arg4);
        return;
    case 2:
        if (arg0->unk1C == 0) {
            arg4->unk0 = 1;
            arg4->unk8 = (f32) arg0->unkC;
            arg4->unk4 = (f32) arg0->unk14;
            return;
        }
        return;
    case 3:
        func_800ED380(arg0, 0, arg3, 0);
        return;
    case 7:
        func_800ED5C8(arg0, arg1, arg3);
        break;
    }
}
