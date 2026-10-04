#ifdef NON_MATCHING
/* NON_MATCHING: diagnostic reconstruction; owner fuzzy bar required. */
#include "types.h"
#include "span_1000/code_80076068.h"
extern void func_80076068_us(void *, int);
void func_800767E4_us(void) {
    s32 ready;
    u32 unused[2];
    u32 temp_s4;
    u32 var_s2;
    u32 temp_s1;
    u32 temp_v1;
    register u32 var_s0;
    u32 count;

    temp_s4 = func_800760A0((void *)0xB1FFFFF4) & 0xB1FFFFFC;
    temp_s1 = func_800760A0((void *)0xB1FFFFF8) & 0x01FFFFFC;
    func_80076068_us((void *)0xB1FFFFFC, 0);
loop_1:
    ready = func_800760A0((void *)0xB0000010);
    temp_v1 = temp_s1 >> 2;
    if (ready == 0) {
        func_800760DC_us(0x1F4);
        goto loop_1;
    }
    if (temp_v1 != 0) {
        count = temp_v1;
        var_s2 = temp_s4 & 0xB07FFFFF;
        var_s0 = 0;
        temp_s1 = temp_s4;
        do {
            func_80076068_us((void *) var_s2, func_800760A0((void *) temp_s1));
            var_s2 += 4;
            var_s0 += 1;
            temp_s1 += 4;
        } while (var_s0 < count);
    }
    func_800760DC_us(0x7D0);
    func_80076068_us((void *)0xB1FFFFF4, 0);
}
#endif
