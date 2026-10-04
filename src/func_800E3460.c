#include "span_1000/code_800E21E4.h"
#include "types.h"

              /* size 0x0 */

s32 func_800E3460(const u8 *arg0) {
    return arg0[0x350] == 2;
}

int func_800E3470(unsigned char *state) {
    return state[848] == 1;
}

struct Shape_func_800E3480;


struct Shape_func_800E3480 {
    char pad_0[0x344];
    short counter;
    char pad_346[0x348 - 0x346];
    unsigned char a;
    unsigned char pad_349;
    unsigned char b;
};

/* Two neighbouring resets that share one interval.
 * func_800E3480 clears the two words at the start of the record; func_800E348C clears
 * the halfword at 0x344 and the bytes at 0x348 and 0x34A of a much larger one.
 * sw fixes the first pair as words, sh fixes 0x344 as a halfword and sb fixes 0x348
 * and 0x34A as single bytes. */



void func_800E3480(int *p) {
    p[0] = 0;
    p[1] = 0;
}

void func_800E348C(struct Shape_func_800E3480 *s) {
    s->counter = 0;
    s->b = 0;
    s->a = 0;
}

struct Unknown800E349C;


struct Unknown800E349C {
    unsigned char unk_000[0x9C];
    int word_09C;
    int word_0A0;
    unsigned char unk_0A4[0x344 - 0xA4];
    short half_344;
    unsigned char unk_346[2];
    unsigned char byte_348;
    unsigned char unk_349;
    unsigned char byte_34A;
};

/* func_800E349C -- clears five fields of the object it is handed and returns nothing.
 *
 * Every store is of `$zero`, so this writes zeros and reads nothing back; the widths the
 * cartridge uses are what fix the types. Two words go out at 0x09C and 0x0A0, one halfword at
 * 0x344, and two single bytes at 0x34A and 0x348 -- in that order, the last of them in the
 * return's delay slot. The two bytes are written high one first, which is the order they were
 * written in rather than the order they sit in, so they are separate fields and not one pair.
 * Nothing else in the image says what any of them hold, so the struct is a placeholder that
 * names each field for its width and leaves the gaps between them opaque.
 */



void func_800E349C(struct Unknown800E349C *self) {
    self->word_09C = 0;
    self->word_0A0 = 0;
    self->half_344 = 0;
    self->byte_34A = 0;
    self->byte_348 = 0;
}
