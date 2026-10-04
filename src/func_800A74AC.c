#include "span_1000/code_800A70E0.h"
#include "types.h"

struct func_800A74AC_S1;
typedef struct func_800A74AC_S1 func_800A74AC_S1;
typedef struct func_800A74AC_S2 func_800A74AC_S2;
typedef struct func_800A74AC_S3 func_800A74AC_S3;
typedef struct func_800A74AC_S4 func_800A74AC_S4;
typedef struct func_800A74AC_S6 func_800A74AC_S6;

struct func_800A74AC_S2;

struct func_800A74AC_S3;

struct func_800A74AC_S4;

struct func_800A74AC_S6;











struct func_800A74AC_S1 {
    char pad0[0x8];
    s32 unk8;
    void * unkC;
};
struct func_800A74AC_S2 {
    char pad0[0x4];
    u8 unk4;
    char pad4[0x93];
    void * unk98;
};
struct func_800A74AC_S3 {
    char pad0[0x1AE];
    u8 unk1AE;
};
struct func_800A74AC_S4 {
    char pad0[0xC];
    u8 unkC;
};
struct func_800A74AC_S6 {
    char pad0[0x2C];
    void * unk2C;
};

#include "types.h"
#define NULL ((void *)0)


#ifndef M2C_MACROS_H
#define M2C_MACROS_H

/* Unknown types */

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */

/* Bitwise (reinterpret) cast */

/* Unaligned reads */

/* Unhandled instructions */

/* Carry/overflow bits from partially-implemented instructions */

/* Memcpy patterns */

/* Sh2 control register loads/stores */

#endif
void *func_800A6688();                            /* extern */
s32 func_800A6E30();                  













/* extern */

/* Releases linked resources when the selected object matches the active one. */
void func_800A74AC(func_800A74AC_S4 *arg0, func_800A74AC_S1 *arg1, s32 arg2) {
    func_800A74AC_S3 *temp_s0;
    void *temp_s0_2;
    func_800A74AC_S2 *temp_s1;
    func_800A74AC_S6 *var_a0;

    if ((arg2 == 0) && (arg1->unk8 == 0)) {
        temp_s1 = arg1->unkC;
        temp_s0 = func_800A6688(temp_s1->unk4);
        if (temp_s0->unk1AE == (((func_800A74AC_S3 *)(func_800A6688(arg0->unkC)))->unk1AE)) {
            var_a0 = temp_s1->unk98;
            if (var_a0 != NULL) {
                do {
                    temp_s0_2 = var_a0->unk2C;
                    func_800A6E30(var_a0, arg0->unkC);
                    var_a0 = temp_s0_2;
                } while (var_a0 != NULL);
            }
            temp_s1->unk98 = NULL;
        }
    }
}
