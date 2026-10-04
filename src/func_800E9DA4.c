#include "span_1000/code_800E9538.h"
#include "types.h"

struct Ent;
typedef struct Ent Ent;
typedef struct Shape_func_800E9DA4 Shape_func_800E9DA4;

struct Shape_func_800E9DA4;





struct Ent {
    char pad0[4];
    struct Shape_func_800E9DA4 *obj;
};
struct Shape_func_800E9DA4 {
    char pad0[0x24];
    f32 x24;
    char pad28[4];
    f32 x2C;
    char pad30[0x6C];
    s32 x9C;
};

#include "types.h"
/* Returns an entity weight: 0 when func_800E3470 rejects its object, else 0.5 if the object state is 8 or 9, plus 0.5 - func_800E0BC4(position) / 16000 when that is positive. */


f32 func_800E0BC4(f32 *);
s32 func_800E3470(Shape_func_800E9DA4 *);

f32 func_800E9DA4(Ent *arg0) {
    f32 pos[2];
    f32 t;
    f32 r;
    s32 k;

    if (func_800E3470(arg0->obj) != 0) {
        return 0.0f;
    }
    k = arg0->obj->x9C;
    pos[1] = arg0->obj->x24;
    r = 0.0f;
    pos[0] = arg0->obj->x2C;
    if ((u32) (k - 8) < 2U) {
        r = 0.5f;
    }
    t = 0.5f - (func_800E0BC4(pos) / 16000.0f);
    if (t > 0.0f) {
        r += t;
    }
    return r;
}
