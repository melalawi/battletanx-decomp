#include "span_1000/code_800E21E4.h"
#include "types.h"




















#include "types.h"


void *func_800A03B8();                      /* extern */
s32 func_800E52A0();                        






/* extern */

void func_800E34B4(func_800E34B4_S1_Shared800E34B4 *arg0, s16 arg1, s16 arg2) {
    func_800E34B4_S2_Shared800E34B4 *temp_v0;
    f32 *ordered_value;

    if (arg2 != 0xFF) {
        func_800A03B8(arg1);
        (void)(arg2 << 0x10);
        temp_v0 = func_800A03B8(arg2);
        arg0->unk10 = temp_v0;
        arg0->unk14 = func_800E52A0(arg1, arg2);
        arg0->unkC = (f32) temp_v0->unk24;
        ordered_value = &arg0->unk8.v1;
        *ordered_value = (f32) temp_v0->unk2C;
        arg0->unk4 = (void *)&arg0->unk8.v0;
        arg0->unk0 = 1;
        return;
    }
    arg0->unk0 = 0;
    arg0->unk4 = ((void *)0);
}
