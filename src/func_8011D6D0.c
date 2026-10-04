#include "span_1000/code_8011D6D0.h"
/* func_8011D6D0 -- writes zero to the word the pointer it is handed points at, and returns nothing.
 * Two instructions: one `sw $zero` at offset 0 and the return. The store width in the cartridge is a
 * word, which is what makes the parameter an int pointer rather than a narrower one.
 */

void func_8011D6D0(int *arg0) {
    *arg0 = 0;
}
