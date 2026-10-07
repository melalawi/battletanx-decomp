#ifdef NON_MATCHING
#include "gbi.h"
#include "audio_callbacks.h"
#include "bt_gbi.h"
#include "span_1000/code_800A9FC4.h"
#include "common/draft_fields_func_800AACCC_us.h"

/* func_8007F060: types.declaration: solved callee prototype */
extern void *func_8007F060(void);
/* func_800AB520_us: types.abi.word: r4: semantic type unknown; one O32 word carrier; types.abi.word_return: v0 carries one O32 word; semantic return unknown or conflicting */
extern int func_800AB520_us(int, int);
/* func_800AB61C_us: types.abi.word: r4: semantic type unknown; one O32 word carrier */
extern int func_800AB61C_us(int);

                                                  /* size = 0x28 */

void func_800AACCC_us(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a2_4;
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v0_2;
    u16 temp_v1;
    void *temp_a0;
    void *temp_a1;
    void *temp_a1_3;
    void *temp_a1_4;
    void *temp_a1_5;
    void *temp_a1_6;
    void *temp_a1_7;
    void *temp_a2;
    void *temp_a2_2;
    void *temp_a2_3;
    void *temp_s1;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;
    void *temp_v1_5;

    temp_s1 = func_8007F060();
    temp_v0 = func_800AB520_us(arg0, arg1 & 0xFFFF);
    if (temp_v0 == 0) {
        ((struct Measured_func_800AACCC_us_6846b134bee3 *)(temp_s1))->value = 0;
        return;
    }
    temp_v0_2 = func_800AB61C_us(arg0);
    ((struct Measured_func_800AACCC_us_6846b134bee3 *)(temp_s1))->value = temp_v0_2;
    if ((u32) (arg2 & 0xFFFF) < 2U) {
        temp_v1 = ((struct Measured_func_800AACCC_us_5ce774556cd1 *)(temp_v0_2))->value;
        switch (temp_v1) {                          /* irregular */
        case 0:
            temp_a1 = ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value;
            ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value = (void *) (temp_a1 + 8);
            gDPSetTextureImage((Gfx *)temp_a1, ((struct Measured_func_800AACCC_us_63c2a83db63f *)temp_v0_2)->value, G_IM_SIZ_8b, ((u16)((struct Measured_func_800AACCC_us_ca5512d0840a *)temp_v0_2)->value >> 1), (void *)temp_v0);
            temp_a2 = ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value;
            ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value = (void *) (temp_a2 + 8);
            temp_a3 = ((s16) arg2 << 8) & 0x1FF;
            gDPSetTile((Gfx *)temp_a2, ((struct Measured_func_800AACCC_us_63c2a83db63f *)temp_v0_2)->value, G_IM_SIZ_8b, ((s32)(((u16)((struct Measured_func_800AACCC_us_ca5512d0840a *)temp_v0_2)->value >> 1) + 7) >> 3), temp_a3, G_TX_LOADTILE, 0, 1, 6, 0, 1, 6, 0);
            temp_v1_2 = ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value;
            ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value = (void *) (temp_v1_2 + 8);
            gDPLoadSync((Gfx *)temp_v1_2);
            temp_a2_2 = ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value;
            ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value = (void *) (temp_a2_2 + 8);
            gDPLoadTile((Gfx *)temp_a2_2, G_TX_LOADTILE, 0, 0, (((struct Measured_func_800AACCC_us_ca5512d0840a *)temp_v0_2)->value - 1) * 2, (((struct Measured_func_800AACCC_us_c0a9ea81f94e *)temp_v0_2)->value - 1) * 4);
            temp_v1_3 = ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value;
            ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value = (void *) (temp_v1_3 + 8);
            gDPPipeSync((Gfx *)temp_v1_3);
            temp_a2_3 = ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value;
            ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value = (void *) (temp_a2_3 + 8);
            gDPSetTile((Gfx *)temp_a2_3, ((struct Measured_func_800AACCC_us_63c2a83db63f *)temp_v0_2)->value, 0, ((s32)(((u16)((struct Measured_func_800AACCC_us_ca5512d0840a *)temp_v0_2)->value >> 1) + 7) >> 3), temp_a3, (s16)arg2, 0, 1, 6, 0, 1, 6, 0);
            temp_a0 = ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value;
            ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value = (void *) (temp_a0 + 8);
            gDPSetTileSize((Gfx *)temp_a0, (s16)arg2, 0, 0, (((struct Measured_func_800AACCC_us_ca5512d0840a *)temp_v0_2)->value - 1) * 4, (((struct Measured_func_800AACCC_us_c0a9ea81f94e *)temp_v0_2)->value - 1) * 4);
            return;
        case 1:
            temp_a1_3 = ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value;
            ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value = (void *) (temp_a1_3 + 8);
            gDPSetTextureImage((Gfx *)temp_a1_3, ((struct Measured_func_800AACCC_us_63c2a83db63f *)temp_v0_2)->value, G_IM_SIZ_8b, ((struct Measured_func_800AACCC_us_ca5512d0840a *)temp_v0_2)->value, (void *)temp_v0);
            temp_a1_4 = ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value;
            ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value = (void *) (temp_a1_4 + 8);
            temp_a2_4 = ((s16) arg2 << 8) & 0x1FF;
            gDPSetTile((Gfx *)temp_a1_4, ((struct Measured_func_800AACCC_us_63c2a83db63f *)temp_v0_2)->value, G_IM_SIZ_8b, ((s32)(((struct Measured_func_800AACCC_us_ca5512d0840a *)temp_v0_2)->value + 7) >> 3), temp_a2_4, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
            temp_v1_4 = ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value;
            ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value = (void *) (temp_v1_4 + 8);
            gDPLoadSync((Gfx *)temp_v1_4);
            temp_a1_5 = ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value;
            ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value = (void *) (temp_a1_5 + 8);
            gDPLoadTile((Gfx *)temp_a1_5, G_TX_LOADTILE, 0, 0, (((struct Measured_func_800AACCC_us_ca5512d0840a *)temp_v0_2)->value - 1) * 4, (((struct Measured_func_800AACCC_us_c0a9ea81f94e *)temp_v0_2)->value - 1) * 4);
            temp_v1_5 = ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value;
            ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value = (void *) (temp_v1_5 + 8);
            gDPPipeSync((Gfx *)temp_v1_5);
            temp_a1_6 = ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value;
            ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value = (void *) (temp_a1_6 + 8);
            gDPSetTile((Gfx *)temp_a1_6, ((struct Measured_func_800AACCC_us_63c2a83db63f *)temp_v0_2)->value, G_IM_SIZ_8b, ((s32)(((struct Measured_func_800AACCC_us_ca5512d0840a *)temp_v0_2)->value + 7) >> 3), temp_a2_4, (s16)arg2, 0, 0, 0, 0, 0, 0, 0);
            temp_a1_7 = ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value;
            ((struct Measured_func_800AACCC_us_034b69863103 *)(temp_s1))->value = (void *) (temp_a1_7 + 8);
            gDPSetTileSize((Gfx *)temp_a1_7, (s16)arg2, 0, 0, (((struct Measured_func_800AACCC_us_ca5512d0840a *)temp_v0_2)->value - 1) * 4, (((struct Measured_func_800AACCC_us_c0a9ea81f94e *)temp_v0_2)->value - 1) * 4);
            break;
        }
    }
}
#endif /* NON_MATCHING */
