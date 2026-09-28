/* func_8011B2A4 -- walks the owner's entry array once per entry, zeroing each entry's first word
 * and then calling func_80119BB4 with the owner and the index. The count at 0x34 is read with lbu
 * on every iteration, so it is an unsigned char; the entry stride of 0x10 fixes the array element
 * size and the sw fixes the zeroed field as a word.
 */
typedef struct {
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_C;
} Entry;

typedef struct {
    char pad0[0x34];
    unsigned char count;
    char pad1[0x60 - 0x35];
    Entry *entries;
} Owner;

extern void func_80119BB4(Owner *, int);

void func_8011B2A4(Owner *owner) {
    int i;

    for (i = 0; i < owner->count; i++) {
        owner->entries[i].unk_0 = 0;
        func_80119BB4(owner, i);
    }
}
