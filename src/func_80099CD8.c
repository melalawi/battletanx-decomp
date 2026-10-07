#include "span_1000/code_80097038.h"
#include "types.h"






#include "types.h"







#include "types.h"
/* checks field conditions and calls handler with scaled float parameter */


s32 func_800796F0();                /* extern */
s32 func_800799D0();                    /* extern */
s32 func_800E3470();                                /* extern */
const f64 D_800723B0 = 0.3;
const f32 D_800723B8 = 0.5f;
const f32 D_800723BC = 28672.0f;

void func_80099CD8(void *arg0, s32 arg1) {
    s32 temp_a0;

    if ((((struct Func_80099CD8_View0_Shared80099CD8 *)arg0)->field_464 == 0) && (D_800723B0 < (f64) ((struct Func_80099CD8_View0_Shared80099CD8 *)arg0)->field_3b4) && (func_800E3470() != 0)) {
        temp_a0 = func_800796F0(arg1, 0);
        if (((struct Func_80099CD8_View0_Shared80099CD8 *)arg0)->field_3b4 < D_800723B8) {
            func_800799D0(temp_a0, (s16) (s32) (2.0f * ((struct Func_80099CD8_View0_Shared80099CD8 *)arg0)->field_3b4 * D_800723BC));
        }
        ((struct Func_80099CD8_View0_Shared80099CD8 *)arg0)->field_464 = 0x20U;
    }
}
