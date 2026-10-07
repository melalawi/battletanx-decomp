#ifdef NON_MATCHING
#include "gbi.h"
#include "span_1000/code_8010527C.h"
#include "audio_callbacks.h"
#include "types.h"
#include "bt_gbi.h"
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
        temp_t8_2 = (void *)(temp_t8 + 8);
        temp_t8_3 = temp_t8_2 + 8;
        temp_t8_4 = temp_t8_3 + 8;
        temp_t8_5 = temp_t8_4 + 8;
        temp_t8_6 = temp_t8_5 + 8;
        temp_t8_7 = temp_t8_6 + 8;
        temp_t8_8 = temp_t8_7 + 8;
        temp_t8_9 = temp_t8_8 + 8;
        temp_t8_10 = temp_t8_9 + 8;
        gDPSetPrimColor((Gfx *)temp_t8, 0, 0, D_803B75A4, D_803B75A5, D_803B75A6, D_803B75A7);
        temp_t8_11 = temp_t8_10 + 8;
        temp_a1 = ((temp_s2 + temp_t6) * 4) & 0xFFF;
        gDPSetTextureImage((Gfx *)temp_t8_2, G_IM_FMT_IA, G_IM_SIZ_8b, ((struct Measured_func_80106010_us_7cc74cb35a88 *)D_803AAD98)->value, D_803AAD98 + ((struct Measured_func_80106010_us_f88949686c7b *)D_803AAD98)->value);
        temp_a0 = (((u32) (temp_s3 + 8) >> 3) << 9) | 0xF5680000;
        gDPSetTile((Gfx *)temp_t8_3, G_IM_FMT_IA, G_IM_SIZ_8b, (((u32)(temp_s3 + 8)) >> 3), 0, G_TX_LOADTILE, 0, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
        temp_a3 = temp_t0 << 0xE;
        temp_a2 = temp_s2 * 4;
        gDPLoadSync((Gfx *)temp_t8_4);
        temp_v1_2 = (temp_t0 + temp_s3) << 0xE;
        gDPLoadTile((Gfx *)temp_t8_5, G_TX_LOADTILE, temp_t0 * 4, temp_s2 * 4, (temp_t0 + temp_s3) * 4, (temp_s2 + temp_t6) * 4);
        gDPPipeSync((Gfx *)temp_t8_6);
        gDPSetTile((Gfx *)temp_t8_7, G_IM_FMT_IA, G_IM_SIZ_8b, (((u32)(temp_s3 + 8)) >> 3), 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
        gDPSetTileSize((Gfx *)temp_t8_8, G_TX_RENDERTILE, temp_t0 * 4, temp_s2 * 4, (temp_t0 + temp_s3) * 4, (temp_s2 + temp_t6) * 4);
        temp_f2 = (f64) temp_t0 * (32.0);
        gTexRect((Gfx *)temp_t8_9, D_803AAD88 * 4, D_803AAD8C * 4, (D_803AAD88 + (s32)((f32)temp_s3 * D_803AAD90)) * 4, (D_803AAD8C + (s32)((f32)temp_t6 * D_803AAD94)) * 4, G_TX_RENDERTILE);
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
        gDPHalf1((Gfx *)temp_t8_10, ((u32)var_v1 << 16) | ((u32)var_v1_2 & 0xFFFF));
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
        gDPHalf2((Gfx *)temp_t8_11, ((u32)var_v1_3 << 16) | ((u32)var_a0 & 0xFFFF));
        var_v0 = (s32) ((f32) (temp_s3 * D_803B75A0) * D_803AAD90);
        D_803AAD88 += var_v0;
        *arg0 = (s32)(temp_t8_11 + 8);
    }
    return var_v0;
}
#endif /* NON_MATCHING */
