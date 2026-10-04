#include "span_1000/code_8011DC00.h"
#include "span_1000/code_8011E3F0.h"
/* func_8011E488 -- initialises one object by handing func_8011F7F0 the object, its two handler
 * entry points and the count 6, then clearing the field at 0x14 and storing the two incoming
 * arguments at 0x18 and 0x1C. All three stores are sw, so the fields are words; the two handler
 * addresses are taken with %hi/%lo, so they are function pointers.
 */
extern void func_8011F7F0(void *, void *, void *, int);



void func_8011E488(int *arg0, int arg1, int arg2) {
    func_8011F7F0(arg0, func_8011E310, func_8011E2E0, 6);
    arg0[5] = 0;
    arg0[6] = arg2;
    arg0[7] = arg1;
}
