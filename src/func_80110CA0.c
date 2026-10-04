#include "span_1000/code_8010DED4.h"
/* FAKEMATCH: The volatile return local preserves the target stack stores of overwritten intermediate results; these stores are compiler-shape preservation, not required hardware semantics. */
/*
 * Shuts one screen down: it always calls func_8011BDA0 first, and when the byte
 * flag D_803C4DC0 is set it also tears down the active view -- func_801112A8(0),
 * func_8011BFD0(1, D_803C4D80) and func_80119240(arg0, 0, 1) -- before calling
 * func_8011BFD0(0, D_803C4D80) again, clearing the flag and calling func_8011BDE4.
 * The result of the last func_8011BFD0 is returned.
 * Types came from the disassembly: D_803C4DC0 is loaded with lbu and cleared with
 * sb, so it is an unsigned char; D_803C4D80 is only ever formed as an address
 * (lui + addiu of %hi/%lo, never loaded), so it is an array passed by address; and
 * the return value lives in the frame at 0x1C and is written on every assignment
 * including the dead first two, which is what fixes it as a volatile local.
 */
extern unsigned char D_803C4DC0;
extern int D_803C4D80[];
extern void func_8011BDA0(void);
extern void func_801112A8(int);
extern int func_8011BFD0(int, int *);
extern void func_80119240(void *, int, int);
extern void func_8011BDE4(void);

int func_80110CA0(void *arg0) {
    volatile int ret;

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
