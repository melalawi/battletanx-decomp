#ifndef UNBAKE_FUNC_800E9DA4_H
#define UNBAKE_FUNC_800E9DA4_H
#include "types.h"

struct Ent;
typedef struct Ent Ent;
typedef struct Shape_func_800E9DA4 Shape_func_800E9DA4;

struct Shape_func_800E9DA4;





struct Ent {
    char pad0[4];
    struct Shape_func_800E9DA4 *obj;
};
struct Shape_func_800E9DA4 {
    char pad0[0x24];
    f32 x24;
    char pad28[4];
    f32 x2C;
    char pad30[0x6C];
    s32 x9C;
};
#endif
