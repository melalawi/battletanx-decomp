#include "span_1000/code_80077620.h"
#include "types.h"

/* This entry returns the address without reading the object. */
extern unsigned char D_8014E0D0;

s32 func_80078F60_us(void) {
    return (s32) &D_8014E0D0;
}
