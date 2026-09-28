/*
 * Writes its argument to the hardware word at 0xA4040010.  The address is
 * built with a bare `lui` into a general register and the store is a full-word
 * `sw` at the low half of the address, which is what an absolute address cast
 * to a pointer produces rather than a %hi/%lo pair against a data symbol.
 */

void func_8011D0D0(unsigned int value) {
    *(volatile unsigned int *)0xA4040010 = value;
}
