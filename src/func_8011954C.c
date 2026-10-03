#include "shared/func_8011954c.h"
/* Copies three fields out of the source record into the destination: two
   words and one signed halfword. The lw/sw pair fixed the words as 32-bit
   and the lh/sh pair fixed the halfword as a signed short. */




void func_8011954C(Dest *dst, Src *src) {
    dst->unk8 = src->unk0;
    dst->unk1A = src->unkC;
    dst->unkC = src->unk4;
}
