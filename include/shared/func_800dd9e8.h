#ifndef BATTLETANX_FUNC_800DD9E8_H
#define BATTLETANX_FUNC_800DD9E8_H
#include "types.h"

/* func_800DD970_us allocates 32 bytes, clears completion, copies two
 * coordinates, supplies the third, and stores its second argument. */
struct Func800DD970State {
    u8 reserved[12];
    s32 completion;
    f32 coordinates[3];
    void *payload;
};

extern void func_800DD9E8_us(struct Func800DD970State *state, s32 *result);
#endif
