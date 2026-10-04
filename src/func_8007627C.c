#include "span_1000/code_80076000.h"
/* func_8007627C -- copies n bytes between two byte-addressed spaces, a byte at a time until the source is word-aligned, then a word at a time split into four byte stores, then the tail. */


extern unsigned int func_800760A0(unsigned int a);

void func_8007627C(unsigned int src, unsigned int dst, unsigned int n) {
    unsigned int w;
    while (n != 0 && (src & 3)) {
        func_80076240(dst++, func_80076124(src++));
        n--;
    }
    while (n >= 4) {
        w = func_800760A0(src);
        func_80076240(dst++, w >> 24);
        func_80076240(dst++, w >> 16);
        func_80076240(dst++, w >> 8);
        func_80076240(dst++, w);
        src += 4;
        n -= 4;
    }
    while (n != 0) {
        func_80076240(dst++, func_80076124(src++));
        n--;
    }
}
