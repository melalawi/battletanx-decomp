#include "shared/func_800a72c8.h"
#include "shared/func_800a6e10.h"
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
