#include "span_1000/code_80119530.h"
#include "types.h"

struct Dest;
typedef struct Dest Dest;
typedef struct Src Src;

struct Src;





struct Dest {
    char unk0[8];
    int unk8;
    int unkC;
    char unk10[0xA];
    short unk1A;
};
struct Src {
    int unk0;
    int unk4;
    char unk8[4];
    short unkC;
};

/* Copies three fields out of the source record into the destination: two
   words and one signed halfword. The lw/sw pair fixed the words as 32-bit
   and the lh/sh pair fixed the halfword as a signed short. */




void func_8011954C(Dest *dst, Src *src) {
    dst->unk8 = src->unk0;
    dst->unk1A = src->unkC;
    dst->unkC = src->unk4;
}
