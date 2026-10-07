#include "span_1000/code_80094704.h"
#include "types.h"















#include "types.h"



extern u8 D_802D8141;
extern s32 D_802D8144;
extern s32 D_802D8148;
extern s32 D_802D814C;
extern s32 D_802E17A8[];
extern struct Func_80096784_Value_Shared80096784 D_802E17B8[];
extern struct Func_80096784_Record_Shared80096784 D_802E17D8[];

/* Extracts and transforms values from data tables, storing the results in global variables. */
void *func_80096784(s32 arg0) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v1;
    u16 temp_v0;
    u16 temp_v1_2;
    void *temp_a2;
    s32 *output_value;

    temp_v1 = D_802E17A8[arg0] * 6;
    temp_a2 = (s8 *)D_802E17D8 + temp_v1;
    temp_v0 = ((struct Func_80096784_Record_Shared80096784 *)temp_a2)->value;
    temp_v1_2 = ((struct Func_80096784_Value_Shared80096784 *)((s8 *)D_802E17B8 + temp_v1))->value;
    temp_a1 = temp_v0 | ((u32) (temp_v0 & 0xF00) >> 8) | ((temp_v0 & 0xF) << 8);
    temp_a0 = temp_v1_2 | ((u32) (temp_v1_2 & 0xF00) >> 8) | ((temp_v1_2 & 0xF) << 8);
    output_value = &D_802D8144;
    *output_value = temp_a1;
    D_802D8148 = temp_a1 & ~temp_a0;
    D_802D814C = temp_a0 & ~temp_a1;
    ((struct Func_80096784_Output_Shared80096784 *)(output_value - 1))->mode = (u8) ((struct Func_80096784_Record_Shared80096784 *)temp_a2)->mode;
    D_802D8141 = ((struct Func_80096784_Record_Shared80096784 *)temp_a2)->channel;
    return output_value - 1;
}
