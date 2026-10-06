#ifdef NON_MATCHING
#include "types.h"
#include "common/types_f8bfabebf96f.h"
#include "span_1000/code_80107168.h"

extern f32 func_800F3AE0_us(s32);
extern f32 func_800F3B40_us(s32);

/* The output is the measured two-f32 direction, y then x. The two temporary
 * records reuse the published nine-halfword QueryBox layout. */
s32 func_8010A8A8_us(struct QueryBox *a, struct QueryBox *b, void *out_arg)
{
  struct QueryBox relative_a;
  struct QueryBox relative_b;
  f32 *out = (f32 *) out_arg;
  f32 dx;
  f32 dy;
  f32 cosine;
  f32 sine;
  f32 negative_sine;
  f32 direction_sine;
  f32 direction_cosine;
  f32 direction_x;
  f32 direction_y;
  s16 x;
  s16 y;
  if (func_8010A680_us(&relative_a, a, b) != 0)
  {
    return 0;
  }
  if (func_8010A680_us(&relative_b, b, a) != 0)
  {
    return 0;
  }
  negative_sine = a->values[1] - b->values[1];
  dx = negative_sine;
  dy = a->values[2] - b->values[2];
  cosine = func_800F3B40_us((u16) b->values[8]);
  sine = func_800F3AE0_us((u16) b->values[8]);
  x = (s16) ((s32) ((cosine * dx) - (sine * dy)));
  y = (s16) ((s32) ((sine * dx) + (cosine * dy)));
  relative_a.values[1] = x;
  relative_a.values[2] = y;
  relative_a.values[8] = ((u16) a->values[8]) - ((u16) b->values[8]);
  relative_a.values[3] = a->values[3];
  relative_a.values[4] = a->values[4];
  relative_a.values[5] = a->values[5];
  relative_a.values[6] = a->values[6];
  dy = func_800F3AE0_us((u16) b->values[8]);
  direction_sine = dy;
  direction_cosine = func_800F3B40_us((u16) b->values[8]);
  out[1] = 0.0f;
  out[0] = 0.0f;
  negative_sine = -direction_sine;
  if (relative_a.values[1] < 0)
  {
    out[0] = direction_sine;
    out[1] = -direction_cosine;
  }
  else
    if (relative_a.values[1] > 0)
  {
    out[1] = direction_cosine;
    out[0] = negative_sine;
  }
  if (relative_a.values[2] < 0)
  {
    direction_x = out[1];
    direction_x = direction_x + negative_sine;
    direction_y = out[0] - direction_cosine;
  }
  else
    if (relative_a.values[2] > 0)
  {
    direction_x = out[1];
    direction_x = direction_x - negative_sine;
    direction_y = out[0] + direction_cosine;
  }
  else
  {
    return 1;
  }
  out[1] = direction_x;
  out[0] = direction_y;
  return 1;
}
#endif /* NON_MATCHING */
