#include "span_1000/code_80077930.h"
#include "span_1000/code_80077930.h"
#include "span_1000/code_80077930.h"
#include "types.h"


s32 func_80111540(); /* extern */
s32 func_80118860(); /* extern */
s32 func_8011BB90();            /* extern */
s32 func_8011D1A0();                   /* extern */
extern s32 D_8014B9F0;
extern s32 D_8014BBA0;
extern s32 D_8014BD50;
extern s32 D_8014C070;


/* Configures the title screen callbacks and waits for the screen transition. */
void func_80077A38(s32 arg0) {
    func_80118860(0x96, &D_8014C070, &D_8014BD50, 0xC8);
    func_80111540(&D_8014BBA0, 2, &func_80077AD0, arg0, &D_8014B9F0, 0xA);
    func_8011D1A0(&D_8014BBA0);
    func_8011BB90(0, 0);
loop_1:
    goto loop_1;
}
