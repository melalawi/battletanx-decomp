#include "shared/func_8011588c.h"
/* NOTE: byte-identical only when compiled at -O1.
 *
 * func_8011588C -- reprobes a display device: it first flushes any pending change, then walks the
 * mode list {1,3,4,6} from index 1 asking func_80114190 to set each mode until func_8011540C
 * reports the target's own width and height back, returning 10 if no mode fits, and finally asks
 * func_80113E10 to tear down every mode it tried except the one that stuck. The lhu loads fix the
 * mode list and the two readback values as unsigned halfwords and the lbu/sb at 0x65 fixes the
 * dirty flag as one byte.
 */




extern int func_8011609C(Obj_func_8011588C *);
extern int func_80114190(void *, void *, unsigned short, Target_func_8011588C *);
extern void func_8011540C(Target_func_8011588C *, unsigned short *, unsigned short *);
extern int func_80113E10(void *, void *, unsigned short, Target_func_8011588C *, int);

int func_8011588C(Obj_func_8011588C *obj, Target_func_8011588C *target) {
    unsigned short modes[4];
    int result;
    unsigned short h1;
    unsigned short h2;
    int i;
    int j;

    result = 0;
    if (obj->unk_65 != 0) {
        obj->unk_65 = 0;
        result = func_8011609C(obj);
        if (result != 0) {
            return result;
        }
    }
    modes[0] = 1;
    modes[1] = 3;
    modes[2] = 4;
    modes[3] = 6;
    for (i = 1; i < 4; i++) {
        result = func_80114190(obj->unk_4, obj->unk_8, modes[i], target);
        if (result != 0) {
            return result;
        }
        func_8011540C(target, &h1, &h2);
        if (target->unk_1C == h1 && target->unk_1E == h2) {
            break;
        }
    }
    if (i == 4) {
        return 10;
    }
    for (j = 0; j < 4; j++) {
        if (j != i) {
            result = func_80113E10(obj->unk_4, obj->unk_8, modes[j], target, 1);
            if (result != 0) {
                return result;
            }
        }
    }
    return 0;
}
