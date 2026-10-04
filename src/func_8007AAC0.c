#include "span_1000/code_8007A470.h"
#include "types.h"

struct S;
typedef struct S S;



struct S {
    char pad[0x204];
    int unk204;
};

/* func_8007AAC0 -- returns the field at 0x204 of the object D_801B4ABC points to, or 0 when there is none. */


extern S *D_801B4ABC;
int func_8007AAC0(void) {
    if (D_801B4ABC) {
        return D_801B4ABC->unk204;
    }
    return 0;
}
