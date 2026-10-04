#include "span_1000/code_8011DC00.h"
/* Hands the second argument to func_8011C150 and then registers it against the
 * sub-record 0x14 bytes into the first argument.
 * Both arguments are homed to their incoming stack slots because they are read after
 * the first call and the function has no loop. */

extern void func_8011C150(void *b);
extern void func_8011C180(void *b, void *sub);

void func_8011DC60(char *a, void *b) {
    func_8011C150(b);
    func_8011C180(b, a + 0x14);
}
