#include "span_1000/code_800A5050.h"
#include "span_1000/code_8010BFDC.h"
#include "types.h"









s32 func_800796F0();            /* extern */
const f32 D_80072DE4 = 30.0f;
extern s16 D_801260A8[];




void func_800A51E8(FuncA51E8State_Shared800A51E8 *arg0, s32 arg1, f32 arg2) {
    s32 temp_a0;
    void *temp_s2;
    f32 product;
    s32 current;

    if ((arg0->unk1A6 == 0) && ((temp_s2 = (void *) ((arg1 << 2) + (u32) arg0), temp_a0 = ((FuncA51E8State_Shared800A51E8 *) temp_s2)->unk260, (temp_a0 == 0)) || ((temp_a0 + D_801260A8[arg1]) < D_801B4AA8))) {
        if (arg1 == 1) {
            func_800796F0(0x2C, 0);
        }
        product = arg2 * D_80072DE4;
        current = D_801B4AA8;
        arg0->unk218 = arg1;
        arg0->unk21C = current + (s32) product;
        ((FuncA51E8State_Shared800A51E8 *) temp_s2)->unk260 = current;
    }
}









/* The values func_800A52AC loads by address:
 * 0x80072DEC = 30.0 (float, unnamed in this cartridge's tables)
 */
s32 func_8011CC84();  /* extern */

extern s32 D_80072DE8;                          



/* Initializes the object's timing fields and registers two callbacks when it is first activated. */

void func_800A52AC(func_800A52AC_S1_Shared800A51E8 *arg0, s32 arg1, s32 arg2, f32 arg3) {
    if (arg0->unk1A6 == 0) {
        arg0->unk218 = 0x27;
        arg0->unk21C = (s32) (D_801B4AA8 + (s32) (arg3 * 30.0f));
        func_8011CC84(&arg0->unk220, &D_80072DE8, arg1);
        func_8011CC84(&arg0->unk240, &D_80072DE8, arg2);
    }
}
