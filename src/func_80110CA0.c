#include "span_1000/code_80110CA0.h"
/* Shuts down the active view and returns the final teardown result. */
extern unsigned char D_803C4DC0;
extern int D_803C4D80[];
extern void func_8011BDA0(void);
extern void func_801112A8(int);
extern int func_8011BFD0(int, int *);
extern void func_80119240(void *, int, int);
extern void func_8011BDE4(void);

int func_80110CA0(void *arg0) {
    int ret;

    ret = 0;
    func_8011BDA0();
    if (D_803C4DC0 != 0) {
        func_801112A8(0);
        ret = func_8011BFD0(1, D_803C4D80);
        func_80119240(arg0, 0, 1);
    }
    ret = func_8011BFD0(0, D_803C4D80);
    D_803C4DC0 = 0;
    func_8011BDE4();
    return ret;
}
