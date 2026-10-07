#include "span_1000/code_8008011C.h"
#include "types.h"








#include "types.h"


s32 func_80110C00();          /* extern */
extern s32 D_801B6C10;
extern s32 D_801B6C14;
extern s32 D_801B6C18;
extern s32 D_801B6C1C;
extern s32 D_801C0840;
extern s16 D_80125800;
extern u8 D_80125802;




void func_800805DC(void) {
    D_801B6C10 = 0;
    D_801B6C14 = 0;
    D_801B6C18 = 0;
    D_801B6C1C = 0;
    func_80110C00(&D_801C0840, 0x380);
    func_80110C00(&((func_800805DC_S1_Shared800805DC *)(&D_801C0840))->unk2680, 0x80);
    D_80125800 = 0;
    D_80125802 = (D_80125802 + 1) % 3;
}
