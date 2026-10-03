#ifndef UNBAKE_FUNC_800A6E10_H
#define UNBAKE_FUNC_800A6E10_H
#include "types.h"

struct L;
typedef struct L L;
typedef struct N N;

struct N;





struct L {
    char pad[0x10];
    N *head;
};
struct N {
    char pad[0x2C];
    struct N *next;
};
#endif
