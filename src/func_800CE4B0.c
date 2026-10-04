#include "span_1000/code_800C3F00.h"
#include "types.h"
#define NULL ((void *)0)



s32 func_80077930();   /* extern */
s32 func_800F4F60(); /* extern */
s32 func_801053B0();                     /* extern */
extern s32 D_803275F4;
extern s32 D_80328150;
extern s32 D_80328154;
extern s8 D_80328158;
extern s8 D_80328159;
extern s8 D_8032815A;
extern s32 D_80328170;
extern s32 D_803DA800;
extern s32 D_B04B1300;
extern s32 D_B04B3280;

/* Initializes the game data and resets related state. */
void func_800CE4B0(void) {
    s32 temp_s0;

    temp_s0 = (s32)((s8 *)(&D_B04B3280) - (s8 *)(&D_B04B1300));
    func_80077930(&D_B04B1300, &D_803DA800, temp_s0);
    func_800F4F60(temp_s0, &D_803DA800, 0x25800, D_803275F4);
    func_801053B0(1);
    D_80328150 = 0;
    D_80328158 = 0;
    D_80328159 = 0;
    D_8032815A = 0;
    D_80328154 = 0;
    D_80328170 = 0;
}
