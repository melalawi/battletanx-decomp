#ifndef UNBAKE_FUNC_8011B2A4_H
#define UNBAKE_FUNC_8011B2A4_H
#include "types.h"

struct Shape_func_8011B2A4_2;
typedef struct Shape_func_8011B2A4_2 Shape_func_8011B2A4_2;
typedef struct Shape_func_8011B2A4 Shape_func_8011B2A4;

struct Shape_func_8011B2A4;





struct Shape_func_8011B2A4_2 {
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_C;
};
struct Shape_func_8011B2A4 {
    char pad0[0x34];
    unsigned char count;
    char pad1[0x60 - 0x35];
    struct Shape_func_8011B2A4_2 *entries;
};
#endif
