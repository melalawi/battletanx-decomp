#include "span_1000/code_800E21E4.h"
#include "types.h"

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
