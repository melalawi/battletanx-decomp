#ifndef UNBAKE_FUNC_8011A134_H
#define UNBAKE_FUNC_8011A134_H
#include "types.h"
#include "shared/func_800a72c8.h"

struct B;
struct Elem;
struct Shape_func_8011A134;






struct B {
    char pad0[0x60];
    struct Elem *unk60;
};
struct Elem {
    char pad0[7];
    unsigned char unk7;
    char pad8[8];
};
struct Shape_func_8011A134 {
    char pad0[0x20];
    struct C *unk20;
    char pad24[0xD];
    unsigned char unk31;
};
#endif
