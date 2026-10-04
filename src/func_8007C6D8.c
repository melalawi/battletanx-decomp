#include "span_1000/code_8007A470.h"
/* func_8007C6D8 -- whether the state D_801B4ABC points at is one of 3 to 6. */

extern unsigned int *D_801B4ABC;
int func_8007C6D8(void) {
    switch (*D_801B4ABC) {
    case 3: case 4: case 5: case 6: return 1;
    }
    return 0;
}
