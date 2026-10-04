#include "span_1000/code_8008F248.h"
#include "types.h"

struct E;
typedef struct E E;



struct E {
    char pad[8];
    unsigned short a;
    unsigned short b;
    char pad2[4];
};

/* func_800917D8 -- copies the pair of halfwords at 0x8 and 0xA from each of n 16-byte records to another array. */


void func_800917D8(int n, E *src, E *dst) {
    int i;
    for (i = 0; i < n; i++) {
        dst[i].a = src[i].a;
        dst[i].b = src[i].b;
    }
}
