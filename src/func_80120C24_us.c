#ifdef NON_MATCHING
#include "abi.h"
#include "audio_callbacks.h"
#include "types.h"
#include "bt_abi.h"
#include "span_1000/code_801207B0.h"
#include "common/draft_fields_func_80120C24_us.h"

/* func_801207B0_us: types.declaration: solved callee prototype */

/* func_80120A98_us: types.abi.arguments: some mapped callers do not establish every consumed argument value; types.abi.word_return: v0 carries one O32 word; semantic return unknown or conflicting */
extern int func_80120A98_us(void *, unsigned int, int, int, void *);
/* func_80121F10: types.declaration: solved callee prototype */
extern unsigned int func_80121F10(void *vaddr);

                                                  /* size = 0x60 */

void *func_80120C24_us(void *arg0, void *arg1, s32 arg2, s32 arg3, void *arg4) {
    s32 sp28;
    s32 sp2C;
    void *sp30;
    s32 sp38;
    f32 sp44;
    void *sp5C;
    f32 temp_f12;
    f32 temp_f2;
    s32 temp_f16;
    s32 temp_t0;
    s32 temp_t3;
    s32 temp_t8;
    void *temp_t6;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;
    void *var_v1;

    if (((struct Measured_func_80120C24_us_028cd1a07375 *)(arg1))->value != 0) {
        sp38 = ((struct Measured_func_80120C24_us_4466dbb779d0 *)(arg1))->value - ((struct Measured_func_80120C24_us_d3723d959b3b *)(arg1))->value;
        temp_f2 = (f32) (1.0 - (f64) ((f32) (s32) ((func_801207B0_us(arg1, arg3) / (f32) sp38) * 32768.0f) / 32768.0f));
        sp44 = temp_f2;
        temp_v0 = ((struct Measured_func_80120C24_us_028cd1a07375 *)(arg1))->value;
        temp_f12 = ((struct Measured_func_80120C24_us_f8165560a06f *)(temp_v0))->value + (temp_f2 * (f32) arg3);
        temp_f16 = (s32) temp_f12;
        ((struct Measured_func_80120C24_us_f8165560a06f *)(temp_v0))->value = (f32) (temp_f12 - (f32) temp_f16);
        sp2C = temp_f16;
        temp_t0 = ((struct Measured_func_80120C24_us_7705078627e3 *)(arg0))->value + ((((struct Measured_func_80120C24_us_4466dbb779d0 *)(arg1))->value - ((struct Measured_func_80120C24_us_7705078627e3 *)(arg1))->value) * -2);
        temp_t8 = (s32) (temp_t0 & 7) >> 1;
        temp_t3 = temp_t8 * 2;
        sp28 = temp_t3;
        temp_v0_2 = func_80120A98_us(arg0, temp_t0 - temp_t3, 0x280, temp_f16 + temp_t8, arg4);
        temp_t6 = temp_v0_2 + 8;
        aSetBuffer((Acmd *)temp_v0_2, 0, temp_t3 + 0x280, arg2, arg3 * 2);
        sp30 = temp_t6;
        temp_v1 = temp_v0_2 + 0x10;

        sp5C = temp_v1;
        var_v1 = temp_v1;
        aResample((Acmd *)temp_t6,
            ((struct Measured_func_80120C24_us_0b0ad7aac4bc *)(((struct Measured_func_80120C24_us_028cd1a07375 *)arg1)->value))->value,
            (s32)(sp44 * 32768.0f),
            func_80121F10(((struct Measured_func_80120C24_us_5a0991979bf8 *)(((struct Measured_func_80120C24_us_028cd1a07375 *)arg1)->value))->value));
        ((struct Measured_func_80120C24_us_0b0ad7aac4bc *)(((struct Measured_func_80120C24_us_028cd1a07375 *)(arg1))->value))->value = 0;
        ((struct Measured_func_80120C24_us_7705078627e3 *)(arg1))->value = (s32) ((((struct Measured_func_80120C24_us_7705078627e3 *)(arg1))->value + temp_f16) - arg3);
    } else {
        var_v1 = func_80120A98_us(arg0, ((struct Measured_func_80120C24_us_7705078627e3 *)(arg0))->value + (((struct Measured_func_80120C24_us_4466dbb779d0 *)(arg1))->value * -2), arg2, arg3, arg4);
    }
    return var_v1;
}
#endif /* NON_MATCHING */
