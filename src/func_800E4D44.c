#include "span_1000/code_800E3BC0.h"
#include "types.h"







#include "types.h"


s32 func_800A03B8();                         /* extern */
s32 func_800A6688();                             /* extern */

void func_800E4D44(void *arg0, s16 arg1) {
    s16 temp_a0;
    s32 temp_v0;
    s32 var_s2;
    s32 var_v0;

    temp_v0 = func_800A6688(arg1 & 0xFFFF);
    ((struct Func_800E4D44_Lists_Shared800E4D44 *)arg0)->initial_ids[((struct Func_800E4D44_Lists_Shared800E4D44 *)arg0)->initial_count] = arg1;
    ((struct Func_800E4D44_Lists_Shared800E4D44 *)arg0)->initial_count = (u16) (((struct Func_800E4D44_Lists_Shared800E4D44 *)arg0)->initial_count + 1);
    for (var_s2 = 0; (u32) (var_s2 & 0xFFFF) < 5U; var_s2++) {
        var_v0 = var_s2 & 0xFFFF;
        temp_a0 = ((s16 *)temp_v0)[var_v0];
        func_800A03B8(temp_a0);
        ((struct Func_800E4D44_Lists_Shared800E4D44 *)arg0)->extra_ids[((struct Func_800E4D44_Lists_Shared800E4D44 *)arg0)->extra_count] = temp_a0;
        ((struct Func_800E4D44_Lists_Shared800E4D44 *)arg0)->extra_count = (u16) (((struct Func_800E4D44_Lists_Shared800E4D44 *)arg0)->extra_count + 1);
    }
}
