#include "span_1000/code_800A27D0.h"
#include "types.h"




















#include "types.h"


s32 func_80078634();                 /* extern */
s32 func_80078680();                 /* extern */
s32 func_8007AAA0();                                /* extern */
void *func_800A03B8();                           /* extern */
extern s32 D_80126128;                          /* unable to generate initializer: unknown type; const */
extern s32 D_80126140;                          /* unable to generate initializer: unknown type; const */







void func_800A3D30(void *arg0) {
    func_800A3D30_S1_Shared800A3D30 *ptr;
    s32 var_v0;
    void *temp_s0;
    func_800A3D30_S2_Shared800A3D30 *temp_v0;

    ptr = arg0;
    temp_v0 = func_800A03B8(ptr->unk20);
    if (temp_v0->unk1 != 0) {
        if (ptr->unk44 == 1) {
            var_v0 = func_8007AAA0();
            temp_s0 = (var_v0 >= 3) ? (FuncA3D30Table_Shared800A3D30 *)&D_80126140 + 1 : (FuncA3D30Table_Shared800A3D30 *)&D_80126140;
        } else {
            var_v0 = func_8007AAA0();
            temp_s0 = (var_v0 >= 3) ? (FuncA3D30Table_Shared800A3D30 *)&D_80126128 + 1 : (FuncA3D30Table_Shared800A3D30 *)&D_80126128;
        }
        func_80078680((s8 *)ptr + 0x48, ((FuncA3D30Table_Shared800A3D30 *)temp_s0)->value[temp_v0->unk18]);
        temp_s0 = (s8 *)ptr + 0x48;
        func_80078634(temp_s0, temp_v0->unk504);
    }
}
