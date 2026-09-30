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
s32 func_800E52A0();                        
typedef struct func_800E34B4_S1 func_800E34B4_S1;
typedef struct func_800E34B4_S2 func_800E34B4_S2;
typedef union func_800E34B4_S1_U8 { u8 v0; f32 v1; } func_800E34B4_S1_U8;
struct func_800E34B4_S1 {
    s32 unk0;
    void* unk4;
    func_800E34B4_S1_U8 unk8;
    f32 unkC;
    void* unk10;
    s32 unk14;
};
struct func_800E34B4_S2 {
    char pad0[0x24];
    f32 unk24;
    char pad24[0x4];
    f32 unk2C;
};

/* extern */

void func_800E34B4(func_800E34B4_S1 *arg0, s16 arg1, s16 arg2) {
    func_800E34B4_S2 *temp_v0;
    f32 *ordered_value;

    if (arg2 != 0xFF) {
        func_800A03B8(arg1);
        (void)(arg2 << 0x10);
        temp_v0 = func_800A03B8(arg2);
        arg0->unk10 = temp_v0;
        arg0->unk14 = func_800E52A0(arg1, arg2);
        arg0->unkC = (f32) temp_v0->unk24;
        ordered_value = &arg0->unk8.v1;
        *ordered_value = (f32) temp_v0->unk2C;
        arg0->unk4 = (void *)&arg0->unk8.v0;
        arg0->unk0 = 1;
        return;
    }
    arg0->unk0 = 0;
    arg0->unk4 = NULL;
}
