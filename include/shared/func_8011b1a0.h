#ifndef UNBAKE_FUNC_8011B1A0_H
#define UNBAKE_FUNC_8011B1A0_H
#include "types.h"

struct Shape_func_8011B1A0;
typedef struct Shape_func_8011B1A0 Shape_func_8011B1A0;
typedef struct Shape_func_8011B1A0_2 Shape_func_8011B1A0_2;
typedef struct Target Target;

struct Shape_func_8011B1A0_2;

struct Target;







struct Shape_func_8011B1A0 {
    char pad0[0x48];
    int unk_48;
    char pad4C[0x50 - 0x4C];
    struct Shape_func_8011B1A0_2 *unk_50;
    char pad54[0x78 - 0x54];
    void (*unk_78)(void *);
};
struct Shape_func_8011B1A0_2 {
    struct Shape_func_8011B1A0_2 *next;
    char pad04[0x08 - 0x04];
    int unk_8;
    short unk_C;
    char pad0E[0x10 - 0x0E];
    struct Target *unk_10;
    void *unk_14;
};
struct Target {
    char pad0[0x37];
    unsigned char unk_37;
};
#endif
