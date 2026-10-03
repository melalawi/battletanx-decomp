#ifndef UNBAKE_FUNC_8007ECE8_H
#define UNBAKE_FUNC_8007ECE8_H
#include "types.h"

struct Func8007ECE8Catalog;
typedef struct Func8007ECE8Catalog Func8007ECE8Catalog;
typedef struct Func8007ECE8Entry Func8007ECE8Entry;
typedef struct func_8007ECE8_S1 func_8007ECE8_S1;
typedef union func_8007ECE8_S1_UE8 func_8007ECE8_S1_UE8;

struct Func8007ECE8Entry;

struct func_8007ECE8_S1;

union func_8007ECE8_S1_UE8;









struct Func8007ECE8Entry {
    s32 threshold;
    char pad4[0x14];
};
union func_8007ECE8_S1_UE8 {
    u32 v0;
    s32 v1;
};
struct Func8007ECE8Catalog {
    char pad0[0xA4];
    Func8007ECE8Entry entries[1];
};
struct func_8007ECE8_S1 {
    char pad0[0xD0];
    u16 unkD0;
    char padD0[0xDC - 0xD0 - sizeof(u16)];
    void * unkDC;
    char padDC[0xE8 - 0xDC - sizeof(void*)];
    func_8007ECE8_S1_UE8 unkE8;
};
#endif
