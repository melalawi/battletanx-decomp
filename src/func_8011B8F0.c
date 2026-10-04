#include "span_1000/code_8011B830.h"
/*
 * Sets up one 16-byte request block on the stack with 0xF in its leading halfword
 * and hands it, together with the sub-object 0x48 bytes into arg0, to
 * func_8011B60C with a third argument of zero.
 * Types came from the disassembly: the literal 0xF is written with sh, so the block's
 * first field is a halfword; the block's address is formed as `addiu $a1, $sp, 0x18`
 * and the frame runs to 0x28, which fixes the block at 16 bytes rather than a bare
 * short; and `addiu $a0, $a0, 0x48` on the incoming pointer fixes arg0 as a byte
 * pointer offset by 0x48.
 */
extern void func_8011B60C(unsigned char *, short *, int);
void func_8011B8F0(unsigned char *arg0) {
    short v[8];

    v[0] = 0xF;
    func_8011B60C(arg0 + 0x48, v, 0);
}
