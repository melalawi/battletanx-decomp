#ifndef UNBAKE_FUNC_80119BB4_H
#define UNBAKE_FUNC_80119BB4_H
#include "types.h"

struct Entry;
typedef struct Entry Entry;
typedef struct Shape_func_80119BB4 Shape_func_80119BB4;

struct Shape_func_80119BB4;





struct Entry {
    char unk0[4];
    short unk4;
    unsigned char unk6;
    unsigned char unk7;
    unsigned char unk8;
    unsigned char unk9;
    unsigned char unkA;
    unsigned char unkB;
    float unkC;
};
struct Shape_func_80119BB4 {
    char unk0[0x60];
    struct Entry *entries;
};
#endif
