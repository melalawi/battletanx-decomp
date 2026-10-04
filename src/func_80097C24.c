#include "span_1000/code_80096D04.h"
#include "types.h"

struct Block;
typedef struct Block Block;



struct Block {
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    int unk_38;
};

/* func_80097C24 -- clears a 0x3C-byte record reached through the first argument by
 * storing $zero into all fifteen words from 0x0 to 0x38. Every store is `sw`, so
 * every field is a 32-bit word; the cartridge writes them in the order 0,4,8,
 * 0x14,0x18,0x20,0xC,0x10,0x1C,0x2C,0x30,0x24,0x28,0x34,0x38, which is the order
 * kept here.
 */


void func_80097C24(Block *b) {
    b->unk_0 = 0;
    b->unk_4 = 0;
    b->unk_8 = 0;
    b->unk_14 = 0;
    b->unk_18 = 0;
    b->unk_20 = 0;
    b->unk_C = 0;
    b->unk_10 = 0;
    b->unk_1C = 0;
    b->unk_2C = 0;
    b->unk_30 = 0;
    b->unk_24 = 0;
    b->unk_28 = 0;
    b->unk_34 = 0;
    b->unk_38 = 0;
}
