#include "span_1000/code_80077930.h"
#include "span_1000/code_8011D0D0.h"
#include "types.h"














/* Polls the status word, reports whether its 0x100 bit was set, and when the
   0x80 bit is also set folds that report into the object's flag word at 0x4
   and clears bit 1 there. Every field and local is touched with lw/sw, so all
   are words; nothing is live across the call inside a loop, so both locals
   sit in the frame. */




int func_8011D100(func_80078D90_S2_Shared80078D90 *obj) {
    int status;
    int pressed;

    status = func_8011D180();
    if ((status & 0x100) != 0) {
        pressed = 1;
    } else {
        pressed = 0;
    }
    if ((status & 0x80) != 0) {
        obj->unk4 = obj->unk4 | pressed;
        obj->unk4 = obj->unk4 & ~2;
    }
    return pressed;
}
