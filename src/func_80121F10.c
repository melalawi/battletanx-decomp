#include "span_1000/code_80121F10.h"
/* func_80121F10 -- turns a virtual address into a physical one. An address in KSEG0
 * (0x80000000..0x9FFFFFFF) or KSEG1 (0xA0000000..0xBFFFFFFF) is masked with 0x1FFFFFFF;
 * anything else is handed to func_80121F90. The `sltu` comparisons fix the address and the
 * result as unsigned. Byte-identical over all 31 body words at -O1; it needs an
 * [toolchain].object_options entry of ["-O1"], and the split interval is 4 bytes longer than
 * the body because it swallows the alignment word at 0x80121F8C.
 */
extern unsigned int func_80121F90(void *vaddr);

unsigned int func_80121F10(void *vaddr) {
    if (((unsigned int) vaddr >= 0x80000000) && ((unsigned int) vaddr < 0xA0000000)) {
        return (unsigned int) vaddr & 0x1FFFFFFF;
    }
    if (((unsigned int) vaddr >= 0xA0000000) && ((unsigned int) vaddr < 0xC0000000)) {
        return (unsigned int) vaddr & 0x1FFFFFFF;
    }
    return func_80121F90(vaddr);
}
