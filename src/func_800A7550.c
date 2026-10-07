#include "span_1000/code_800A6864.h"
#include "types.h"








#include "types.h"


void *func_8008AD10();     /* extern */
s32 func_80106D18(); 



/* extern */

void func_800A7550(f32 arg0, f32 arg1, s32 arg2) {
    s32 temp_a3;
    func_800A7550_S1_Shared800A7550 *temp_v0;

    temp_v0 = func_8008AD10(0, 0x1F, 0x18);
    if (temp_v0 != ((void *)0)) {
        temp_a3 = -arg2;
        temp_v0->unkC = func_80106D18(temp_v0, (s32) arg0, (s32) arg1, temp_a3, arg2, temp_a3, arg2, 2, 0);
        temp_v0->unk14 = arg0;
        temp_v0->unk10 = arg1;
    }
}
