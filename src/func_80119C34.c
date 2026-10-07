#include "span_1000/code_8010BFDC.h"
#include "span_1000/code_80119B60.h"
#include "types.h"

















#include "types.h"


s32 func_80119B60();            /* extern */
s32 func_80119BB4();                 /* extern */

void func_80119C34(void *arg0, void *arg1) {
    s32 temp_s1;
    s32 var_s0;
    void *var_v0;

    var_v0 = arg1;
    do {
        temp_s1 = ((struct Func_80119C34_View0_Shared80119C34 *)var_v0)->field_c;
        var_v0 = (void *)((s32 *)var_v0 + 1);
    } while (temp_s1 == 0);
    var_s0 = 0;
    if ((s32) ((struct Func_80119C34_View1_Shared80119C34 *)arg0)->field_34 > 0) {
        do {
            func_80119BB4(arg0, var_s0);
            func_80119B60(arg0, temp_s1, var_s0);
            var_s0 += 1;
        } while (var_s0 < (s32) ((struct Func_80119C34_View1_Shared80119C34 *)arg0)->field_34);
    }
    if (((struct func_8010DCD0_S2_Shared8010DCD0 *)arg1)->unk8 != 0) {
        func_80119BB4(arg0, var_s0);
        func_80119B60(arg0, ((struct func_8010DCD0_S2_Shared8010DCD0 *)arg1)->unk8, 9);
    }
}
