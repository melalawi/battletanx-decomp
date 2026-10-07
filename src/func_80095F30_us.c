#ifdef NON_MATCHING
#include "span_1000/code_80094704.h"
#include "audio_callbacks.h"
#include "types.h"
#include "common/draft_fields_func_80095F30_us.h"

/* func_800821C0: types.abi.declared: reuse existing C; propagated semantic conflicts remain named */
extern int func_800821C0(void);
/* func_80094C58_us: types.abi.word: r4: semantic type conflict; one O32 word carrier; types.abi.word: r5: semantic type conflict; one O32 word carrier; types.abi.word: r6: semantic type conflict; one O32 word carrier; types.abi.word: r7: semantic type conflict; one O32 word carrier; types.abi.word_return: v0 carries one O32 word; semantic return unknown or conflicting */

/* func_80095CDC_us: types.abi.word: r4: semantic type unknown; one O32 word carrier; types.abi.word: r6: semantic type unknown; one O32 word carrier; types.abi.arguments: some mapped callers do not establish every consumed argument value; types.abi.word_return: v0 carries one O32 word; semantic return unknown or conflicting */
extern int func_80095CDC_us(int, int, int, int, int, int);

                                                  /* size = 0x58 */

s32 func_80095F30_us(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 temp_f0;
    s32 temp_f4;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    void *temp_v0;

    temp_v0 = func_800821C0() + ((arg5 * 0x2C) + 0x584);
    temp_f4 = (s32) ((struct Measured_func_80095F30_us_dcc02779e267 *)(temp_v0))->value;
    temp_f0 = (s32) ((struct Measured_func_80095F30_us_ada0386e2a2f *)(temp_v0))->value;
    if (temp_f4 < arg0) {
        if (temp_f0 < arg1) {
            var_v0_2 = 0;
            if (func_80094C58_us(arg0, arg1, arg2, arg1, arg5, (s32) &sp28, (s32) &sp2C, (s32) &sp30, (s32) &sp34) != 0) {
                var_v0_2 = func_80095CDC_us(sp28, sp2C, sp30, sp34, arg4, arg5);
            }
            var_v0 = 1;
            if (var_v0_2 == 0) {
                var_a1 = arg1;
                var_a2 = arg0;
                goto block_6;
            }
            /* Duplicate return node #35. Try simplifying control flow for better match */
            return var_v0;
        }
        var_a1_2 = arg1;
        if (arg3 < temp_f0) {
            var_v0_3 = 0;
            if (func_80094C58_us(arg0, var_a1_2, arg0, arg3, arg5, (s32) &sp28, (s32) &sp2C, (s32) &sp30, (s32) &sp34) != 0) {
                var_v0_3 = func_80095CDC_us(sp28, sp2C, sp30, sp34, arg4, arg5);
            }
            var_v0 = 1;
            if (var_v0_3 == 0) {
                var_a0 = arg0;
                var_a1_2 = arg3;
                goto block_13;
            }
            /* Duplicate return node #35. Try simplifying control flow for better match */
            return var_v0;
        }
        var_a0 = arg0;
        var_a2_2 = var_a0;
        var_a3 = arg3;
        goto block_15;
    }
    temp_v0_2 = temp_f0 < arg1;
    if (arg2 < temp_f4) {
        if (temp_v0_2 != 0) {
            var_v0_4 = 0;
            if (func_80094C58_us(arg0, arg1, arg2, arg1, arg5, (s32) &sp28, (s32) &sp2C, (s32) &sp30, (s32) &sp34) != 0) {
                var_v0_4 = func_80095CDC_us(sp28, sp2C, sp30, sp34, arg4, arg5);
            }
            var_v0 = 1;
            if (var_v0_4 == 0) {
                var_a0 = arg2;
                var_a1_2 = arg1;
                var_a2_2 = var_a0;
                var_a3 = arg3;
                goto block_15;
            }
            /* Duplicate return node #35. Try simplifying control flow for better match */
            return var_v0;
        }
        var_a0 = arg2;
        if (arg3 < temp_f0) {
            var_v0_5 = 0;
            if (func_80094C58_us(var_a0, arg1, arg2, arg3, arg5, (s32) &sp28, (s32) &sp2C, (s32) &sp30, (s32) &sp34) != 0) {
                var_v0_5 = func_80095CDC_us(sp28, sp2C, sp30, sp34, arg4, arg5);
            }
            var_v0 = 1;
            if (var_v0_5 == 0) {
                var_a0 = arg2;
                var_a1_2 = arg3;
                var_a2_2 = arg0;
                goto block_14;
            }
            /* Duplicate return node #35. Try simplifying control flow for better match */
            return var_v0;
        }
        var_a1_2 = arg1;
        var_a2_2 = var_a0;
        var_a3 = arg3;
        goto block_15;
    }
    var_a0 = arg0;
    if (temp_v0_2 != 0) {
        var_a1_2 = arg1;
block_13:
        var_a2_2 = arg2;
block_14:
        var_a3 = var_a1_2;
block_15:
        if (func_80094C58_us(var_a0, var_a1_2, var_a2_2, var_a3, arg5, (s32) &sp28, (s32) &sp2C, (s32) &sp30, (s32) &sp34) == 0) {
            return 0;
        }
        goto block_7;
    }
    var_a1 = arg3;
    if (arg3 < temp_f0) {
        var_a2 = arg2;
block_6:
        var_v0 = 0;
        if (func_80094C58_us(arg0, var_a1, var_a2, arg3, arg5, (s32) &sp28, (s32) &sp2C, (s32) &sp30, (s32) &sp34) != 0) {
block_7:
            return func_80095CDC_us(sp28, sp2C, sp30, sp34, arg4, arg5);
        }
        /* Duplicate return node #35. Try simplifying control flow for better match */
        return var_v0;
    }
    var_v0 = 1;
    return var_v0;
}
#endif /* NON_MATCHING */
