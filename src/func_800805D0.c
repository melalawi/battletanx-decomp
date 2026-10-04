#include "span_1000/code_8007EB64.h"
/*
 * Returns the constant 0x12320.  The value is built with lui plus ori into
 * $v0, which is how a 32-bit integer constant too large for one immediate is
 * loaded, so the return type is int rather than anything narrower.
 */

int func_800805D0(void) {
    return 0x12320;
}
