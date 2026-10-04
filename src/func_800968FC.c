#include "span_1000/code_80093D30.h"
/* func_800968FC -- forwards its two arguments to func_800A8EF8 with the second repeated and a zero fourth. */

extern void func_800A8EF8(int, int, int, int);
void func_800968FC(int a, int b) {
    func_800A8EF8(a, b, b, 0);
}
