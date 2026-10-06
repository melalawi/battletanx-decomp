#ifdef NON_MATCHING
#include "span_1000/code_8010527C.h"
#include "audio_callbacks.h"
#include "types.h"
#include "common/draft_fields_func_80106010_us.h"



                                                  /* size = 0x20 */

extern s32 D_803AAD88;
extern s32 D_803AAD8C;
extern f32 D_803AAD90;
extern f32 D_803AAD94;
extern void *D_803AAD98;
extern s32 D_803B75A0;
extern u8 D_803B75A4;
extern u8 D_803B75A5;
extern u8 D_803B75A6;
extern u8 D_803B75A7;
extern u8 D_803B75A8;

s32 func_80106010_us(s32 *arg0, s32 arg1) {
    f32 temp_f2_3;
    f32 temp_f2_4;
    f64 temp_f2;
    f64 temp_f2_2;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_t6;
    s32 temp_t8;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    u8 temp_s2;
    u8 temp_s3;
    u8 temp_t0;
    u8 temp_v1;
    void *temp_t8_10;
    void *temp_t8_11;
    void *temp_t8_2;
    void *temp_t8_3;
    void *temp_t8_4;
    void *temp_t8_5;
    void *temp_t8_6;
    void *temp_t8_7;
    void *temp_t8_8;
    void *temp_t8_9;
    void *temp_v0_2;

    D_803B75A8 += 1;
    if (arg1 == 0x20) {
        temp_v0 = D_803AAD88 + (s32) ((f32) (D_803B75A0 * 3) * D_803AAD90);
        D_803AAD88 = temp_v0;
        return temp_v0;
    }
    temp_v1 = ((struct Measured_func_80106010_us_586592ff79c1 *)((D_803AAD98 + arg1)))->value;
    var_v0 = 0xFF;
    if (temp_v1 != 0xFF) {
        temp_t8 = *arg0;
        temp_t6 = ((struct Measured_func_80106010_us_5bc2a4c5e17f *)(D_803AAD98))->value;
        temp_v0_2 = D_803AAD98 + (temp_v1 * 4);
        temp_t0 = ((struct Measured_func_80106010_us_6118e4b73d6f *)(temp_v0_2))->value;
        temp_s2 = ((struct Measured_func_80106010_us_86ecf9630c4a *)(temp_v0_2))->value;
        temp_s3 = ((struct Measured_func_80106010_us_78c30cba5e02 *)(temp_v0_2))->value;
        temp_t8_2 = temp_t8 + 8;
        temp_t8_3 = temp_t8_2 + 8;
        temp_t8_4 = temp_t8_3 + 8;
        temp_t8_5 = temp_t8_4 + 8;
        temp_t8_6 = temp_t8_5 + 8;
        temp_t8_7 = temp_t8_6 + 8;
        temp_t8_8 = temp_t8_7 + 8;
        temp_t8_9 = temp_t8_8 + 8;
        temp_t8_10 = temp_t8_9 + 8;
        ((struct Measured_func_80106010_us_07091f3fea0d *)(temp_t8))->value = 0xFA000000;
        temp_t8_11 = temp_t8_10 + 8;
        ((struct Measured_func_80106010_us_5bc2a4c5e17f *)(temp_t8))->value = (s32) ((D_803B75A4 << 0x18) | (D_803B75A5 << 0x10) | (D_803B75A6 << 8) | D_803B75A7);
        temp_a1 = ((temp_s2 + temp_t6) * 4) & 0xFFF;
        ((struct Measured_func_80106010_us_034b69863103 *)(temp_t8_2))->value = (void *) (D_803AAD98 + ((struct Measured_func_80106010_us_f88949686c7b *)(D_803AAD98))->value);
        ((struct Measured_func_80106010_us_db74d82bc842 *)(temp_t8))->value = (s32) (((((struct Measured_func_80106010_us_7cc74cb35a88 *)(D_803AAD98))->value - 1) & 0xFFF) | 0xFD680000);
        temp_a0 = (((u32) (temp_s3 + 8) >> 3) << 9) | 0xF5680000;
        ((struct Measured_func_80106010_us_db74d82bc842 *)(temp_t8_2))->value = temp_a0;
        ((struct Measured_func_80106010_us_5bc2a4c5e17f *)(temp_t8_3))->value = 0x07080200;
        temp_a3 = temp_t0 << 0xE;
        temp_a2 = temp_s2 * 4;
        ((struct Measured_func_80106010_us_db74d82bc842 *)(temp_t8_3))->value = 0xE6000000;
        temp_v1_2 = (temp_t0 + temp_s3) << 0xE;
        ((struct Measured_func_80106010_us_5bc2a4c5e17f *)(temp_t8_4))->value = 0;
        ((struct Measured_func_80106010_us_db74d82bc842 *)(temp_t8_4))->value = (s32) (temp_a3 | (temp_a2 | 0xF4000000));
        ((struct Measured_func_80106010_us_5bc2a4c5e17f *)(temp_t8_5))->value = (s32) (temp_v1_2 | (temp_a1 | 0x07000000));
        ((struct Measured_func_80106010_us_db74d82bc842 *)(temp_t8_5))->value = 0xE7000000;
        ((struct Measured_func_80106010_us_5bc2a4c5e17f *)(temp_t8_6))->value = 0;
        ((struct Measured_func_80106010_us_db74d82bc842 *)(temp_t8_6))->value = temp_a0;
        ((struct Measured_func_80106010_us_5bc2a4c5e17f *)(temp_t8_7))->value = 0x80200;
        ((struct Measured_func_80106010_us_5bc2a4c5e17f *)(temp_t8_8))->value = (s32) (temp_v1_2 | temp_a1);
        ((struct Measured_func_80106010_us_db74d82bc842 *)(temp_t8_7))->value = (s32) (temp_a3 | (temp_a2 | 0xF2000000));
        ((struct Measured_func_80106010_us_5bc2a4c5e17f *)(temp_t8_9))->value = (s32) ((((D_803AAD88 * 4) & 0xFFF) << 0xC) | ((D_803AAD8C * 4) & 0xFFF));
        temp_f2 = (f64) temp_t0 * (32.0);
        ((struct Measured_func_80106010_us_db74d82bc842 *)(temp_t8_8))->value = (s32) (((((D_803AAD88 + (s32) ((f32) temp_s3 * D_803AAD90)) * 4) & 0xFFF) << 0xC) | ((((D_803AAD8C + (s32) ((f32) temp_t6 * D_803AAD94)) * 4) & 0xFFF) | 0xE4000000));
        ((struct Measured_func_80106010_us_db74d82bc842 *)(temp_t8_9))->value = 0xB4000000;
        if (!((2147483648.0) <= temp_f2)) {
            var_v1 = (s32) temp_f2;
        } else {
            var_v1 = (s32) (temp_f2 - (2147483648.0)) | 0x80000000;
        }
        temp_f2_2 = (f64) temp_s2 * (32.0);
        if (!((2147483648.0) <= temp_f2_2)) {
            var_v1_2 = (s32) temp_f2_2;
        } else {
            var_v1_2 = (s32) (temp_f2_2 - (2147483648.0)) | 0x80000000;
        }
        temp_f2_3 = (1024.0f) / D_803AAD90;
        ((struct Measured_func_80106010_us_5bc2a4c5e17f *)(temp_t8_10))->value = (s32) ((var_v1 << 0x10) | (var_v1_2 & 0xFFFF));
        ((struct Measured_func_80106010_us_db74d82bc842 *)(temp_t8_10))->value = 0xB3000000;
        if (!((2147483648.0f) <= temp_f2_3)) {
            var_v1_3 = (s32) temp_f2_3;
        } else {
            var_v1_3 = (s32) (temp_f2_3 - (2147483648.0f)) | 0x80000000;
        }
        temp_f2_4 = (1024.0f) / D_803AAD94;
        if (!((2147483648.0f) <= temp_f2_4)) {
            var_a0 = (s32) temp_f2_4;
        } else {
            var_a0 = (s32) (temp_f2_4 - (2147483648.0f)) | 0x80000000;
        }
        ((struct Measured_func_80106010_us_5bc2a4c5e17f *)(temp_t8_11))->value = (s32) ((var_v1_3 << 0x10) | (var_a0 & 0xFFFF));
        var_v0 = (s32) ((f32) (temp_s3 * D_803B75A0) * D_803AAD90);
        D_803AAD88 += var_v0;
        *arg0 = temp_t8_11 + 8;
    }
    return var_v0;
}
#endif /* NON_MATCHING */
