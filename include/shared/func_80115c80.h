#ifndef UNBAKE_FUNC_80115C80_H
#define UNBAKE_FUNC_80115C80_H
#include "types.h"

struct Obj_func_80115C80;
typedef struct Obj_func_80115C80 Obj_func_80115C80;



struct Obj_func_80115C80 {
    char pad0[0x4];
    void *unk_4;
    void *unk_8;
    unsigned char unk_C[0x20];
    char pad2C[0x65 - 0x2C];
    unsigned char unk_65;
};
#endif
