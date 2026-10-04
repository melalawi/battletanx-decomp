#include "span_1000/code_8011D790.h"
#include "types.h"

struct func_8011E564_S1;
typedef struct func_8011E564_S1 func_8011E564_S1;



struct func_8011E564_S1 {
    char pad0[0x14];
    s32 unk14;
    s32 unk18;
    char pad1C[0x30 - 0x1C];
    s32 unk30;
    char pad34[0x3C - 0x34];
    s32 unk3C;
    s32 unk40;
    s32 unk44;
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
void func_8011F7F0(void *, int, int, int);
s32 func_80112140(); /* extern */
extern s32 func_8011F810;
extern s32 func_8011FEBC;




void func_8011E564(func_8011E564_S1 *arg0, s32 (*arg1)(void *), s32 arg2) {
    func_8011F7F0(arg0, (s32) &func_8011FEBC, (s32) &func_8011F810, 0);
    arg0->unk14 = func_80112140(0, 0, arg2, 1, 0x20);
    arg0->unk18 = func_80112140(0, 0, arg2, 1, 0x20);
    arg0->unk30 = arg1((s8 *)arg0 + 0x34);
    arg0->unk3C = 0;
    arg0->unk40 = 1;
    arg0->unk44 = 0;
}
