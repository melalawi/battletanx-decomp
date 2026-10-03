#ifndef UNBAKE_FUNC_8007EC38_H
#define UNBAKE_FUNC_8007EC38_H
#include "types.h"

struct Func8007EC38Catalog;
typedef struct Func8007EC38Catalog Func8007EC38Catalog;
typedef struct Func8007EC38Entry Func8007EC38Entry;
typedef struct func_8007EC38_S1 func_8007EC38_S1;
typedef union func_8007EC38_S1_UE8 func_8007EC38_S1_UE8;

struct Func8007EC38Entry;

struct func_8007EC38_S1;

union func_8007EC38_S1_UE8;









struct Func8007EC38Entry {
    s32 threshold;
    char pad4[0x14];
};
union func_8007EC38_S1_UE8 {
    u32 v0;
    s32 v1;
};
struct Func8007EC38Catalog {
    char pad0[0xA4];
    Func8007EC38Entry entries[1];
};
struct func_8007EC38_S1 {
    char pad0[0xD0];
    u16 unkD0;
    char padD0[0xD8 - 0xD0 - sizeof(u16)];
    void * unkD8;
    char padD8[0xE8 - 0xD8 - sizeof(void*)];
    func_8007EC38_S1_UE8 unkE8;
};
#endif
