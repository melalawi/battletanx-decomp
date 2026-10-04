#include "span_1000/code_800A27D0.h"
#include "types.h"
/* func_800A4A64 -- appends arg1's two floats to the looked-up object's pair list (count at 0x1AF,
 * stopping at one entry) and keeps the first entry's id from func_800A6AB4 at 0x1B8. */

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_8007AAB0();
void *func_800A6688();
s32 func_800A6AB4();

void func_800A4A64(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 id;
    u8 count;
    void *obj;
    s8 *arg1_4;

    if (arg0 < func_8007AAB0()) {
        id = 8;
        obj = func_800A6688(arg0 & 0xFFFF);
        count = FIELD(obj, u8 *, 0x1AF);
        if (count != 1) {
            arg1_4 = (s8 *) arg1 + 4;
            FIELD(obj + count * id, f32 *, 0x1B4) = *(f32 *) arg1_4;
            FIELD(obj + FIELD(obj, u8 *, 0x1AF) * id, f32 *, 0x1B0) = FIELD(arg1, f32 *, 0);
            id = func_800A6AB4(arg0 & 0xFF, arg1, arg2, arg3);
            if (FIELD(obj, u8 *, 0x1AF) == 0) {
                FIELD(obj, s32 *, 0x1B8) = id;
            }
            FIELD(obj, u8 *, 0x1AF) = FIELD(obj, u8 *, 0x1AF) + 1;
        }
    }
}
