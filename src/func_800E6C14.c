#include "span_1000/code_800E5FA8.h"
#include "types.h"

struct O;
typedef struct O O;
typedef struct T T;

struct T;





struct O {
    char pad[4];
    struct T *t;
    char pad2[0x18];
    float f;
};
struct T {
    char pad[0x14C];
    unsigned int v;
};

/* func_800E6C14 -- stores an object's float field, converted to an unsigned integer, into the record the object points to, and returns -1. */



int func_800E6C14(O *o) {
    o->t->v = o->f;
    return -1;
}
