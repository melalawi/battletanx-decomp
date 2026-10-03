#include "shared/func_800e6c14.h"
/* func_800E6C14 -- stores an object's float field, converted to an unsigned integer, into the record the object points to, and returns -1. */



int func_800E6C14(O *o) {
    o->t->v = o->f;
    return -1;
}
