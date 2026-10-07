#include "types.h"
#include "common/types_d507c48987bb.h"
#include "span_1000/code_8007EBA0.h"
#include "span_1000/code_800F45C8.h"
#include "gfx.h"
#undef F3DEX_GBI_2

#include "gbi.h"


extern u8 D_801257F5;


s32 func_8008001C_us(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    u32 next;
    D_801B6C00 = (void *)(D_801B4C00 + (D_801257F5 << 10));
    if (arg4) {
        func_800F4DFC((struct Shape_func_800B8804_us *)&D_801B6C00, 0x22, 0x13, 0xFC, 0x72,
                      arg0 & 0xFF, arg1 & 0xFF, arg2 & 0xFF, arg3 & 0xFF);
    } else {
        func_800F4DFC((struct Shape_func_800B8804_us *)&D_801B6C00, 0, 0, 0x140, 0xF0,
                      arg0 & 0xFF, arg1 & 0xFF, arg2 & 0xFF, arg3 & 0xFF);
    }
    gSPEndDisplayList((Gfx *)D_801B6C00++);
    func_8007EF40_us((s32)(D_801B4C00 + (D_801257F5 << 10)));
    next = (D_801257F5 + 1) & 7;
    D_801257F5 = next;
    return next;
}
