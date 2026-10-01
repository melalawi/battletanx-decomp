#ifndef FUNC_800A42A4_H
#define FUNC_800A42A4_H

#include "types.h"

/* Partial layout: the lw at 800A42A4 reads the word at offset 0xF4. */
struct Unknown800A42A4 {
    u8 padding[0xF4];
    s32 value;
};

#endif
