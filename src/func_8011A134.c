#include "span_1000/code_801199A0.h"
#include "types.h"
#include "types.h"
#include "types.h"

struct L;
typedef struct L L;
typedef struct N N;

struct N;





struct L {
    char pad[0x10];
    N *head;
};
struct N {
    char pad[0x2C];
    struct N *next;
};


struct C;
typedef struct C C;
typedef struct Shape_func_800A72C8 Shape_func_800A72C8;

struct Shape_func_800A72C8;





struct C {
    char pad[0xC];
    unsigned char c;
};
struct Shape_func_800A72C8 {
    char pad[0x98];
    N *head;
};


struct B;
struct Elem;
struct Shape_func_8011A134;






struct B {
    char pad0[0x60];
    struct Elem *unk60;
};
struct Elem {
    char pad0[7];
    unsigned char unk7;
    char pad8[8];
};
struct Shape_func_8011A134 {
    char pad0[0x20];
    struct C *unk20;
    char pad24[0xD];
    unsigned char unk31;
};

/*
 * Clamps a brightness-like byte: it indexes a 16-byte table held at b->unk60 by
 * the unsigned byte a->unk31, adds byte 7 of that entry to byte 0xC of the object
 * a->unk20 points at, subtracts 0x40, then clamps the result into 0..0x7F and
 * returns it as a byte.
 * Types came from the load widths: lbu for a->unk31, entry+7 and sub+0xC makes all
 * three unsigned char; lw for a->unk20 and b->unk60 makes them pointers; the
 * `sll 4` on the index fixes the table's element stride at 16 bytes; and the final
 * `andi 0xFF` on the return value fixes the return type as unsigned char.
 */








unsigned char func_8011A134(struct Shape_func_8011A134 *a, struct B *b) {
    int v;

    v = b->unk60[a->unk31].unk7 + a->unk20->c;
    v -= 0x40;
    if (v <= 0) {
        v = 0;
    }
    if (v >= 0x7F) {
        v = 0x7F;
    }
    return v;
}
