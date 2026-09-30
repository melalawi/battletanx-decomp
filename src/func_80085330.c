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
extern M2C_UNK D_80125860;                          /* unable to generate initializer: unknown type */
extern M2C_UNK D_801258D8;                          
typedef struct func_80085330_S1 func_80085330_S1;
typedef struct func_80085330_S2 func_80085330_S2;
typedef struct func_80085330_S3 func_80085330_S3;
struct func_80085330_S1 {
    s32 unk0;
    s32 unk4;
    u8 unk8;
};
struct func_80085330_S2 {
    s32 unk0;
    s32 unk4;
    M2C_UNK unk8;
};
struct func_80085330_S3 {
    s32 unk0;
    s32 unk4;
    M2C_UNK unk8;
};

/* unable to generate initializer: unknown type */

/* Rewrites matching display-list entries using the paired lookup tables. */
void func_80085330(void *arg0, s32 arg1) {
    M2C_UNK *var_a1;
    M2C_UNK *var_a2;
    s32 temp_t1;
    s32 var_t0;
    func_80085330_S1 *var_a0;
    func_80085330_S1 *var_a3;
    func_80085330_S2 *base_a1;
    func_80085330_S3 *base_a2;
    s32 magic;
    s32 replacement0;
    s32 replacement4;

    var_a0 = arg0;
    if (arg1 > 0) {
        /* FAKEMATCH: copy the command constant to steer its load before the loop bound. */
        magic = 0xB8000000;
        base_a1 = &D_80125860;
        base_a2 = &D_801258D8;
        temp_t1 = (s32)((arg1 << 3) + (u32)var_a0);
loop_2:
        if (var_a0->unk0 != magic) {
            var_t0 = 0;
            var_a3 = var_a0;
            var_a2 = base_a2;
            var_a1 = base_a1;
            do {
                if ((((func_80085330_S2 *)(var_a1))->unk0 == var_a3->unk0) && (((func_80085330_S2 *)(var_a1))->unk4 == var_a3->unk4)) {
                    replacement0 = ((func_80085330_S3 *)var_a2)->unk0;
                    replacement4 = ((func_80085330_S3 *)var_a2)->unk4;
                    var_a3->unk0 = replacement0;
                    var_a3->unk4 = replacement4;
                }
                var_a2 = &((func_80085330_S3 *)(var_a2))->unk8;
                var_t0 += 1;
                var_a1 = &((func_80085330_S2 *)(var_a1))->unk8;
            } while (var_t0 < 0xF);
            var_a0 = (void *)&var_a0->unk8;
            if ((s32) var_a0 < temp_t1) {
                goto loop_2;
            }
        }
    }
}
