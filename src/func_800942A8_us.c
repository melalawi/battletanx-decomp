#ifdef NON_MATCHING
#include "types.h"
#include "span_1000/code_80091A60.h"












s32 func_800942A8_us(s32 polygon_word, s32 count, void *transform_arg)
{
    struct PolygonPoint *polygon = (struct PolygonPoint *)polygon_word;
    struct PolygonTransform *transform = (struct PolygonTransform *)transform_arg;
    struct PolygonPoint shifted[4];
    struct PolygonPoint projected[4];
    u8 regions[4];
    s8 common = 0xFF;
    s32 i;
    s32 next;
    f32 fraction;
    f32 y;
    if (transform->disabled != 0) return 0;
    if (count >= 5) return 1;
    for (i = 0; i < count; i++) {
        shifted[i].x = polygon[i].x + transform->translate_x;
        shifted[i].y = polygon[i].y + transform->translate_y;
        projected[i].x = transform->x_x * shifted[i].x -
                         transform->x_y * shifted[i].y;
        projected[i].y = transform->y_y * shifted[i].y +
                         transform->y_x * shifted[i].x;
        if (0.0f < projected[i].x) {
            if (projected[i].y < 0.0f) {
                regions[i] = 5;
            } else {
                if (projected[i].x < projected[i].y) return 0;
                regions[i] = 1;
            }
        } else {
            if (projected[i].y < 0.0f) {
                regions[i] = 6;
            } else {
                if (-projected[i].x < projected[i].y) return 0;
                regions[i] = 2;
            }
        }
    }
    for (i = 0; i < count; i++) {
        common &= regions[i];
    }
    if ((common & 0xFF) != 0) return 1;
    for (i = 0; i < count; i++) {
        if ((regions[i] | regions[(i + 1) % count]) == 3) return 0;
    }
    for (i = 0; i < count; i++) {
        next = (i + 1) % count;
        if ((regions[i] ^ regions[next]) == 7) {
            fraction = -projected[i].x /
                       (projected[(u8)next].x - projected[i].x);
            y = fraction * (projected[(u8)next].y - projected[i].y) +
                projected[i].y;
            if (0.0f < y) return 0;
        }
    }
    return 1;
}
#endif /* NON_MATCHING */
