/*
 * Reads and returns the hardware word at 0xA4500004.  The address is built
 * with a bare `lui` into a general register and the load is a full-word `lw`
 * at the low half of the address, which is what an absolute address cast to a
 * pointer produces rather than a %hi/%lo pair against a data symbol.
 */

unsigned int func_80110480(void) {
    return *(volatile unsigned int *)0xA4500004;
}
