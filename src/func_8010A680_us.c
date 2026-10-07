#include "types.h"
#include "common/types_d507c48987bb.h"
#include "span_1000/code_80107168.h"

/* Both callees end in add.s to f0 and jr ra. Each takes the low 16 bits
 * of a0, interpolates a single precision table, and returns f32. */
extern f32 func_800F3AE0_us(s32);
extern f32 func_800F3B40_us(s32);

s32 func_8010A680_us(void *dst_arg, struct QueryBox *base,
                     struct QueryBox *other)
{
    struct QueryBox *dst = (struct QueryBox *)dst_arg;
    f32 points[4][2];
    f32 bounds[4];
    f32 dx;
    f32 dy;
    f32 cosine;
    f32 sine;
    s32 i;
    f32 rotated_x;
    f32 rotated_y;
    s16 x;
    s16 y;

    dx = other->values[1] - base->values[1];
    dy = other->values[2] - base->values[2];
    cosine = func_800F3B40_us((u16)base->values[8]);
    sine = func_800F3AE0_us((u16)base->values[8]);
    rotated_x = cosine * dx - sine * dy;
    rotated_y = sine * dx + cosine * dy;
    x = (s16)(s32)rotated_x;
    y = (s16)(s32)rotated_y;
    dst->values[1] = x;
    dst->values[2] = y;
    dst->values[8] = (u16)other->values[8] - (u16)base->values[8];
    dst->values[3] = other->values[3];
    dst->values[4] = other->values[4];
    dst->values[5] = other->values[5];
    dst->values[6] = other->values[6];
    func_8010A474_us(dst, points);
    bounds[1] = bounds[0] = points[0][1];
    bounds[3] = bounds[2] = points[0][0];
    for (i = 1; i < 4; i++) {
        if (points[i][1] < bounds[0]) bounds[0] = points[i][1];
        if (points[i][1] > bounds[1]) bounds[1] = points[i][1];
        if (points[i][0] < bounds[2]) bounds[2] = points[i][0];
        if (points[i][0] > bounds[3]) bounds[3] = points[i][0];
    }
    if ((f32)base->values[4] < bounds[0]) return 1;
    if (bounds[1] < (f32)base->values[3]) return 1;
    if ((f32)base->values[6] < bounds[2]) return 1;
    if (bounds[3] < (f32)base->values[5]) return 1;
    return 0;
}
