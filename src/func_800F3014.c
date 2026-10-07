#include "span_1000/code_800F29F0.h"
#include "types.h"







#include "types.h"


void *func_8008AD10();     /* extern */

void func_800F3014(s8 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, s32 arg6, s32 arg7) {
    void *temp_v0;

    temp_v0 = func_8008AD10(1, 0x20, 0x20);
    if (temp_v0 != ((void *)0)) {
        ((struct Func_800F3014_View0_Shared800F3014 *)temp_v0)->field_c = arg0;
        ((struct Func_800F3014_View0_Shared800F3014 *)temp_v0)->field_d = arg1;
        ((struct Func_800F3014_View0_Shared800F3014 *)temp_v0)->field_e = arg2;
        ((struct Func_800F3014_View0_Shared800F3014 *)temp_v0)->field_f = arg3;
        ((struct Func_800F3014_View0_Shared800F3014 *)temp_v0)->field_10 = arg4;
        ((struct Func_800F3014_View0_Shared800F3014 *)temp_v0)->field_11 = arg5;
        ((struct Func_800F3014_View0_Shared800F3014 *)temp_v0)->field_14 = arg6;
        ((struct Func_800F3014_View0_Shared800F3014 *)temp_v0)->field_18 = 0;
        ((struct Func_800F3014_View0_Shared800F3014 *)temp_v0)->field_1c = arg7;
    }
}
