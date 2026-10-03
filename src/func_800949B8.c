#include "shared/func_800949b8.h"
/* func_800949B8 -- keeps the smallest value seen: it loads the current best from
 * the third argument with lw, compares the second argument against it with a
 * signed slt, and on a smaller value writes the value and the first argument
 * into the record's first two words. The lw/sw widths fix both record fields as
 * 32-bit, and slt (not sltu) fixes the compared value as a signed int; the
 * compare lands in the same register as the loaded value because the cartridge
 * reuses one local for both.
 */


void func_800949B8(void *owner, int value, Best *best) {
    int t;

    t = best->value;
    t = value < t;
    if (t) {
        best->value = value;
        best->owner = owner;
    }
}
