#include "span_1000/code_800A8940.h"
/* func_800A9B44 -- sums the bytes from offset 4 to 0xFF of a block. */

int func_800A9B44(unsigned char *arg0) {
    int sum = 0;
    int i;
    for (i = 4; i < 0x100; i++) {
        sum += arg0[i];
    }
    return sum;
}
