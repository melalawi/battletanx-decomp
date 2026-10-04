#include "span_1000/code_800E3BC0.h"
#include "types.h"

struct Obj;
typedef struct Obj Obj;



struct Obj {
    char pad0[0x34C];
    void *unk_34C;
    char pad350[0x358 - 0x350];
    unsigned char unk_358;
};

/* func_800E3C18 -- records a one-shot value on an object: it stores the argument at 0x34C and clears
 * the byte at 0x358, but only the first time, leaving an already-set 0x34C alone. The sw fixes 0x34C
 * as a word and the sb fixes 0x358 as a single byte. First landing from the cartridge's addu-move
 * region, so its 28 bytes move from not-ruled-out to shown reachable.
 */


void func_800E3C18(Obj *obj, void *value) {
    void *cur;

    cur = obj->unk_34C;
    if (cur == 0) {
        obj->unk_34C = value;
        obj->unk_358 = 0;
    }
}
