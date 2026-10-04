#include "span_1000/code_80090F94.h"
#include "types.h"

struct Unknown800917C4;
typedef struct Unknown800917C4 Unknown800917C4;



struct Unknown800917C4 {
    unsigned char pad0[8];
    unsigned short unk8;
    unsigned short unkA;
};

/*
 * Copies the two 16-bit fields at offsets 8 and 0xA from one structure to
 * another.  Both loads are `lhu` and both stores are `sh`, which fixes the
 * fields as unsigned 16-bit halfwords, and the single register reused for both
 * copies is what a named temporary variable produces.
 */



void func_800917C4(Unknown800917C4 *src, Unknown800917C4 *dst) {
    unsigned short value;

    value = src->unk8;
    dst->unk8 = value;
    value = src->unkA;
    dst->unkA = value;
}
