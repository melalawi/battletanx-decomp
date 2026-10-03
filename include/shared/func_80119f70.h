#ifndef UNBAKE_FUNC_80119F70_H
#define UNBAKE_FUNC_80119F70_H
#include "types.h"

struct Heap;
struct Shape_func_80119F70;




struct Heap {
    unsigned char unk_000[0x64];
    struct Shape_func_80119F70 *used;
    struct Shape_func_80119F70 *last;
    struct Shape_func_80119F70 *free;
};
struct Shape_func_80119F70 {
    struct Shape_func_80119F70 *next;
};
#endif
