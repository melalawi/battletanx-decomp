#include "span_1000/code_800A27D0.h"
#include "types.h"
#include "callback_word.h"

struct A;
typedef struct A A;



struct A {
    char pad[0xB0];
    float b0;
    char pad2[4];
    float b8;
};

/* func_800A4254 -- the value func_800F3BE4 gives for the float at 0xB0, negated when the float at 0xB8 is negative, as a halfword. */

extern int func_800F3BE4(float);

unsigned short func_800A4254(A *a) {
    unsigned short r;
    if (a->b8 < 0.0f) {
        r = -func_800F3BE4(a->b0);
    } else {
        r = func_800F3BE4(a->b0);
    }
    return r;
}

struct Unknown800A42A4;


struct Unknown800A42A4 {
    u8 padding[0xF4];
    s32 value;
};

/* func_800A42A4 -- returns the word at offset 0xF4 of its argument. */


s32 func_800A42A4(struct Unknown800A42A4 *arg0) {
    return arg0->value;
}

s32 func_800A42B0(s32 arg0) {
    return ((CallbackWord *)arg0)->value;
}
