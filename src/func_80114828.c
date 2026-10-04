#include "span_1000/code_80114190.h"
/* Builds a 4x4 identity matrix in a stack buffer and hands it, with the
   caller's argument, to the routine that consumes it. The 0x58 frame with
   $ra at 0x14 fixed the buffer as the 0x40 bytes at 0x18, which the identity
   writer's swc1 stores make a float[4][4]. */

extern void func_801146A0(float (*m)[4], void *arg);

void func_80114828(void *arg) {
    float m[4][4];

    func_801147A0(m);
    func_801146A0(m, arg);
}
