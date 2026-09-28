/* func_800A72C8 -- hands every node of the list at 0x98 to func_800A6E30 with the byte at 0xC of the second argument, then empties the list. */

typedef struct N { char pad[0x2C]; struct N *next; } N;
typedef struct { char pad[0x98]; N *head; } L;
typedef struct { char pad[0xC]; unsigned char c; } C;
extern void func_800A6E30(N *, unsigned char);
void func_800A72C8(L *l, C *c) {
    N *n = l->head;
    N *next;
    while (n != 0) {
        next = n->next;
        func_800A6E30(n, c->c);
        n = next;
    }
    l->head = 0;
}
