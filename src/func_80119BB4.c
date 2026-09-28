/* Resets one 16-byte entry of the array hanging off offset 0x60 of the
   object to its default field values, ending with a 1.0f scale. The sb/sh/
   swc1 widths fixed the entry fields as bytes, a short at 0x4 and a float
   at 0xC, and the sll by 4 of the index fixed the entry size at 16 bytes. */
typedef struct Entry {
    char unk0[4];
    short unk4;
    unsigned char unk6;
    unsigned char unk7;
    unsigned char unk8;
    unsigned char unk9;
    unsigned char unkA;
    unsigned char unkB;
    float unkC;
} Entry;

typedef struct Owner {
    char unk0[0x60];
    Entry *entries;
} Owner;

void func_80119BB4(Owner *owner, int index) {
    owner->entries[index].unk6 = 0;
    owner->entries[index].unkA = 0;
    owner->entries[index].unk7 = 0x40;
    owner->entries[index].unk9 = 0x7F;
    owner->entries[index].unk8 = 5;
    owner->entries[index].unkB = 0;
    owner->entries[index].unk4 = 0xC8;
    owner->entries[index].unkC = 1.0f;
}
