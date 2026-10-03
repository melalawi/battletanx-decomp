#include "shared/func_800e566c.h"
/* Clears five bytes and one word of a record: the bytes at 0x4..0x7, the word at
 * 0x8, and last the byte at 0x3.
 * sb fixes 0x3..0x7 as single bytes and sw fixes 0x8 as a 32-bit field. */



void func_800E566C(struct Rec *r) {
    r->b = 0;
    r->c = 0;
    r->d = 0;
    r->e = 0;
    r->f = 0;
    r->a = 0;
}
