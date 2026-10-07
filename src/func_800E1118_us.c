#ifdef NON_MATCHING
#include "types.h"
#include "span_1000/code_80091A60.h"
#include "span_1000/code_800E0B00.h"












s32 func_800E1118_us(void *a_arg, void *b_arg, void *c_arg, void *d_arg,
                    void *out_arg, void *count_arg)
{
    struct PolygonPoint *a = (struct PolygonPoint *)a_arg;
    struct PolygonPoint *b = (struct PolygonPoint *)b_arg;
    struct PolygonPoint *c = (struct PolygonPoint *)c_arg;
    struct PolygonPoint *d = (struct PolygonPoint *)d_arg;
    struct PolygonPoint *out = (struct PolygonPoint *)out_arg;
    u16 *count = (u16 *)count_arg;
    struct PolygonPoint hit;
    struct SegmentBounds ab;
    struct SegmentBounds cd;
    f32 dx;
    f32 slope_ab;
    f32 slope_cd;
    f32 intercept_ab;
    f32 intercept_cd;
    f32 denominator;
    s32 found;
    s32 equal;
    s16 endpoint_count = 0;
    ab.min_x = a->x < b->x ? a->x : b->x;
    ab.min_y = a->y < b->y ? a->y : b->y;
    ab.max_x = b->x < a->x ? a->x : b->x;
    ab.max_y = b->y < a->y ? a->y : b->y;
    cd.min_x = c->x < d->x ? c->x : d->x;
    cd.min_y = c->y < d->y ? c->y : d->y;
    cd.max_x = d->x < c->x ? c->x : d->x;
    cd.max_y = d->y < c->y ? c->y : d->y;
    if (ab.max_x < ab.min_x + 0.02f) {
        ab.min_x -= 0.01f;
        ab.max_x += 0.01f;
    }
    if (ab.max_y < ab.min_y + 0.02f) {
        ab.min_y -= 0.01f;
        ab.max_y += 0.01f;
    }
    if (cd.max_x < cd.min_x + 0.02f) {
        cd.min_x -= 0.01f;
        cd.max_x += 0.01f;
    }
    if (cd.max_y < cd.min_y + 0.02f) {
        cd.min_y -= 0.01f;
        cd.max_y += 0.01f;
    }
    dx = b->x - a->x;
    if (dx > 0.0f) {
        if (dx < 0.01f) slope_ab = 1600000.0f;
        else slope_ab = (b->y - a->y) / dx;
    } else {
        if (-dx < 0.01f) slope_ab = 1600000.0f;
        else slope_ab = (b->y - a->y) / dx;
    }
    dx = d->x - c->x;
    if (dx > 0.0f) {
        if (dx < 0.01f) slope_cd = 1600000.0f;
        else slope_cd = (d->y - c->y) / dx;
    } else {
        if (-dx < 0.01f) slope_cd = 1600000.0f;
        else slope_cd = (d->y - c->y) / dx;
    }
    intercept_ab = a->y - a->x * slope_ab;
    intercept_cd = c->y - c->x * slope_cd;
    if (slope_ab == slope_cd) {
        if (intercept_ab == intercept_cd) {
            hit.x = (a->x + b->x) / 2.0f;
            hit.y = (a->y + b->y) / 2.0f;
            found = 1;
        } else {
            found = 0;
        }
    } else {
        denominator = slope_ab - slope_cd;
        hit.x = 0.0f;
        if (denominator != 0.0f) {
            hit.x = (slope_ab * hit.x - intercept_ab) / denominator;
        }
        hit.y = slope_ab * hit.x + intercept_ab;
        found = 1;
    }
    if (!found) return 0;
    found = (ab.min_x <= hit.x && hit.x <= ab.max_x &&
             ab.min_y <= hit.y && hit.y <= ab.max_y &&
             cd.min_x <= hit.x && hit.x <= cd.max_x &&
             cd.min_y <= hit.y && hit.y <= cd.max_y);
    if (count != 0) {
        if (found) {
            equal = (a->x == c->x && a->y == c->y);
            if (equal) endpoint_count++;
            equal = (a->x == d->x && a->y == d->y);
            if (equal) endpoint_count++;
            equal = (b->x == c->x && b->y == c->y);
            if (equal) endpoint_count++;
            equal = (b->x == d->x && b->y == d->y);
            if (equal) endpoint_count++;
        }
        *count = endpoint_count;
    }
    if (out != 0) {
        out->x = hit.x;
        out->y = hit.y;
    }
    return found;
}
#endif /* NON_MATCHING */
