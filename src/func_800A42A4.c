#include "span_1000/code_800A27D0.h"
#include "types.h"

struct Unknown800A42A4;


struct Unknown800A42A4 {
    u8 padding[0xF4];
    s32 value;
};

/* func_800A42A4 -- returns the word at offset 0xF4 of its argument. */
#include "types.h"


s32 func_800A42A4(struct Unknown800A42A4 *arg0) {
    return arg0->value;
}
