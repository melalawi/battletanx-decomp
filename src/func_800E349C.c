#include "shared/func_800e349c.h"
/* func_800E349C -- clears five fields of the object it is handed and returns nothing.
 *
 * Every store is of `$zero`, so this writes zeros and reads nothing back; the widths the
 * cartridge uses are what fix the types. Two words go out at 0x09C and 0x0A0, one halfword at
 * 0x344, and two single bytes at 0x34A and 0x348 -- in that order, the last of them in the
 * return's delay slot. The two bytes are written high one first, which is the order they were
 * written in rather than the order they sit in, so they are separate fields and not one pair.
 * Nothing else in the image says what any of them hold, so the struct is a placeholder that
 * names each field for its width and leaves the gaps between them opaque.
 */



void func_800E349C(struct Unknown800E349C *self) {
    self->word_09C = 0;
    self->word_0A0 = 0;
    self->half_344 = 0;
    self->byte_34A = 0;
    self->byte_348 = 0;
}
