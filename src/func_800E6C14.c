/* func_800E6C14 -- stores an object's float field, converted to an unsigned integer, into the record the object points to, and returns -1. */

typedef struct { char pad[0x14C]; unsigned int v; } T;
typedef struct { char pad[4]; T *t; char pad2[0x18]; float f; } O;
int func_800E6C14(O *o) {
    o->t->v = o->f;
    return -1;
}
