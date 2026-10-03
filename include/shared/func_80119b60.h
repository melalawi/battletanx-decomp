#ifndef UNBAKE_FUNC_80119B60_H
#define UNBAKE_FUNC_80119B60_H
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
#endif
