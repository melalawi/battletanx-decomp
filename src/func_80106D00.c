#include "span_1000/code_8010698C.h"
/* func_80106D00 -- returns -1.
 *
 * A constant with no argument read and no state touched. -1 rather than 0xFFFFFFFF because the
 * cartridge builds it with a single `addiu` from zero, which is the sign-extended form.
 */

int func_80106D00(void) {
    return -1;
}
