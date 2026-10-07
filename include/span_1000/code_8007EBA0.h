#ifndef UNBAKE_SPAN_1000_CODE_8007EBA0_H
#define UNBAKE_SPAN_1000_CODE_8007EBA0_H
#include "../types.h"
#include "gfx.h"
#include "types.h"
/* unbake published declaration: published_05593061e302b687a02ab91c */
extern void *func_8007F030_us(void);


/* unbake published declaration: published_1590df0aab5fd6772b1b8e34 */
extern int func_8008001C_us(int arg0, int arg1, int arg2, int arg3, unsigned char arg4);


/* unbake published declaration: published_198938effae6a385f1df527e */
extern u8 D_801B4C00[];


/* unbake published declaration: published_2c5d155f4b03ddd5e2183210 */
extern void func_8007FF68(void);


struct Shape_func_8008001C_us;

struct Func8007EC38Catalog_Shared8007EC38;
typedef struct Func8007EC38Catalog_Shared8007EC38 Func8007EC38Catalog_Shared8007EC38;
typedef struct Func8007EC38Entry_Shared8007EC38 Func8007EC38Entry_Shared8007EC38;
typedef struct func_8007EC38_S1_Shared8007EC38 func_8007EC38_S1_Shared8007EC38;
typedef union func_8007EC38_S1_UE8_Shared8007EC38 func_8007EC38_S1_UE8_Shared8007EC38;

struct Func8007EC38Entry_Shared8007EC38;

struct func_8007EC38_S1_Shared8007EC38;

union func_8007EC38_S1_UE8_Shared8007EC38;

struct func_8007ECE8_S1_Shared8007ECE8;
typedef struct func_8007ECE8_S1_Shared8007ECE8 func_8007ECE8_S1_Shared8007ECE8;

struct Func_8007FF68_View0_Shared8007FF68;
struct Func_8007FF68_View1_Shared8007FF68;
struct Func8007EC38Entry_Shared8007EC38 {
    s32 threshold;
    char pad4[0x14];
};
struct Func_8007FF68_View0_Shared8007FF68 {
    char pad_0[0x88];
    s32 field_88;
};
struct Func_8007FF68_View1_Shared8007FF68 {
    char pad_0[0x140];
    s32 field_140;
};
struct Shape_func_8008001C_us {
    unsigned char unknown_0[4];
    unsigned char unknown_4[4];
};

struct Shape_func_8008001C_us;

/* unbake published declaration: published_398a3c360a1fc1dc72049c79 */
extern struct Shape_func_8008001C_us * D_801B6C00;


/* unbake published declaration: published_90445e1af551f2724f0de220 */
extern int func_8007EC38(int unused, int arg1);


/* unbake published declaration: published_bc9cc1924773ad0cb226168c */
extern int func_8007EF40_us(int);


/* unbake published declaration: published_cdbf3d49f0a1ce16048a6465 */
extern int func_8007ED98(int unused, int arg1);


/* unbake published declaration: published_d133e003a1048f78d3cf37aa */
extern int func_8007ECE8(int unused, int arg1);


/* unbake published declaration: published_de4580f8df5792b6bdbb7dc3 */
extern void * func_8007F060(void);


/* unbake published declaration: published_e68e33566cd43a12f3b43f73 */
extern int func_8007EE48(int unused, int arg1);


extern int func_8007EEF8_us(int arg0);

extern int func_8007EF1C_us(int arg0);

extern void * func_8007F00C_us();

extern void * func_8007F040_us();

extern int func_8007F2A0_us();








union func_8007EC38_S1_UE8_Shared8007EC38 {
    u32 v0;
    s32 v1;
};
struct Func8007EC38Catalog_Shared8007EC38 {
    char pad0[0xA4];
    Func8007EC38Entry_Shared8007EC38 entries[1];
};
struct func_8007ECE8_S1_Shared8007ECE8 {
    char pad0[0xD0];
    u16 unkD0;
    char padD0[0xDC - 0xD0 - sizeof(u16)];
    void * unkDC;
    char padDC[0xE8 - 0xDC - sizeof(void*)];
    func_8007EC38_S1_UE8_Shared8007EC38 unkE8;
};
struct func_8007EC38_S1_Shared8007EC38 {
    char pad0[0xD0];
    u16 unkD0;
    char padD0[0xD8 - 0xD0 - sizeof(u16)];
    void * unkD8;
    char padD8[0xE8 - 0xD8 - sizeof(void*)];
    func_8007EC38_S1_UE8_Shared8007EC38 unkE8;
};






#endif
