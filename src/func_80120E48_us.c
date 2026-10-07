#ifdef NON_MATCHING
#include "common/draft_fields_func_80120E48_us.h"
#include "span_1000/code_801207B0.h"
#include "types.h"

/* func_8011E6B0_us: types.abi.unused_return: no mapped direct caller consumes a result; semantic return unknown */
extern void func_8011E6B0_us(void *);

                                                  /* size = 0x18 */

extern void *D_80145E10;

s32 func_80120E48_us(s32 arg0, s32 arg1, void *arg2) {
    f64 var_f18;
    s16 *temp_a1;
    s32 temp_t0;
    s32 temp_t5;
    s32 temp_t6_2;
    s32 temp_v1;
    u32 temp_t6;
    void *temp_v0;

    temp_v1 = arg1 - 2;
    temp_t6 = temp_v1 & 7;
    temp_t0 = ((s32 *)arg2)[0];
    switch (temp_t6) {
    case 0:
        ((struct Measured_func_80120E48_us_07091f3fea0d *)(((struct Measured_func_80120E48_us_9e38496ccf6a *)arg0)->value + ((temp_v1 / 8) * 0x28)))->value = temp_t0 & ~7;
        break;
    case 1:
        ((struct Measured_func_80120E48_us_5bc2a4c5e17f *)((((struct Measured_func_80120E48_us_9e38496ccf6a *)(arg0))->value + ((temp_v1 / 8) * 0x28))))->value = (s32) (temp_t0 & ~7);
        break;
    case 3:
        ((struct Measured_func_80120E48_us_850d9776b906 *)((((struct Measured_func_80120E48_us_9e38496ccf6a *)(arg0))->value + ((temp_v1 / 8) * 0x28))))->value = (s16) temp_t0;
        break;
    case 2:
        ((struct Measured_func_80120E48_us_7432af7348b3 *)((((struct Measured_func_80120E48_us_9e38496ccf6a *)(arg0))->value + ((temp_v1 / 8) * 0x28))))->value = (s16) temp_t0;
        break;
    case 4:
        ((struct Measured_func_80120E48_us_d5373a855630 *)((((struct Measured_func_80120E48_us_9e38496ccf6a *)(arg0))->value + ((temp_v1 / 8) * 0x28))))->value = (s16) temp_t0;
        break;
    case 5:
        ((struct Measured_func_80120E48_us_949b950a3b21 *)((((struct Measured_func_80120E48_us_9e38496ccf6a *)(arg0))->value + ((temp_v1 / 8) * 0x28))))->value = (f32) ((2.0 * (f64) ((f32) temp_t0 / 1000.0f)) / (f64) ((struct Measured_func_80120E48_us_71ab4e09f94a *)(D_80145E10))->value);
        break;
    case 6:
        temp_v0 = ((struct Measured_func_80120E48_us_9e38496ccf6a *)(arg0))->value + ((temp_v1 / 8) * 0x28);
        temp_t6_2 = ((struct Measured_func_80120E48_us_5bc2a4c5e17f *)(temp_v0))->value - ((struct Measured_func_80120E48_us_07091f3fea0d *)(temp_v0))->value;
        var_f18 = (f64) temp_t6_2;
        if (temp_t6_2 < 0) {
            var_f18 += 4294967296.0;
        }
        ((struct Measured_func_80120E48_us_a9fa63ae5932 *)(temp_v0))->value = (f32) (var_f18 * ((f64) (f32) temp_t0 / (173123.404906676)));
        break;
    case 7:
        temp_t5 = (temp_v1 / 8) * 0x28;
        temp_a1 = ((struct Measured_func_80120E48_us_0b91e0e95412 *)((((struct Measured_func_80120E48_us_9e38496ccf6a *)(arg0))->value + temp_t5)))->value;
        if (temp_a1 != 0) {
            *temp_a1 = (s16) temp_t0;
            func_8011E6B0_us(((struct Measured_func_80120E48_us_3fe6923ed817 *)((((struct Measured_func_80120E48_us_9e38496ccf6a *)(arg0))->value + temp_t5)))->value);
        }
        break;
    }
    return 0;
}
#endif /* NON_MATCHING */
