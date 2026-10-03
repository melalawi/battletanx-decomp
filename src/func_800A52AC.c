#include "shared/func_800a52ac.h"
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
/* The values func_800A52AC loads by address:
 * 0x80072DEC = 30.0 (float, unnamed in this cartridge's tables)
 */
s32 func_8011CC84();  /* extern */
extern s32 D_801B4AA8;
extern s32 D_80072DE8;                          



/* Initializes the object's timing fields and registers two callbacks when it is first activated. */

void func_800A52AC(func_800A52AC_S1 *arg0, s32 arg1, s32 arg2, f32 arg3) {
    if (arg0->unk1A6 == 0) {
        arg0->unk218 = 0x27;
        arg0->unk21C = (s32) (D_801B4AA8 + (s32) (arg3 * 30.0f));
        func_8011CC84(&arg0->unk220, &D_80072DE8, arg1);
        func_8011CC84(&arg0->unk240, &D_80072DE8, arg2);
    }
}
