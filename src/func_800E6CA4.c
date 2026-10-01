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
#define M2C_BREAK(...) (0)
#define M2C_SYNC(...) (0)
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
#define M2C_LOAD_SR(...) (0)
#define M2C_LOAD_GBR(...) (0)
#define M2C_LOAD_VBR(...) (0)
#define M2C_STORE_SR(a)
#define M2C_STORE_GBR(a)
#define M2C_STORE_VBR(a)

#define M2C_CMP_STR(a, b) (0)
#define M2C_TAS_B(a) (0)

#endif
/* Tests whether two points remain within the object's scaled distance threshold. */
f32 func_800E1A20(M2C_UNK, f32 *);                  
typedef struct func_800E6CA4_S1 func_800E6CA4_S1;
struct func_800E6CA4_S1 {
    char pad0[0x4D0];
    f32 unk4D0;
    char pad4D0[0x4D4 - 0x4D0 - sizeof(f32)];
    f32 unk4D4;
    char pad4D4[0x4D8 - 0x4D4 - sizeof(f32)];
    f32 unk4D8;
    char pad4D8[0x4DC - 0x4D8 - sizeof(f32)];
    f32 unk4DC;
    char pad4DC[0x4E0 - 0x4DC - sizeof(f32)];
    f32 unk4E0;
};

/* extern */

s32 func_800E6CA4(func_800E6CA4_S1 *arg0, M2C_UNK arg1) {
    f32 sp10[4];
    f32 temp_f20;
    f32 temp_f4;
    f32 arg0_2;
    f32 temp_f6;
    s32 var_v0;
    float temp_2;

    temp_f4 = arg0->unk4D4;
    sp10[1] = temp_f4;
    temp_f6 = arg0->unk4D0;
    sp10[0] = temp_f6;
    sp10[3] = temp_f4 + (arg0->unk4DC * arg0->unk4E0);
    sp10[2] = temp_f6 + ((arg0_2 = arg0->unk4D8) * arg0->unk4E0);
    temp_f20 = func_800E1A20(arg1, &sp10[0]);
    temp_2 = temp_f20 + func_800E1A20(arg1, &sp10[2]);
    var_v0 = 1;
    if (!(temp_2 < (arg0->unk4E0 * 1.2f))) {
        var_v0 = 0;
    }
    return var_v0;
}
