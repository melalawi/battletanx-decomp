#include "shared/func_80119f70.h"
/* func_80119F70 -- unlinks one allocation from a heap's in-use list and pushes it onto the free
 * list. The caller hands over the payload address, so the block header is the four bytes ahead of
 * it, which is what the cartridge's `addiu $a2, $a1, -0x4` says. Every field touched is a word, so
 * the three list pointers at 0x064, 0x068 and 0x06C are pointers; the tail pointer at 0x068 is
 * rewound to the predecessor only when the removed block was the tail.
 */




void func_80119F70(struct Heap *heap, void *payload) {
    struct Shape_func_80119F70 *previous;
    struct Shape_func_80119F70 *block;
    struct Shape_func_80119F70 *target;

    previous = 0;
    block = heap->used;
    target = (struct Shape_func_80119F70 *)((unsigned char *)payload - 4);
    while (block != 0) {
        if (block == target) {
            if (previous != 0) {
                previous->next = block->next;
            } else {
                heap->used = block->next;
            }
            if (block == heap->last) {
                heap->last = previous;
            }
            block->next = heap->free;
            heap->free = block;
            return;
        }
        previous = block;
        block = block->next;
    }
}
