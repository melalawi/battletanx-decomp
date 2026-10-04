#include "span_1000/code_800DAD5C.h"
#include "types.h"

/* func_800DD970_us allocates 32 bytes, clears completion, copies two
 * coordinates, supplies the third, and stores its second argument. */
struct Func800DD970State {
    u8 reserved[12];
    s32 completion;
    f32 coordinates[3];
    void *payload;
};




void func_800DD9E8_us(struct Func800DD970State *state, s32 *result) {
    if (state->completion != 0) {
        *result = 2;
    }
}

              /* size 0x0 */

void func_800DDA00_us(void) {

}
