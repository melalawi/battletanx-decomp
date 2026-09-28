/* func_800A42BC -- writes the word at 0x010.
 *
 * The write half of the pair whose read half is func_800A42B0, twelve bytes earlier. The store
 * sits in the return's delay slot, so the function is two words with no body ahead of it.
 */

struct Unknown800A42BC {
    int unk_000[4];
    int value; /* 0x010 */
};

void func_800A42BC(struct Unknown800A42BC *self, int value) {
    self->value = value;
}
