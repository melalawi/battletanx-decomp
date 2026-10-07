#include "span_1000/code_800ABFD0.h"
#include "types.h"




s32 func_800F4DFC(); /* extern */
s32 func_801054E0();                     /* extern */
s32 func_8010552C();            /* extern */
s32 func_8010555C(); /* extern */
s32 func_80105A50(); /* extern */
s32 func_8010698C();                   /* extern */
extern s32 D_803276D4;
extern s32 D_800731B0;                          /* unable to generate initializer: unknown type */

void func_800ABFD0(void) {
    func_800F4DFC(&D_803276D4, 0, 0, 0x140, 0xF0, 0, 0, 0, 0xFF);
    func_8010698C(&D_803276D4);
    func_8010555C(0xC8, 0xC8, 0xC8, 0xFF);
    func_801054E0(1);
    func_8010552C(0, 0x55);
    func_80105A50(&D_803276D4, &D_800731B0, 0, 0x140);
}
