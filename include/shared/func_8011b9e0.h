#ifndef UNBAKE_FUNC_8011B9E0_H
#define UNBAKE_FUNC_8011B9E0_H
#include "types.h"
#include "shared/typemap.h"

struct Command;
typedef struct Command Command;
typedef struct Shape_func_8011B9E0_2 Shape_func_8011B9E0_2;

struct Shape_func_8011B9E0_2;





struct Command {
    short type;
    char unk2[0xE];
};
struct Shape_func_8011B9E0_2 {
    char unk0[0x48];
    struct Shape_func_8011B9E0 queue;
};
#endif
