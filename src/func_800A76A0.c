#include "span_1000/code_800A70E0.h"
#include "types.h"

struct Unknown800A76A0;
typedef struct Unknown800A76A0 Unknown800A76A0;



struct Unknown800A76A0 {
    unsigned char pad0[0x30];
    float unk30;
    float unk34;
    float unk38;
};

/*
 * Copies three consecutive floats into the fields at offsets 0x30, 0x34 and
 * 0x38 of the destination structure.  Every load is `lwc1` and every store
 * `swc1`, so both sides are single-precision floats, and the one
 * floating-point register reused for all three copies is what a named float
 * temporary variable produces.
 */



void func_800A76A0(Unknown800A76A0 *dst, float *src) {
    float value;

    value = src[0];
    dst->unk30 = value;
    value = src[1];
    dst->unk34 = value;
    value = src[2];
    dst->unk38 = value;
}
