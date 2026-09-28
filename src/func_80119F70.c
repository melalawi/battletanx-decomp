/* func_80119F70 -- unlinks one allocation from a heap's in-use list and pushes it onto the free
 * list. The caller hands over the payload address, so the block header is the four bytes ahead of
 * it, which is what the cartridge's `addiu $a2, $a1, -0x4` says. Every field touched is a word, so
 * the three list pointers at 0x064, 0x068 and 0x06C are pointers; the tail pointer at 0x068 is
 * rewound to the predecessor only when the removed block was the tail.
 */
struct Block {
    struct Block *next;              /* 0x00 */
};

struct Heap {
    unsigned char unk_000[0x64];
    struct Block *used;              /* 0x064 */
    struct Block *last;              /* 0x068 */
    struct Block *free;              /* 0x06C */
};

void func_80119F70(struct Heap *heap, void *payload) {
    struct Block *previous;
    struct Block *block;
    struct Block *target;

    previous = 0;
    block = heap->used;
    target = (struct Block *)((unsigned char *)payload - 4);
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
