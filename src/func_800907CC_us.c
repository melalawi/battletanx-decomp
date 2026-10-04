#include "span_1000/code_8008D588.h"
#include "audio_callbacks.h"
#include "types.h"
#include "common/draft_fields_func_800907CC_us.h"

/* func_8008AD10: types.abi.declared: reuse existing C; propagated semantic conflicts remain named */
extern void *func_8008AD10();
/* func_80106D18: types.abi.declared: reuse existing C; propagated semantic conflicts remain named; types.abi.draft_words: complete O32 argument slots, including caller stack operands */
extern int func_80106D18(int, int, int, int, int, int, int, int, int);

/* types.abi.stack_argument: func_80106D18: stack16: all mapped call sites prove the operand */
/* types.abi.stack_argument: func_80106D18: stack20: all mapped call sites prove the operand */
/* types.abi.stack_argument: func_80106D18: stack24: all mapped call sites prove the operand */
                                                  /* size = 0x50 */

s32 func_800907CC_us(s32 arg0, s32 arg1, s32 arg2, u16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s8 arg8) {
    void *temp_v0;

    temp_v0 = func_8008AD10(0, 0x12, 0x20);
    if (temp_v0 == 0) {
        return -1;
    }
    ((struct Measured_func_800907CC_us_f88949686c7b *)(temp_v0))->value = arg0;
    ((struct Measured_func_800907CC_us_180d010f5e65 *)(temp_v0))->value = arg8;
    ((struct Measured_func_800907CC_us_fc8673a50ef1 *)(temp_v0))->value = func_80106D18((s32) temp_v0, arg1, arg2, arg4, arg5, arg6, arg7, (arg8 & 1) ? 0x20 : 0xF95F, arg3 & 0xFFFF);
    ((struct Measured_func_800907CC_us_7cc74cb35a88 *)(temp_v0))->value = arg1;
    ((struct Measured_func_800907CC_us_95b7c07a1977 *)(temp_v0))->value = arg2;
    ((struct Measured_func_800907CC_us_a9e1f6880f69 *)(temp_v0))->value = 0;
    return 0;
}
