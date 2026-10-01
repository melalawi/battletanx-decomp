#ifndef UNBAKE_STRUCTS_H
#define UNBAKE_STRUCTS_H
#include "types.h"

struct ResetState {
    char pad[0x40];
    int field40;
    int field44;
};

struct Unknown800A42A4 {
    u8 padding[0xF4];
    s32 value;
};

#endif
