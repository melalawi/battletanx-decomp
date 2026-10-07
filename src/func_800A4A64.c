#include "common/draft_fields_func_800A4A64.h"
#include "span_1000/code_800A27D0.h"
#include "types.h"
/* func_800A4A64 -- appends arg1's two floats to the looked-up object's pair list (count at 0x1AF,
 * stopping at one entry) and keeps the first entry's id from func_800A6AB4 at 0x1B8. */


s32 func_8007AAB0();
void *func_800A6688();
s32 func_800A6AB4();

void func_800A4A64(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 id;
    u8 count;
    void *obj;
    f32 *arg1_4;

    if (arg0 < func_8007AAB0()) {
        id = 8;
        obj = func_800A6688(arg0 & 0xFFFF);
        count = ((struct Measured_func_800A4A64_cda16eb6f0a3 *)(obj))->value;
        if (count != 1) {
            arg1_4 = (f32 *) arg1 + 1;
            ((struct Measured_func_800A4A64_00ccaa86bd0b *)(obj + count * id))->value = *(f32 *) arg1_4;
            ((struct Measured_func_800A4A64_c3a3680c3ebf *)(obj + ((struct Measured_func_800A4A64_cda16eb6f0a3 *)(obj))->value * id))->value = ((struct Measured_func_800A4A64_0826b8651d57 *)(arg1))->value;
            id = func_800A6AB4(arg0 & 0xFF, arg1, arg2, arg3);
            if (((struct Measured_func_800A4A64_cda16eb6f0a3 *)(obj))->value == 0) {
                ((struct Measured_func_800A4A64_99073b2fcbeb *)(obj))->value = id;
            }
            ((struct Measured_func_800A4A64_cda16eb6f0a3 *)(obj))->value = ((struct Measured_func_800A4A64_cda16eb6f0a3 *)(obj))->value + 1;
        }
    }
}
