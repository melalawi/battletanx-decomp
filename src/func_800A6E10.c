#include "span_1000/code_800A51E8.h"
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

/* func_800A6E10 -- counts the nodes of the list held at 0x10. */



int func_800A6E10(L *arg0) {
    N *n = arg0->head;
    int count = 0;
    while (n != 0) {
        n = n->next;
        count++;
    }
    return count;
}
