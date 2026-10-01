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
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)expr + (offset)))

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
M2C_UNK func_801146A0();                /* extern */
extern void *D_801257D0[4]; 
typedef struct func_8007ED98_S1 func_8007ED98_S1;
typedef struct func_8007ED98_S2 func_8007ED98_S2;
typedef union func_8007ED98_S1_UE8 { u32 v0; s32 v1; } func_8007ED98_S1_UE8;
struct func_8007ED98_S1 {
    char pad0[0xD0];
    u16 unkD0;
    char padD0[0xD8 - 0xD0 - sizeof(u16)];
    void* unkD8;
    char padD8[0xE8 - 0xD8 - sizeof(void*)];
    func_8007ED98_S1_UE8 unkE8;
};
struct func_8007ED98_S2 {
    s32 unk0;
    char pad0[0x4 - 0x0 - sizeof(s32)];
    s32 unk4;
    char pad4[0x8 - 0x4 - sizeof(s32)];
    u8 unk8;
};

/* const */

s32 func_8007ED98(s32 unused, s32 arg1) {
    s32 var_a2 = 0;
    u32 temp_a1;
    func_8007ED98_S2 *temp_a0;
    func_8007ED98_S1 *temp_s0;

    temp_s0 = *D_801257D0;
    do {
        if ((u32) (temp_a1 = temp_s0->unkE8.v0) >= (u32) ((*(s32 *)((s8 *)(((s8 *)temp_s0 + (temp_s0->unkD0 * 0x18))) + 0xA4)) + 0xC000)) {
            break;
        }
        func_801146A0(unused, temp_a1, var_a2);
        temp_a0 = temp_s0->unkD8;
        temp_s0->unkD8 = (void *)&temp_a0->unk8;
        temp_a0->unk0 = (s32) (((arg1 & 0xFF) << 0x10) | 0x01000040);
        temp_a0->unk4 = (s32) (temp_s0->unkE8.v1 - 0x80000000);
        var_a2 = temp_s0->unkE8.v1;
        temp_s0->unkE8.v1 = (s32) (var_a2 + 0x40);
    } while (0);
    return var_a2;
}
