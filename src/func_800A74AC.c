#include "span_1000/code_800A6864.h"
#include "types.h"
































#include "types.h"


void *func_800A6688();                            /* extern */
s32 func_800A6E30();                  













/* extern */

/* Releases linked resources when the selected object matches the active one. */
void func_800A74AC(func_800A74AC_S4_Shared800A74AC *arg0, func_800A74AC_S1_Shared800A74AC *arg1, s32 arg2) {
    func_800A74AC_S3_Shared800A74AC *temp_s0;
    void *temp_s0_2;
    func_800A74AC_S2_Shared800A74AC *temp_s1;
    func_800A74AC_S6_Shared800A74AC *var_a0;

    if ((arg2 == 0) && (arg1->unk8 == 0)) {
        temp_s1 = arg1->unkC;
        temp_s0 = func_800A6688(temp_s1->unk4);
        if (temp_s0->unk1AE == (((func_800A74AC_S3_Shared800A74AC *)(func_800A6688(arg0->unkC)))->unk1AE)) {
            var_a0 = temp_s1->unk98;
            if (var_a0 != ((void *)0)) {
                do {
                    temp_s0_2 = var_a0->unk2C;
                    func_800A6E30(var_a0, arg0->unkC);
                    var_a0 = temp_s0_2;
                } while (var_a0 != ((void *)0));
            }
            temp_s1->unk98 = ((void *)0);
        }
    }
}
