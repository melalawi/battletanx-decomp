#ifndef UNBAKE_FUNC_8011ECA4_H
#define UNBAKE_FUNC_8011ECA4_H
#include "types.h"
#include "shared/func_80119f70.h"

struct Shape_func_8011ECA4;
typedef struct Shape_func_8011ECA4 Shape_func_8011ECA4;
typedef struct Shape_func_8011ECA4_2 Shape_func_8011ECA4_2;

struct Shape_func_8011ECA4_2;





struct Shape_func_8011ECA4 {
    struct Shape_func_8011ECA4_2 *owner;
    char pad04[0x1A - 0x04];
    short unk_1A;
    char pad1C[0x38 - 0x1C];
    int unk_38;
    struct Shape_func_80119F70 *head;
    struct Shape_func_80119F70 *tail;
    char pad44[0x48 - 0x44];
    int unk_48;
};
struct Shape_func_8011ECA4_2 {
    char pad0[0x8];
    void (*unk_8)(struct Shape_func_8011ECA4_2 *, int, void *);
};
#endif
