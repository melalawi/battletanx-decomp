#include "span_1000/code_8011E3F0.h"
/* func_8011E434 -- initialises one object by registering a pair of callbacks for it and then
 * clearing and filling three of its own words. The call takes the two function addresses and a
 * count of seven; afterwards the word at 0x14 is zeroed and the second and third arguments are
 * stored at 0x18 and 0x1C, in that order. Every access is a full word (lw/sw), so the object's
 * fields and both remaining arguments are int-wide.
 */

extern void func_8011F7F0(void *, void *, void *, int);
extern void func_80120390(void);
extern void func_80120360(void);

void func_8011E434(int *arg0, int arg1, int arg2) {
    func_8011F7F0(arg0, func_80120390, func_80120360, 7);
    arg0[5] = 0;
    arg0[6] = arg2;
    arg0[7] = arg1;
}
