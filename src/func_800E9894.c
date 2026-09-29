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
void *func_800A03B8();                      /* extern */
void *func_800A6688();                            /* extern */
extern M2C_UNK D_8033A980;

typedef struct func_800E9894_S1 func_800E9894_S1;
typedef struct func_800E9894_S2 func_800E9894_S2;
typedef struct func_800E9894_S3 func_800E9894_S3;
typedef struct func_800E9894_S4 func_800E9894_S4;
struct func_800E9894_S1 {
    void* unk0;
    char pad0[0x4 - 0x0 - sizeof(void*)];
    void* unk4;
    char pad4[0x8 - 0x4 - sizeof(void*)];
    func_800E9894_S3 * unk8;
    char pad8[0xC - 0x8 - sizeof(func_800E9894_S3 *)];
    void* unkC;
    char padC[0x10 - 0xC - sizeof(void*)];
    void* unk10;
    char pad10[0x14 - 0x10 - sizeof(void*)];
    s32 unk14;
    char pad14[0x18 - 0x14 - sizeof(s32)];
    s16 unk18;
    char pad18[0x1A - 0x18 - sizeof(s16)];
    s16 unk1A;
    char pad1A[0x1C - 0x1A - sizeof(s16)];
    u8 unk1C;
    char pad1C[0x40 - 0x1C - sizeof(u8)];
    s32 unk40;
    char pad40[0x44 - 0x40 - sizeof(s32)];
    s32 unk44;
};
struct func_800E9894_S2 {
    char pad0[0x4];
    u8 unk4;
};
struct func_800E9894_S3 {
    char pad0[0x4];
    u8 unk4;
    char pad5[0x9C - 0x5];
    u8 unk9C;
    char pad9D[0xCC - 0x9D];
    u8 unkCC;
};
struct func_800E9894_S4 {
    char pad0[0x1AE];
    u8 unk1AE;
};

/* Initializes an object from the selected resource and its metadata. */
void func_800E9894(func_800E9894_S1 *arg0, s16 arg1) {
    s16 temp_a1;
    u8 temp_v1;
    func_800E9894_S3 *temp_a0;
    func_800E9894_S2 *temp_v0;
    func_800E9894_S4 *temp_v0_2;

    temp_a1 = arg1 & 0xFF;
    arg0->unk14 = 2;
    arg0->unk18 = temp_a1;
    temp_v0 = func_800A03B8(arg1, temp_a1);
    arg0->unk8 = temp_v0;
    arg0->unk1A = (s16) temp_v0->unk4;
    temp_v0_2 = func_800A6688(arg0->unk8->unk4);
    arg0->unk4 = temp_v0_2;
    temp_v1 = temp_v0_2->unk1AE;
    temp_a0 = arg0->unk8;
    arg0->unk40 = 0;
    arg0->unk44 = 0;
    arg0->unk1C = temp_v1;
    arg0->unk0 = (void *) ((s8 *)(&D_8033A980) + ((temp_v1 & 0xFF) * 0x52));
    arg0->unkC = (void *)&temp_a0->unk9C;
    arg0->unk10 = (void *)&temp_a0->unkCC;
}
