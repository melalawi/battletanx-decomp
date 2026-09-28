/* func_8009E39C -- the address of the member at 0x054.
 *
 * The same shape as func_800A424C at a different offset in a different object: an addition on
 * the argument, returned, with nothing loaded.
 */

struct Unknown8009E39C {
    unsigned char unk_000[0x54];
    unsigned char member[4]; /* 0x054 */
};

void *func_8009E39C(struct Unknown8009E39C *self) {
    return self->member;
}
