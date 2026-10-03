#include "shared/func_8011b2a4.h"
/* func_8011B2A4 -- walks the owner's entry array once per entry, zeroing each entry's first word
 * and then calling func_80119BB4 with the owner and the index. The count at 0x34 is read with lbu
 * on every iteration, so it is an unsigned char; the entry stride of 0x10 fixes the array element
 * size and the sw fixes the zeroed field as a word.
 */




extern void func_80119BB4(Shape_func_8011B2A4 *, int);

void func_8011B2A4(Shape_func_8011B2A4 *owner) {
    int i;

    for (i = 0; i < owner->count; i++) {
        owner->entries[i].unk_0 = 0;
        func_80119BB4(owner, i);
    }
}
