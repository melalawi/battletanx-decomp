#ifndef UNBAKE_FUNC_8011588C_H
#define UNBAKE_FUNC_8011588C_H
#include "types.h"

struct Obj_func_8011588C;
typedef struct Obj_func_8011588C Obj_func_8011588C;
typedef struct Target_func_8011588C Target_func_8011588C;

struct Target_func_8011588C;





struct Obj_func_8011588C {
    char pad0[0x4];
    void *unk_4;
    void *unk_8;
    char pad0C[0x65 - 0x0C];
    unsigned char unk_65;
};
struct Target_func_8011588C {
    char pad0[0x1C];
    unsigned short unk_1C;
    unsigned short unk_1E;
};
#endif
