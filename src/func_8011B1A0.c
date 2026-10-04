#include "span_1000/code_80119B60.h"
#include "types.h"

struct Shape_func_8011B1A0;
typedef struct Shape_func_8011B1A0 Shape_func_8011B1A0;
typedef struct Shape_func_8011B1A0_2 Shape_func_8011B1A0_2;
typedef struct Target Target;

struct Shape_func_8011B1A0_2;

struct Target;







struct Shape_func_8011B1A0 {
    char pad0[0x48];
    int unk_48;
    char pad4C[0x50 - 0x4C];
    struct Shape_func_8011B1A0_2 *unk_50;
    char pad54[0x78 - 0x54];
    void (*unk_78)(void *);
};
struct Shape_func_8011B1A0_2 {
    struct Shape_func_8011B1A0_2 *next;
    char pad04[0x08 - 0x04];
    int unk_8;
    short unk_C;
    char pad0E[0x10 - 0x0E];
    struct Target *unk_10;
    void *unk_14;
};
struct Target {
    char pad0[0x37];
    unsigned char unk_37;
};

/* func_8011B1A0 -- unhooks every node of the owner's list at 0x50 that belongs to one target and is
 * of kind 0x16 or 0x17: it calls the owner's callback at 0x78 with the node's 0x14 word, retires the
 * node through func_8011C150, folds the node's 0x8 count into its successor's, returns it to the
 * owner's free list at 0x48 through func_8011C180, clears bit 0 or bit 1 of the target's flag byte
 * according to the kind, and stops early once that byte reaches zero. The lh at 0xC fixes the kind
 * as a signed short and the lbu/sb at 0x37 fixes the flag as one unsigned byte.
 */






extern void func_8011C150(Shape_func_8011B1A0_2 *);
extern void func_8011C180(Shape_func_8011B1A0_2 *, int *);

void func_8011B1A0(Shape_func_8011B1A0 *owner, Target *target) {
    Shape_func_8011B1A0_2 *node;
    Shape_func_8011B1A0_2 *next;
    short kind;

    for (node = owner->unk_50; node != 0; node = next) {
        kind = node->unk_C;
        next = node->next;
        if (kind == 0x16 || kind == 0x17) {
            if (node->unk_10 == target) {
                owner->unk_78(node->unk_14);
                func_8011C150(node);
                if (next != 0) {
                    next->unk_8 += node->unk_8;
                }
                func_8011C180(node, &owner->unk_48);
                if (kind == 0x16) {
                    target->unk_37 &= 0xFE;
                } else {
                    target->unk_37 &= 0xFD;
                }
                if (target->unk_37 == 0) {
                    return;
                }
            }
        }
    }
}

struct Shape_func_8011B2A4_2;
typedef struct Shape_func_8011B2A4_2 Shape_func_8011B2A4_2;
typedef struct Shape_func_8011B2A4 Shape_func_8011B2A4;

struct Shape_func_8011B2A4;





struct Shape_func_8011B2A4_2 {
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_C;
};
struct Shape_func_8011B2A4 {
    char pad0[0x34];
    unsigned char count;
    char pad1[0x60 - 0x35];
    struct Shape_func_8011B2A4_2 *entries;
};

/* func_8011B2A4 -- walks the owner's entry array once per entry, zeroing each entry's first word
 * and then calling func_80119BB4 with the owner and the index. The count at 0x34 is read with lbu
 * on every iteration, so it is an unsigned char; the entry stride of 0x10 fixes the array element
 * size and the sw fixes the zeroed field as a word.
 */




extern void func_80119BB4(Shape_func_8011B2A4 *, int);

void func_8011B2A4(Shape_func_8011B2A4 *owner) {
    int i;

    for (i = 0; i < owner->count; i++) {
        owner->entries[i].unk_0 = 0;
        func_80119BB4(owner, i);
    }
}
