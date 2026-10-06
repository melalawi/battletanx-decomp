#ifdef NON_MATCHING
#include "span_1000/code_800862E8.h"
#include "audio_callbacks.h"
#include "types.h"
#include "common/draft_fields_func_8008716C_us.h"



                                                  /* size = 0x18 */

extern unsigned char D_936C; /* opaque address transport */
extern unsigned char D_9370; /* opaque address transport */
extern unsigned char D_9374; /* opaque address transport */
extern unsigned char D_937C; /* opaque address transport */
extern unsigned char D_A374; /* opaque address transport */
extern unsigned char D_A378; /* opaque address transport */
extern unsigned char D_A37C; /* opaque address transport */
extern unsigned char D_A384; /* opaque address transport */

s32 func_8008716C_us(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_t0;
    s32 temp_t0_2;
    s32 temp_t0_3;
    s32 temp_t2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_a3_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    void *temp_t1;
    void *temp_t1_2;
    void *temp_v1;

    if (arg1 < 0xE10) {
        temp_v1 = ((struct Measured_func_8008716C_us_6846b134bee3 *)(arg0))->value + (arg1 * 8);
        temp_v0 = ((struct Measured_func_8008716C_us_42e3d9f6bf48 *)(temp_v1))->value;
        if (temp_v0 == 0) {
            var_v0_2 = 2;
            if (arg2 == 0) {
                var_v0_2 = 1;
            }
            ((struct Measured_func_8008716C_us_42e3d9f6bf48 *)(temp_v1))->value = var_v0_2;
            temp_t0 = ((struct Measured_func_8008716C_us_6846b134bee3 *)(arg0))->value;
            temp_t1 = ((struct Measured_func_8008716C_us_fc8673a50ef1 *)(arg0))->value + (arg1 * 0x10);
            temp_v0_2 = *(temp_t0 + &D_936C);
            temp_t2 = ((struct Measured_func_8008716C_us_07091f3fea0d *)(temp_t1))->value;
            var_a3 = 0;
            if (temp_v0_2 > 0) {
                var_v1 = temp_t0;
loop_6:
                var_a3 += 1;
                if (*(var_v1 + &D_9370) != temp_t2) {
                    var_v1 += 0x10;
                    if (var_a3 >= temp_v0_2) {
                        goto block_8;
                    }
                    goto loop_6;
                }
                var_a1 = 0;
            } else {
block_8:
                temp_v1_2 = *(temp_t0 + &D_936C);
                if (temp_v1_2 == 0x100) {
                    var_a1 = -1;
                } else {
                    *(temp_t0 + (temp_v1_2 * 0x10) + &D_937C) = 1;
                    *(temp_t0 + (*(temp_t0 + &D_936C) * 0x10) + &D_9370) = temp_t2;
                    temp_v0_3 = *(temp_t0 + &D_936C);
                    var_a1 = 0;
                    *(temp_t0 + &D_936C) = temp_v0_3 + 1;
                    *(temp_t0 + (temp_v0_3 * 0x10) + &D_9374) = (s32) ((struct Measured_func_8008716C_us_c0a9ea81f94e *)(temp_t1))->value;
                }
            }
            var_v0 = -1;
            if (var_a1 >= 0) {
                temp_a0 = ((struct Measured_func_8008716C_us_6846b134bee3 *)(arg0))->value;
                temp_t0_2 = ((struct Measured_func_8008716C_us_db74d82bc842 *)(temp_t1))->value;
                var_a1_2 = 0;
                if (*(temp_a0 + &D_A374) > 0) {
                    var_a3_2 = 0;
                    var_v1_2 = temp_a0;
loop_15:
                    if (*(var_v1_2 + &D_A378) != temp_t0_2) {
                        var_a1_2 += 1;
                        var_v1_2 += 0x10;
                        if (var_a1_2 >= *(temp_a0 + &D_A374)) {
                            goto block_21;
                        }
                        goto loop_15;
                    }
                    if (arg2 != 0) {
                        *(var_v1_2 + &D_A384) = *(var_v1_2 + &D_A384) + 1;
                    }
                } else {
block_21:
                    temp_v1_3 = *(temp_a0 + &D_A374);
                    if (temp_v1_3 == 0x708) {
                        var_a3_2 = -1;
                    } else {
                        if (arg2 != 0) {
                            var_v0_3 = 2;
                        } else {
                            var_v0_3 = 1;
                        }
                        *(temp_a0 + (temp_v1_3 * 0x10) + &D_A384) = var_v0_3;
                        *(temp_a0 + (*(temp_a0 + &D_A374) * 0x10) + &D_A378) = temp_t0_2;
                        temp_v0_4 = *(temp_a0 + &D_A374);
                        var_a3_2 = 0;
                        *(temp_a0 + &D_A374) = temp_v0_4 + 1;
                        *(temp_a0 + (temp_v0_4 * 0x10) + &D_A37C) = ((struct Measured_func_8008716C_us_7cc74cb35a88 *)(temp_t1))->value;
                    }
                }
                var_v0 = 0;
                if (var_a3_2 < 0) {
                    goto block_28;
                }
                /* Duplicate return node #46. Try simplifying control flow for better match */
                return var_v0;
            }
            /* Duplicate return node #46. Try simplifying control flow for better match */
            return var_v0;
        }
        if (arg2 != 0) {
            ((struct Measured_func_8008716C_us_42e3d9f6bf48 *)(temp_v1))->value = (s32) (temp_v0 + 1);
            temp_a0_2 = ((struct Measured_func_8008716C_us_6846b134bee3 *)(arg0))->value;
            temp_t1_2 = ((struct Measured_func_8008716C_us_fc8673a50ef1 *)(arg0))->value + (arg1 * 0x10);
            temp_t0_3 = ((struct Measured_func_8008716C_us_db74d82bc842 *)(temp_t1_2))->value;
            var_a3_3 = 0;
            if (*(temp_a0_2 + &D_A374) > 0) {
                var_a1_3 = 0;
                var_v1_3 = temp_a0_2;
loop_32:
                if (*(var_v1_3 + &D_A378) != temp_t0_3) {
                    var_a3_3 += 1;
                    var_v1_3 += 0x10;
                    if (var_a3_3 >= *(temp_a0_2 + &D_A374)) {
                        goto block_38;
                    }
                    goto loop_32;
                }
                if (arg2 != 0) {
                    *(var_v1_3 + &D_A384) = *(var_v1_3 + &D_A384) + 1;
                }
            } else {
block_38:
                temp_v1_4 = *(temp_a0_2 + &D_A374);
                if (temp_v1_4 == 0x708) {
                    var_a1_3 = -1;
                } else {
                    if (arg2 != 0) {
                        var_v0_4 = 2;
                    } else {
                        var_v0_4 = 1;
                    }
                    *(temp_a0_2 + (temp_v1_4 * 0x10) + &D_A384) = var_v0_4;
                    *(temp_a0_2 + (*(temp_a0_2 + &D_A374) * 0x10) + &D_A378) = temp_t0_3;
                    temp_v0_5 = *(temp_a0_2 + &D_A374);
                    var_a1_3 = 0;
                    *(temp_a0_2 + &D_A374) = temp_v0_5 + 1;
                    *(temp_a0_2 + (temp_v0_5 * 0x10) + &D_A37C) = ((struct Measured_func_8008716C_us_7cc74cb35a88 *)(temp_t1_2))->value;
                }
            }
            var_v0 = -1;
            if (var_a1_3 >= 0) {
                goto block_45;
            }
        } else {
block_45:
            var_v0 = 0;
        }
        return var_v0;
    }
block_28:
    return -1;
}
#endif /* NON_MATCHING */
