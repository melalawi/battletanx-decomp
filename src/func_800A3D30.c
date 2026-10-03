#include "shared/func_800a3d30.h"
#include "types.h"
#define NULL ((void *)0)


#ifndef M2C_MACROS_H
#define M2C_MACROS_H

/* Unknown types */

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */

/* Bitwise (reinterpret) cast */

/* Unaligned reads */

/* Unhandled instructions */

/* Carry/overflow bits from partially-implemented instructions */

/* Memcpy patterns */

/* Sh2 control register loads/stores */

#endif
s32 func_80078634();                 /* extern */
s32 func_80078680();                 /* extern */
s32 func_8007AAA0();                                /* extern */
void *func_800A03B8();                           /* extern */
extern s32 D_80126128;                          /* unable to generate initializer: unknown type; const */
extern s32 D_80126140;                          /* unable to generate initializer: unknown type; const */







void func_800A3D30(void *arg0) {
    func_800A3D30_S1 *ptr;
    s32 var_v0;
    void *temp_s0;
    func_800A3D30_S2 *temp_v0;

    ptr = arg0;
    temp_v0 = func_800A03B8(ptr->unk20);
    if (temp_v0->unk1 != 0) {
        if (ptr->unk44 == 1) {
            var_v0 = func_8007AAA0();
            temp_s0 = (var_v0 >= 3) ? (FuncA3D30Table *)&D_80126140 + 1 : (FuncA3D30Table *)&D_80126140;
        } else {
            var_v0 = func_8007AAA0();
            temp_s0 = (var_v0 >= 3) ? (FuncA3D30Table *)&D_80126128 + 1 : (FuncA3D30Table *)&D_80126128;
        }
        func_80078680((s8 *)ptr + 0x48, ((FuncA3D30Table *)temp_s0)->value[temp_v0->unk18]);
        temp_s0 = (s8 *)ptr + 0x48;
        func_80078634(temp_s0, temp_v0->unk504);
    }
}
