#include "span_1000/code_80119B60.h"
#include "types.h"

struct Entry;
typedef struct Entry Entry;
typedef struct Shape_func_80119BB4 Shape_func_80119BB4;

struct Shape_func_80119BB4;





struct Entry {
    char unk0[4];
    short unk4;
    unsigned char unk6;
    unsigned char unk7;
    unsigned char unk8;
    unsigned char unk9;
    unsigned char unkA;
    unsigned char unkB;
    float unkC;
};
struct Shape_func_80119BB4 {
    char unk0[0x60];
    struct Entry *entries;
};

/* Resets one 16-byte entry of the array hanging off offset 0x60 of the
   object to its default field values, ending with a 1.0f scale. The sb/sh/
   swc1 widths fixed the entry fields as bytes, a short at 0x4 and a float
   at 0xC, and the sll by 4 of the index fixed the entry size at 16 bytes. */




void func_80119BB4(Shape_func_80119BB4 *owner, int index) {
    owner->entries[index].unk6 = 0;
    owner->entries[index].unkA = 0;
    owner->entries[index].unk7 = 0x40;
    owner->entries[index].unk9 = 0x7F;
    owner->entries[index].unk8 = 5;
    owner->entries[index].unkB = 0;
    owner->entries[index].unk4 = 0xC8;
    owner->entries[index].unkC = 1.0f;
}
