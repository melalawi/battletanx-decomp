#include "common/types.h"
#include "span_1000/code_8011D790.h"
#include "types.h"

struct Shape_func_8011DC98;


struct Shape_func_8011DC98 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    struct Shape_func_8011B9E0 *first;
};

/* func_8011DC98 -- drains the owner's single-entry list at 0x14: while that word is non-zero it
 * hands the entry to func_8011C150, then to func_8011C180 together with the address of the owner's
 * field at 0x04, and re-reads 0x14. The lw/sw widths make every field a word, and the loop keeping
 * the owner and the 0x04 address in $s1/$s2 across the two calls fixes them as one pointer each.
 */







extern void func_8011C150(struct Shape_func_8011B9E0 *);
extern void func_8011C180(struct Shape_func_8011B9E0 *, int *);

void func_8011DC98(struct Shape_func_8011DC98 *owner) {
    struct Shape_func_8011B9E0 *child;

    child = owner->first;
    while (child != 0) {
        func_8011C150(child);
        func_8011C180(child, &owner->unk_04);
        child = owner->first;
    }
}
