#include "span_1000/code_8008F248.h"
#include "types.h"





















s32 func_8008B89C();                      /* extern */
s32 func_8009FBE4();                             /* extern */
s32 func_800E3460();                             /* extern */





void func_80091608(func_80091608_Object_Shared80091608 *arg0, func_80091608_Status_Shared80091608 *arg1, void *arg2, func_80091608_Output_Shared80091608 *arg3) {
    if (arg0->unk20 == 0) {
        if ((arg1->unk8 == 0) && ((func_8009FBE4(arg1->unkC) & 0xFF) != arg0->unk2C) && (func_800E3460(arg1->unkC) == 0)) {
            arg3->code = 3;
            arg3->value = (s32) arg0->unk18;
            arg0->unk20 = 1U;
            func_8008B89C(arg0);
            return;
        }
        goto block_6;
    }
block_6:
    arg3->code = 1;
}















s32 func_8008B89C();                      /* extern */
s32 func_8009FBE4();                             /* extern */
s32 func_800E3460();                             /* extern */

void func_800916B8(void *arg0, void *arg1, s32 arg2, void *arg3, void *arg4) {
    s32 temp_v0;
    s32 local_arr[1];

    local_arr[0] = (s32) arg1;
    if (arg2 == 0) {
        if ((((struct func_80091608_Object_Shared80091608 *)arg0)->unk20 == 0) && (((struct func_80091608_Status_Shared80091608 *)arg1)->unk8 == 0) && ((func_8009FBE4(((struct func_80091608_Status_Shared80091608 *)arg1)->unkC) & 0xFF) != ((struct func_80091608_Object_Shared80091608 *)arg0)->unk2C) && (func_800E3460(((struct func_80091608_Status_Shared80091608 *)arg1)->unkC) == 0)) {
            ((struct func_80091608_Output_Shared80091608 *)arg4)->code = 3;
            temp_v0 = (s32) ((struct func_80091608_Object_Shared80091608 *)arg0)->unk18;
            ((struct func_80091608_Output_Shared80091608 *)arg4)->value = temp_v0;
            ((struct func_80091608_Object_Shared80091608 *)arg0)->unk20 = 1U;
            func_8008B89C(arg0);
            return;
        }
        ((struct func_80091608_Output_Shared80091608 *)arg4)->code = 1;
    }
}
