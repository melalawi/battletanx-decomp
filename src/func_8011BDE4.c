#include "span_1000/code_8011BD50.h"
/* func_8011BDE4 -- a wrapper that takes no arguments and calls func_801193E0 with
 * the address of D_803C75C8 and two zeros. The lui/addiu pair builds the address of
 * the global rather than loading from it, so the first argument is a pointer to that
 * object; $a1 and $a2 are cleared with `or $zero, $zero`, so the other two arguments
 * are integer zeros.
 */
extern unsigned char D_803C75C8[];
extern void func_801193E0(unsigned char *, int, int);

void func_8011BDE4(void) {
    func_801193E0(D_803C75C8, 0, 0);
}
