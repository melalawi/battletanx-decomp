#ifdef NON_MATCHING
#include "types.h"
#include "span_1000/code_801130A0.h"
#include "span_1000/code_80114520.h"

extern f32 func_8011D190_us(f32);

/* Every scalar argument is consumed by lwc1. O32 places these floats after
 * the matrix pointer in integer argument slots; there are no double inputs.
 * The inverses deliberately use double division then round to float, as the
 * cartridge does. This prepared source awaits public ABI admission/proof. */
void func_80113460_us(void *matrix_arg, f32 eye_x, f32 eye_y, f32 eye_z,
                     f32 at_x, f32 at_y, f32 at_z,
                     f32 up_x, f32 up_y, f32 up_z)
{
    f32 (*m)[4] = (f32 (*)[4])matrix_arg;
    f32 look_x;
    f32 look_y;
    f32 look_z;
    f32 right_x;
    f32 right_y;
    f32 right_z;
    f32 inv;

    func_801147A0(m);
    look_x = at_x - eye_x;
    look_y = at_y - eye_y;
    look_z = at_z - eye_z;
    inv = (f32)(-1.0 / (f64)func_8011D190_us(
        (look_x * look_x + look_y * look_y) + look_z * look_z));
    look_x *= inv;
    look_y *= inv;
    look_z *= inv;
    right_x = up_y * look_z - up_z * look_y;
    right_y = up_z * look_x - up_x * look_z;
    right_z = up_x * look_y - up_y * look_x;
    inv = (f32)(1.0 / (f64)func_8011D190_us(
        (right_x * right_x + right_y * right_y) + right_z * right_z));
    right_x *= inv;
    right_y *= inv;
    right_z *= inv;
    up_x = look_y * right_z - look_z * right_y;
    up_y = look_z * right_x - look_x * right_z;
    up_z = look_x * right_y - look_y * right_x;
    inv = (f32)(1.0 / (f64)func_8011D190_us(
        (up_x * up_x + up_y * up_y) + up_z * up_z));
    up_x *= inv;
    up_y *= inv;
    up_z *= inv;
    m[0][0] = right_x;
    m[1][0] = right_y;
    m[2][0] = right_z;
    m[3][0] = -((eye_x * right_x + eye_y * right_y) + eye_z * right_z);
    m[0][1] = up_x;
    m[1][1] = up_y;
    m[2][1] = up_z;
    m[3][1] = -((eye_x * up_x + eye_y * up_y) + eye_z * up_z);
    m[0][2] = look_x;
    m[1][2] = look_y;
    m[2][2] = look_z;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][2] = -((eye_x * look_x + eye_y * look_y) + eye_z * look_z);
    m[3][3] = 1.0f;
}
#endif /* NON_MATCHING */
