#include "span_1000/code_800A70E0.h"
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

/* func_800A72C8 -- hands every node of the list at 0x98 to func_800A6E30 with the byte at 0xC of the second argument, then empties the list. */




extern void func_800A6E30(N *, unsigned char);
void func_800A72C8(Shape_func_800A72C8 *l, C *c) {
    N *n = l->head;
    N *next;
    while (n != 0) {
        next = n->next;
        func_800A6E30(n, c->c);
        n = next;
    }
    l->head = 0;
}
