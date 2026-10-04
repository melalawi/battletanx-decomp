#include "span_1000/code_80119B60.h"
#include "types.h"

struct Node;
struct Owner;
struct Shape_func_80119B60;






struct Node {
    struct Shape_func_80119B60 *src;
    short h4;
    unsigned char pad6;
    unsigned char b7;
    unsigned char b8;
    unsigned char b9;
    unsigned char padA[6];
};
struct Owner {
    unsigned char pad0[0x60];
    struct Node *nodes;
};
struct Shape_func_80119B60 {
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned char pad3[9];
    short hC;
};







void func_80119B60(struct Owner *owner, struct Shape_func_80119B60 *src, int index) {
    owner->nodes[index].src = src;
    owner->nodes[index].b7 = src->b1;
    owner->nodes[index].b9 = src->b0;
    owner->nodes[index].b8 = src->b2;
    owner->nodes[index].h4 = src->hC;
}
