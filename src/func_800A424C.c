/* func_800A424C -- the address of the member at 0x048.
 *
 * No load: the cartridge adds 0x48 to the argument and returns it, which is a pointer into the
 * object rather than anything read out of it. What lives at 0x48 is unknown, so the member is
 * named for its offset and left an opaque byte run.
 */

struct Unknown800A424C {
    unsigned char unk_000[0x48];
    unsigned char member[4]; /* 0x048 */
};

void *func_800A424C(struct Unknown800A424C *self) {
    return self->member;
}
