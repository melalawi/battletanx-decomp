#ifndef UNBAKE_FUNC_8011C300_H
#define UNBAKE_FUNC_8011C300_H
#include "types.h"

struct Shape_func_8011C300;
typedef struct Shape_func_8011C300 Shape_func_8011C300;
typedef struct Slot Slot;

struct Slot;





struct Shape_func_8011C300 {
    char unk0[0x3C];
    int current;
    struct Slot *slots;
};
struct Slot {
    char unk0[0x28];
    int unk28;
    char unk2C[4];
};
#endif
