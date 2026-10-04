#include "span_1000/code_8011C3AC.h"
/*
 * Returns the length of a NUL-terminated string: it walks a cursor forward
 * while the byte ahead of it is non-zero and returns the distance covered.
 * The `lbu` loads fix the characters as unsigned bytes and the closing
 * `subu $v0, $v1, $a0` is the pointer difference that gives the count.
 */

int func_8011D3DC(unsigned char *s) {
    unsigned char *p;

    for (p = s; *p != 0; p++) {
    }
    return p - s;
}
