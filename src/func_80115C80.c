#include "shared/func_80115c80.h"
/* NOTE: byte-identical only when compiled at -O1.
 *
 * func_80115C80 -- reloads a device's 0x20-byte register block: after flushing any pending change
 * it asks func_80114190 for the block, retrying once when that returns 2, then compares all 0x20
 * bytes against the copy the device holds at 0xC and returns 2 on the first mismatch. The lbu loads
 * fix both the held copy and the readback buffer as unsigned char arrays of 0x20.
 */


extern int func_8011609C(Obj_func_80115C80 *);
extern int func_80114190(void *, void *, unsigned short, unsigned char *);

int func_80115C80(Obj_func_80115C80 *obj) {
    int i;
    unsigned char buf[0x20];
    int result;

    if (obj->unk_65 != 0) {
        obj->unk_65 = 0;
        result = func_8011609C(obj);
        if (result != 0) {
            return result;
        }
    }
    result = func_80114190(obj->unk_4, obj->unk_8, 1, buf);
    if (result != 0) {
        if (result != 2) {
            return result;
        }
        result = func_80114190(obj->unk_4, obj->unk_8, 1, buf);
        if (result != 0) {
            return result;
        }
    }
    for (i = 0; i < 0x20; i++) {
        if (obj->unk_C[i] != buf[i]) {
            return 2;
        }
    }
    return 0;
}
