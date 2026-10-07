#include "span_1000/code_800A5050.h"
#include "types.h"








#include "types.h"
/* Adds to the counter at offset 0x210 and, when its 50000-unit quotient increases and the mode check succeeds, calls func_800A5DD8 with the new quotient scaled by 50000. */


s32 func_8007C700();
s32 func_800A5DD8();



void func_800A59E8(FuncA59E8State_Shared800A59E8 *arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v1;
    s32 temp_t0;

    temp_v1 = arg0->unk210;
    temp_s1 = temp_v1 + arg1;
    temp_s0 = temp_s1 / 50000;
    temp_t0 = arg0->unk210 / 50000;
    if (temp_t0 >= temp_s0) {
        arg0->unk210 = temp_s1;
        return;
    }
    if (func_8007C700() != 0) {
        func_800A5DD8(arg0, temp_s0 * 0xC350);
    }
    arg0->unk210 = temp_s1;
}
