#include "span_1000/code_800A27D0.h"
#include "types.h"

struct Unknown800A4D1C;


struct Unknown800A4D1C {
    int unk_000[130];
    int countdown;
};

/* func_800A4D1C -- the first function in this cartridge matched byte for byte.
 *
 * A saturating countdown on one field: decrement it, but never below zero. The field sits at
 * 0x208 in whatever the caller passes, and it is signed -- the cartridge tests it with `blez`,
 * which is the signed comparison.
 *
 * The struct is a placeholder. Only the one field at 0x208 is known, from this function alone;
 * everything ahead of it is padding until a caller gives it a shape. The name follows the same
 * rule: it is the address, because nothing yet says what this counter counts.
 *
 * Written to compile under the IDO described in docs/toolchain.md at -O2; see that file for the
 * byte check, and `tools/ido/verify-function.sh func_800A4D1C` to rerun it.
 */



void func_800A4D1C(struct Unknown800A4D1C *self) {
    int remaining = self->countdown;

    if (remaining > 0) {
        remaining--;
        self->countdown = remaining;
    }
}
