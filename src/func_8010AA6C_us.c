#ifdef NON_MATCHING
#include "span_1000/code_80091A60.h"
#include "span_1000/code_80107168.h"
#include "types.h"

/* Incoming coordinates are copied in four eight-byte aggregates. Both
 * components are consumed as single precision. No alignment/padding fields. */


s32 func_8010AA6C_us(struct PolygonPoint a, struct PolygonPoint b,
                    struct PolygonPoint c, struct PolygonPoint d,
                    struct PolygonPoint *remaining,
                    struct PolygonPoint *intersection)
{
    struct PolygonPoint hit;
    f64 ay = (f64)(b.y - a.y);
    f64 ax = (f64)(b.x - a.x);
    f64 bx = (f64)(d.x - c.x);
    f64 by = (f64)(d.y - c.y);
    f64 rx = (f64)(a.x - c.x);
    f64 ry = (f64)(a.y - c.y);
    f64 denominator = bx * ay - by * ax;
    f64 t;
    f64 u;
    s32 state;

    if (denominator == 0.0) {
        state = (rx * ay - ry * ax == 0.0) ? 2 : 0;
    } else {
        t = (rx * ay - ry * ax) / denominator;
        u = (rx * by - ry * bx) / denominator;
        state = (((0.0 <= t) & (t <= 1.0)) &&
                 ((0.0 <= u) & (u <= 1.0))) ? 1 : 0;
        hit.x = (f32)((f64)c.x + t * (f64)(d.x - c.x));
        hit.y = (f32)((f64)c.y + t * (f64)(d.y - c.y));
    }
    if (state == 1) {
        remaining->x = d.x - hit.x;
        remaining->y = d.y - hit.y;
        intersection->x = hit.x;
        intersection->y = hit.y;
        return 1;
    }
    return 0;
}
#endif /* NON_MATCHING */
