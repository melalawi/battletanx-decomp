#include "span_1000/code_80091A60.h"
#include "span_1000/code_800E0B00.h"
#include "types.h"










#include "types.h"














#include "types.h"


           /* extern */
const f32 D_80074428 = 2.0f;
extern void *D_80135834;

void func_800E0B00(s32 arg0, void *arg1) {
    u16 sp10;
    u16 sp12;
    void *var_a1;
    void *var_v1;

    func_800E1818(arg0 & 0xFFFF, &sp10, &sp12);
    var_a1 = ((void *)0);
    if ((sp10 < (u16) ((struct Func_800E0B00_View0_Shared800E0B00 *)D_80135834)->field_8) && (sp10 != 0)) {
        var_a1 = ((struct Func_800E0B00_View0_Shared800E0B00 *)D_80135834)->field_c + (sp10 * 8);
    }
    if (sp12 >= (u16) ((struct Func_800E0B00_View0_Shared800E0B00 *)D_80135834)->field_8) {
        var_v1 = ((void *)0);
    } else if (sp12 == 0) {
        var_v1 = ((void *)0);
    } else {
        var_v1 = ((struct Func_800E0B00_View0_Shared800E0B00 *)D_80135834)->field_c + (sp12 * 8);
    }
    ((struct PolygonPoint *)arg1)->x = (f32) ((((struct PolygonPoint *)var_a1)->x + ((struct PolygonPoint *)var_v1)->x) / D_80074428);
    ((struct PolygonPoint *)arg1)->y = (f32) ((((struct PolygonPoint *)var_a1)->y + ((struct PolygonPoint *)var_v1)->y) / D_80074428);
}
