/* func_8011BFD0 -- starts a 64-byte PI DMA in one direction after checking the interface is
 * idle. The buffer's physical address goes to PI_DRAM_ADDR and the cartridge address
 * 0x1FC007C0 to PI_CART_ADDR for a read or to PI_WR_LEN for a write, both as word stores.
 * The registers are written through constant volatile pointers rather than named externs,
 * which is what puts their addresses in scratch registers instead of $at. Byte-identical over
 * all 43 body words at -O1; it needs an [toolchain].object_options entry of ["-O1"], and the
 * split interval is 4 bytes longer than the body because it swallows the alignment word at
 * 0x8011C07C.
 */
#define PI_DRAM_ADDR (*(volatile unsigned int *) 0xA4800000)
#define PI_CART_ADDR (*(volatile unsigned int *) 0xA4800004)
#define PI_WR_LEN    (*(volatile unsigned int *) 0xA4800010)

extern int func_8011C080(void);
extern void func_801226A0(void *buffer, int length);
extern unsigned int func_80121F10(void *vaddr);
extern void func_801124C0(void *buffer, int length);

int func_8011BFD0(int direction, void *buffer) {
    if (func_8011C080() != 0) {
        return -1;
    }
    if (direction == 1) {
        func_801226A0(buffer, 0x40);
    }
    PI_DRAM_ADDR = func_80121F10(buffer);
    if (direction == 0) {
        PI_CART_ADDR = 0x1FC007C0;
    } else {
        PI_WR_LEN = 0x1FC007C0;
    }
    if (direction == 0) {
        func_801124C0(buffer, 0x40);
    }
    return 0;
}
