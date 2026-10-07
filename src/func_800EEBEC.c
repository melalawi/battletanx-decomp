#include "span_1000/code_8008F248.h"
#include "span_1000/code_800EDB20.h"
#include "types.h"





















s32 func_800E3470();                             /* extern */
extern u8 D_8033B630;
extern u8 D_8033B631;
extern s32 D_8013957C;                          /* unable to generate initializer: unknown type; const */
extern s32 D_801395B8;                          /* unable to generate initializer: unknown type; const */





void func_800EEBEC(FuncEEBECObject_Shared800EEBEC *arg0, func_80091608_Status_Shared80091608 *arg1, void *arg2, FuncEEBECOutput_Shared800EEBEC *arg3) {
    if (arg1->unk8 == 0) {
        if (func_800E3470(arg1->unkC) != 0) {
            if (arg0->unk24 < 0.0f) {
                if (D_8033B630 != 0) {
                    arg3->code = 0xA;
                    arg3->data = &D_8013957C;
                    return;
                }
                goto block_7;
            }
            if (D_8033B631 != 0) {
                arg3->code = 0xA;
                arg3->data = &D_801395B8;
                return;
            }
            goto block_7;
        }
block_7:
        arg3->code = 1;
    }
}




















/* When arg2 and the status field at offset 8 are zero, sets output code 10 and sign-specific data if func_800E3470 succeeds and the corresponding flag is set, otherwise setting code 1. */



s32 func_800E3470();

extern u8 D_8033B630;
extern u8 D_8033B631;
extern s32 D_8013957C;
extern s32 D_801395B8;





void func_800EECA0(FuncEEBECObject_Shared800EEBEC *arg0, func_80091608_Status_Shared80091608 *arg1, s32 arg2, void *arg3, FuncEEBECOutput_Shared800EEBEC *arg4) {
    s32 temp_arg3;
    s32 temp_arg0;

    temp_arg0 = (s32) arg0;
    temp_arg3 = (s32) arg4;

    if ((arg2 == 0) && (arg1->unk8 == 0)) {
        if (func_800E3470(arg1->unkC) != 0) {
            if (((FuncEEBECObject_Shared800EEBEC *) temp_arg0)->unk24 < 0.0f) {
                if (D_8033B630 != 0) {
                    ((FuncEEBECOutput_Shared800EEBEC *) temp_arg3)->code = 0xA;
                    ((FuncEEBECOutput_Shared800EEBEC *) temp_arg3)->data = &D_8013957C;
                    return;
                }
            } else if (D_8033B631 != 0) {
                ((FuncEEBECOutput_Shared800EEBEC *) temp_arg3)->code = 0xA;
                ((FuncEEBECOutput_Shared800EEBEC *) temp_arg3)->data = &D_801395B8;
                return;
            }
        }
        ((FuncEEBECOutput_Shared800EEBEC *) temp_arg3)->code = 1;
    }
}
