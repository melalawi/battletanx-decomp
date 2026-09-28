/* func_800A6E10 -- counts the nodes of the list held at 0x10. */

typedef struct N { char pad[0x2C]; struct N *next; } N;
typedef struct { char pad[0x10]; N *head; } L;
int func_800A6E10(L *arg0) {
    N *n = arg0->head;
    int count = 0;
    while (n != 0) {
        n = n->next;
        count++;
    }
    return count;
}
