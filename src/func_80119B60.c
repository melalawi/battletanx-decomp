struct Src {
    /* 0x0 */ unsigned char b0;
    /* 0x1 */ unsigned char b1;
    /* 0x2 */ unsigned char b2;
    /* 0x3 */ unsigned char pad3[9];
    /* 0xC */ short hC;
};

struct Node {
    /* 0x0 */ struct Src *src;
    /* 0x4 */ short h4;
    /* 0x6 */ unsigned char pad6;
    /* 0x7 */ unsigned char b7;
    /* 0x8 */ unsigned char b8;
    /* 0x9 */ unsigned char b9;
    /* 0xA */ unsigned char padA[6];
};

struct Owner {
    /* 0x00 */ unsigned char pad0[0x60];
    /* 0x60 */ struct Node *nodes;
};

void func_80119B60(struct Owner *owner, struct Src *src, int index) {
    owner->nodes[index].src = src;
    owner->nodes[index].b7 = src->b1;
    owner->nodes[index].b9 = src->b0;
    owner->nodes[index].b8 = src->b2;
    owner->nodes[index].h4 = src->hC;
}
