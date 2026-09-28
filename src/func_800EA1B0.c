/* func_800EA1B0 -- clears the word the argument points at.
 *
 * The whole function is the store, which rides the return's delay slot. Nothing says the target
 * is a struct rather than a bare word, so it is written as the word it is.
 */

void func_800EA1B0(int *slot) {
    *slot = 0;
}
