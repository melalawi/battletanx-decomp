#include "shared/func_80119b60.h"






void func_80119B60(struct Owner *owner, struct Shape_func_80119B60 *src, int index) {
    owner->nodes[index].src = src;
    owner->nodes[index].b7 = src->b1;
    owner->nodes[index].b9 = src->b0;
    owner->nodes[index].b8 = src->b2;
    owner->nodes[index].h4 = src->hC;
}
