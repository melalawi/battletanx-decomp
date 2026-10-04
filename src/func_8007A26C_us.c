#include "audio_callbacks.h"
#include "types.h"
#include "common/types.h"
#include "span_1000/code_800794C8.h"

/* func_80112140: types.abi.word: r7: semantic type conflict; one O32 word carrier */
extern int func_80112140(int, int, void *, int, int);

                                                  /* size = 0x30 */

extern unsigned char D_80150340; /* opaque address transport */


s32 func_8007A26C_us(void) {
    s32 *var_s0;
    s32 *var_s0_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    u32 allocation;
    u32 address;
    u32 size;
    s32 kind;
    u32 var_s1;
    u32 var_s1_2;

    var_s1 = 0;
    allocation = 0x8000;
    var_s0 = D_80152EF0;
    do {
        *var_s0 = func_80112140(0, 0, &D_80150340, 1, allocation);
        var_s0 += 1;
        var_s1 += 1;
    } while (var_s1 < 2U);
    var_s1_2 = 0;
    address = (u32)&D_80150340;
    size = 0x50;
    kind = 2;
    var_s0_2 = &D_801B4A48;
    do {
        temp_v0_2 = func_80112140(0, 0, (void *)address, 1, size);
        *var_s0_2 = temp_v0_2;
        ((struct Measured_func_8007A26C_us_9f751e433327 *)(temp_v0_2))->value = kind;
        temp_v1 = *var_s0_2;
        ((struct Measured_func_8007A26C_us_c1ec687bfaf5 *)(temp_v1))->value = temp_v1;
        var_s1_2 += 1;
        ((struct Measured_func_8007A26C_us_07091f3fea0d *)(*var_s0_2))->value = func_80112140(0, 0, (void *)address, 1, D_80152EF8 * 4);
        temp_v0 = var_s1_2 < 3U;
        var_s0_2 += 1;
    } while (temp_v0 != 0);
    return temp_v0;
}
