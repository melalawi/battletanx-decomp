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
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */

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
extern u8 D_802D8141;
extern M2C_UNK D_802D8144;
extern s32 D_802D8148;
extern s32 D_802D814C;
extern M2C_UNK D_802E17A8;
extern M2C_UNK D_802E17B8;
extern M2C_UNK D_802E17D8;

/* Extracts and transforms values from data tables, storing the results in global variables. */
void *func_80096784(s32 arg0) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v1;
    u16 temp_v0;
    u16 temp_v1_2;
    void *temp_a2;

    temp_v1 = M2C_FIELD(&D_802E17A8, s32 *, (arg0 * 4)) * 6;
    temp_a2 = (s8 *)(&D_802E17D8) + temp_v1;
    temp_v0 = M2C_FIELD(temp_a2, u16 *, 0);
    temp_v1_2 = M2C_FIELD(&D_802E17B8, u16 *, temp_v1);
    temp_a1 = temp_v0 | ((u32) (temp_v0 & 0xF00) >> 8) | ((temp_v0 & 0xF) << 8);
    temp_a0 = temp_v1_2 | ((u32) (temp_v1_2 & 0xF00) >> 8) | ((temp_v1_2 & 0xF) << 8);
    M2C_FIELD(&D_802D8144, s32 *, 0) = temp_a1;
    D_802D8148 = temp_a1 & ~temp_a0;
    D_802D814C = temp_a0 & ~temp_a1;
    M2C_FIELD(&D_802D8144, u8 *, -4) = (u8) M2C_FIELD(temp_a2, u8 *, 2);
    D_802D8141 = M2C_FIELD(temp_a2, u8 *, 3);
    return (s8 *)(&D_802D8144) + -4;
}
