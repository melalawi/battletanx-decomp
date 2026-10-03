#include "shared/func_8011f7f0.h"
/* func_8011F7F0 -- fills six fields of the record it is handed from three of its arguments and zero.
 * The store widths in the cartridge fix the types: four words at 0x0, 0x4, 0x8 and 0x10, and two
 * halfwords at 0xC and 0xE. The first word and both halfwords take $zero; the other three take the
 * second, third and fourth arguments in order.
 */


void func_8011F7F0(struct Shape_func_8011F7F0 *arg0, int arg1, int arg2, int arg3) {
    arg0->unk0 = 0;
    arg0->unk4 = arg1;
    arg0->unk8 = arg2;
    arg0->unkC = 0;
    arg0->unkE = 0;
    arg0->unk10 = arg3;
}
