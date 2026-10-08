#ifndef BT_MENU_RENDER_H
#define BT_MENU_RENDER_H
#include "types.h"
#include "gfx.h"

/* Menu drawing and timer interfaces reconstructed from the callee argument
 * reads. Existing scalar return contracts are retained when this caller
 * ignores their result. The timer returns its 64-bit O32 v0/v1 pair. */
int func_800798C0(int);
void func_80079BB4_us(int);
int func_80079BD4_us(void);
void func_80079BF4_us(int);
int func_800AD340_us(void);
int func_800AD5A0_us(void);
void func_800AD828_us(void);
void func_800ADD70_us(void);
void func_800AE2B8_us(void);
int func_800AE800_us(void);
void func_800AEA50_us(void);
void func_800AEF98_us(void);
int func_800AF534_us(void);
int func_800AFB08_us(void);
int func_800B0210_us(void);
void func_800B0440_us(void);
void func_800B098C_us(void);
void func_800B0D1C_us(void);
int func_800B1264_us(void);
int func_800B9C0C_us(void *);
int func_800B9C34_us(int, int);
struct Shape_func_800B8804_us;
int func_800F4DFC(struct Shape_func_800B8804_us *, int, int, int, int, int, int, int, int);
void func_801054E0(int);
void func_8010552C(int, int);
void func_8010555C(int, int, int, int);
void func_80105A50(Gfx **, char *, int, int);
void func_8010698C(Gfx **);
u64 func_801120A0_us(void);

#endif
