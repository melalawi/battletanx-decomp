#ifdef NON_MATCHING
#include "audio_callbacks.h"
#include "span_1000/code_80097038.h"
#include "span_1000/code_8010BFDC.h"
#include "common/draft_fields_func_800983E0_us.h"

/* func_8007C6D8: types.declaration: solved callee prototype */
extern int func_8007C6D8(void);
/* func_80097DD0_us: types.abi.word: r4: semantic type conflict; one O32 word carrier; types.abi.word: r5: semantic type conflict; one O32 word carrier; types.abi.word: r6: semantic type conflict; one O32 word carrier; types.abi.unused_return: no mapped direct caller consumes a result; semantic return unknown */
extern void func_80097DD0_us(int, int, int);
/* func_8009EDD0_us: types.abi.word: r4: semantic type conflict; one O32 word carrier; types.abi.unused_return: no mapped direct caller consumes a result; semantic return unknown */
extern void func_8009EDD0_us(int);
/* func_800A51E8: types.abi.declared: reuse existing C; propagated semantic conflicts remain named */
extern void func_800A51E8(struct FuncA51E8State * arg0, int arg1, float arg2);
/* func_800A6688: types.abi.word: r4: semantic type unknown; one O32 word carrier; types.abi.word_return: v0 carries one O32 word; semantic return unknown or conflicting */
extern int func_800A6688(int);
/* func_800A8EF8: types.abi.declared: reuse existing C; propagated semantic conflicts remain named */
extern void func_800A8EF8(int, int, int, int);
/* func_800E3460: types.abi.declared: reuse existing C; propagated semantic conflicts remain named */
extern int func_800E3460(const unsigned char * arg0);

                                                  /* size = 0x30 */

extern u8 D_80135762;
extern u8 D_80135763;

int func_800983E0_us(void *arg0, int arg1, int arg2, unsigned int arg3) {
    f32 temp_f20;
    f32 temp_f2;
    s32 temp_a0_2;
    s32 temp_s2;
    s32 temp_v1_2;
    s32 var_a0_2;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    s32 var_a2;
    s32 var_s1;
    s32 var_v1;
    u16 temp_v1;
    u8 var_a0;
    void *temp_a0;

    if (D_80135762 == 0) {
        if (((D_80135763 == 0) || (func_800E3460((u8 *) arg0) != 0)) && (((struct Measured_func_800983E0_us_572ebb6641c0 *)(arg0))->value != 0) && (temp_v1 = ((struct Measured_func_800983E0_us_dc539bebcfa1 *)(arg0))->value, ((temp_v1 & 0x8001) == 0))) {
            if (temp_v1 & 2) {
                func_8009EDD0_us((s32)arg0);
                var_a2 = 0;
                goto block_48;
            }
            if (arg1 != 0) {
                if (!(temp_v1 & 0x100) || (var_a0 = 1, (func_8007C6D8() == 0))) {
                    var_a0 = ((struct Measured_func_800983E0_us_11c714a35a35 *)(arg0))->value;
                }
                temp_f20 = (100.0f);
                var_s1 = (s32) ((f32) arg1 * (((struct Measured_func_800983E0_us_661d24d43cd2 *)(func_800A6688((s32) var_a0)))->value / temp_f20));
                if ((u32) arg2 < 4U) {
                    var_s1 = (s32) ((f32) var_s1 / (((struct Measured_func_800983E0_us_1b54afc73f5a *)(func_800A6688(arg2 & 0xFFFF)))->value / temp_f20));
                }
                temp_s2 = func_800A6688((s32) ((struct Measured_func_800983E0_us_11c714a35a35 *)(arg0))->value);
                if (var_s1 == 0) {
                    var_s1 = 1;
                }
                if (func_800E3460((u8 *) arg0) == 0) {
                    var_a1 = (var_s1 / 3) + 0x14;
                    if (var_a1 >= 0x29) {
                        var_a1 = 0x28;
                    }
                    func_800A8EF8((s32) ((struct Measured_func_800983E0_us_11c714a35a35 *)(arg0))->value, var_a1, 6, 4);
                }
                temp_a0 = ((struct Measured_func_800983E0_us_69e5ef5b3570 *)(arg0))->value;
                if ((temp_a0 != 0) && (((struct Measured_func_800983E0_us_1598d169e0a4 *)(arg0))->value == ((struct Measured_func_800983E0_us_5bc2a4c5e17f *)(temp_a0))->value)) {
                    temp_v1_2 = ((struct Measured_func_800983E0_us_fc8673a50ef1 *)(temp_a0))->value;
                    if (temp_v1_2 < var_s1) {
                        var_s1 -= temp_v1_2;
                        ((struct Measured_func_800983E0_us_fc8673a50ef1 *)(temp_a0))->value = 0;
                    } else {
                        ((struct Measured_func_800983E0_us_fc8673a50ef1 *)(temp_a0))->value = (s32) (temp_v1_2 - var_s1);
                        var_s1 = 0;
                    }
                }
                if ((arg2 == ((struct Measured_func_800983E0_us_11c714a35a35 *)(arg0))->value) & (arg3 != 0)) {
                    var_a0_2 = func_800A6688(arg2 & 0xFFFF);
                    var_a1_2 = 0xA;
                    goto block_31;
                }
                if (((struct Measured_func_800983E0_us_fc8673a50ef1 *)(arg0))->value == 2) {
                    var_a0_2 = temp_s2;
                    if (((struct Measured_func_800983E0_us_5cf0a8e1d176 *)(temp_s2))->value != ((struct Measured_func_800983E0_us_73da4640dc10 *)(arg0))->value) {
                        var_a1_2 = 2;
block_31:
                        func_800A51E8((struct FuncA51E8State *) var_a0_2, var_a1_2, 3.0f);
                    }
                }
                temp_a0_2 = ((struct Measured_func_800983E0_us_7d6aec9d411c *)(arg0))->value - var_s1;
                ((struct Measured_func_800983E0_us_7d6aec9d411c *)(arg0))->value = temp_a0_2;
                if ((((struct Measured_func_800983E0_us_2ac2e0f9715f *)(arg0))->value != 0) && (temp_a0_2 < ((s32) ((struct Measured_func_800983E0_us_9e38496ccf6a *)(arg0))->value / 2))) {
                    func_800A51E8((struct FuncA51E8State *) temp_s2, 0x21, 3.0f);
                }
                if (((struct Measured_func_800983E0_us_95b7c07a1977 *)(arg0))->value == 0) {
                    ((struct Measured_func_800983E0_us_db74d82bc842 *)(arg0))->value = 0xF0;
                }
                ((struct Measured_func_800983E0_us_d21dc9cabacf *)(arg0))->value = (s32) D_801B4AA8;
                if (((struct Measured_func_800983E0_us_7d6aec9d411c *)(arg0))->value <= 0) {
                    if (func_800E3460((u8 *) arg0) == 0) {
                        var_v1 = (var_s1 / 3) + 0x14;
                        if (var_v1 >= 0x29) {
                            var_v1 = 0x28;
                        }
                        temp_f2 = (f32) var_v1 * (1.5f);
                        if ((2147483648.0f) <= temp_f2) {
                            var_a1_3 = (s32) (temp_f2 - (2147483648.0f)) | 0x80000000;
                        } else {
                            var_a1_3 = (s32) temp_f2;
                        }
                        func_800A8EF8((s32) ((struct Measured_func_800983E0_us_11c714a35a35 *)(arg0))->value, var_a1_3, 2, 1);
                    }
                    ((struct Measured_func_800983E0_us_7d6aec9d411c *)(arg0))->value = 0;
                    var_a2 = 1;
block_48:
                    func_80097DD0_us((s32)arg0, arg2, var_a2);
                    return 1;
                }
                if (func_800E3460((u8 *) arg0) == 0) {
                    var_a1_4 = (var_s1 / 3) + 0x14;
                    if (var_a1_4 >= 0x29) {
                        var_a1_4 = 0x28;
                    }
                    func_800A8EF8((s32) ((struct Measured_func_800983E0_us_11c714a35a35 *)(arg0))->value, var_a1_4, 6, 4);
                }
            }
        }
    }
    return 0;
}
/* Warning: struct FuncA51E8State is not defined (only forward-declared) */
#endif /* NON_MATCHING */
