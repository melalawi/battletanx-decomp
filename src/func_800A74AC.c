typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
#define NULL ((void *)0)


#ifndef M2C_MACROS_H
#define M2C_MACROS_H

/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_DCACHE_CLEAN(addr) (0)
#define M2C_DCACHE_INVALIDATE(addr) (0)
#define M2C_DCACHE_CLEAN_INVALIDATE(addr) (0)
#define M2C_DCACHE_BLOCK_SETZERO(addr) (0)
#define M2C_DCACHE_BLOCK_SETZERO_LOCKED(addr) (0)
#define M2C_ICACHE_INVALIDATE(addr) (0)
#define M2C_PREFETCH(addr) (0)
#define M2C_PREFETCH_STORE(addr) (0)

#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

/* Sh2 control register loads/stores */
#define M2C_LOAD_SR() (0)
#define M2C_LOAD_GBR() (0)
#define M2C_LOAD_VBR() (0)
#define M2C_STORE_SR(a)
#define M2C_STORE_GBR(a)
#define M2C_STORE_VBR(a)

#define M2C_CMP_STR(a, b) (0)
#define M2C_TAS_B(a) (0)

#endif
void *func_800A6688();                            /* extern */
M2C_UNK func_800A6E30();                  
typedef struct func_800A74AC_S1 func_800A74AC_S1;
typedef struct func_800A74AC_S2 func_800A74AC_S2;
typedef struct func_800A74AC_S3 func_800A74AC_S3;
typedef struct func_800A74AC_S4 func_800A74AC_S4;
typedef struct func_800A74AC_S5 func_800A74AC_S5;
typedef struct func_800A74AC_S6 func_800A74AC_S6;
struct func_800A74AC_S1 {
    char pad0[0x8];
    s32 unk8;
    void* unkC;
};
struct func_800A74AC_S2 {
    char pad0[0x4];
    u8 unk4;
    char pad4[0x93];
    void* unk98;
};
struct func_800A74AC_S3 {
    char pad0[0x1AE];
    u8 unk1AE;
};
struct func_800A74AC_S4 {
    char pad0[0xC];
    u8 unkC;
};
struct func_800A74AC_S5 {
    char pad0[0x1AE];
    u8 unk1AE;
};
struct func_800A74AC_S6 {
    char pad0[0x2C];
    void* unk2C;
};

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
        if (temp_s0->unk1AE == (((func_800A74AC_S5 *)(func_800A6688(arg0->unkC)))->unk1AE)) {
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
