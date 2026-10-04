#include "span_1000/code_800A2A28.h"
#include "types.h"

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
