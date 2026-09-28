/* func_8011B7BC -- clears the five words at the head of the accumulator, then walks `count`
 * consecutive 0x1C-byte entries and hands each one, with the accumulator, to func_8011C180. The
 * five sw of $zero fix the head as five words; the 0x1C add per iteration fixes the entry stride.
 */

struct Accum {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
};

struct Entry {
    unsigned char unk_00[0x1C];
};

extern void func_8011C180(struct Entry *, struct Accum *);

void func_8011B7BC(struct Accum *accum, struct Entry *entries, int count) {
    int i;
    struct Entry *entry;

    accum->unk_10 = 0;
    accum->unk_08 = 0;
    accum->unk_0C = 0;
    accum->unk_00 = 0;
    accum->unk_04 = 0;
    i = 0;
    if (count > 0) {
        entry = entries;
        do {
            func_8011C180(entry, accum);
            i++;
            entry++;
        } while (i < count);
    }
}
