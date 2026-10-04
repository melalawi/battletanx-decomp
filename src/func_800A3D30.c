#include "span_1000/code_800A27D0.h"
#include "types.h"

struct FuncA3D30Table;
typedef struct FuncA3D30Table FuncA3D30Table;
typedef struct func_800A3D30_S1 func_800A3D30_S1;
typedef struct func_800A3D30_S2 func_800A3D30_S2;

struct func_800A3D30_S1;

struct func_800A3D30_S2;







struct FuncA3D30Table {
    s32 value[3];
};
struct func_800A3D30_S1 {
    char pad0[0x20];
    s16 unk20;
    char pad20[0x22];
    u16 unk44;
};
struct func_800A3D30_S2 {
    char pad0[1];
    u8 unk1;
    char pad1[0x18 - 2];
    s32 unk18;
    char pad18[0x504 - 0x1C];
    s32 unk504;
};

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
