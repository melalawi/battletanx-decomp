#include "span_1000/code_8007963C.h"
/* func_80079A5C -- unless the handle is -1, sets it and then the float value on the object D_80150380 holds. */

extern int D_80150380;
extern void func_8011CB90(int, short);
extern void func_8011CB00(int, float);
void func_80079A5C(int a, float b) {
    if (a != -1) {
        func_8011CB90(D_80150380, a);
        func_8011CB00(D_80150380, b);
    }
}
