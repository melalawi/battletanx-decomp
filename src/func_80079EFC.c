#include "shared/func_80079efc.h"
#include "types.h"
#define NULL ((void *)0)


s32 func_80112140(); /* extern */
s32 func_8011B314();                  /* extern */
extern s32 D_80150340;
extern s32 D_80150350;
extern s32 D_80150354;



void func_80079EFC(void) {
    Func79EFCArg arg;
    s32 temp_v0;

    arg.unk0 = 0x30;
    arg.unk4 = 0x40;
    arg.unk8 = 0x10;
    arg.tail.values[0] = (s32) &D_80150340;
    arg.tail.values[1] = 0;
    arg.tail.values[2] = 0;
    arg.tail.values[3] = 0;
    arg.unk9 = 0;
    temp_v0 = func_80112140(0, 0, &D_80150340, 1, 0x88);
    D_80150350 = temp_v0;
    func_8011B314(temp_v0, &arg);
    D_80150354 = func_80112140(0, 0, &D_80150340, 1, 0x1C);
}
