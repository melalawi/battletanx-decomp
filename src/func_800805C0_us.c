#include "audio_callbacks.h"
#include "types.h"
#include "span_1000/code_8007EB64.h"

extern unsigned char D_801B6C20; /* opaque address transport */

s32 func_800805C0_us(void) {
    return (s32) &D_801B6C20;
}
