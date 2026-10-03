#ifndef UNBAKE_FUNC_800E6C14_H
#define UNBAKE_FUNC_800E6C14_H
#include "types.h"

struct O;
typedef struct O O;
typedef struct T T;

struct T;





struct O {
    char pad[4];
    struct T *t;
    char pad2[0x18];
    float f;
};
struct T {
    char pad[0x14C];
    unsigned int v;
};
#endif
