/* func_8011DC98 -- drains the owner's single-entry list at 0x14: while that word is non-zero it
 * hands the entry to func_8011C150, then to func_8011C180 together with the address of the owner's
 * field at 0x04, and re-reads 0x14. The lw/sw widths make every field a word, and the loop keeping
 * the owner and the 0x04 address in $s1/$s2 across the two calls fixes them as one pointer each.
 */

struct Owner;

struct Child {
    int unk_00;
};

struct Owner {
    int unk_00;            /* 0x00 */
    int unk_04;            /* 0x04 */
    int unk_08;            /* 0x08 */
    int unk_0C;            /* 0x0C */
    int unk_10;            /* 0x10 */
    struct Child *first;   /* 0x14 */
};

extern void func_8011C150(struct Child *);
extern void func_8011C180(struct Child *, int *);

void func_8011DC98(struct Owner *owner) {
    struct Child *child;

    child = owner->first;
    while (child != 0) {
        func_8011C150(child);
        func_8011C180(child, &owner->unk_04);
        child = owner->first;
    }
}
