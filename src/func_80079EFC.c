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
s32 func_80112140(); /* extern */
M2C_UNK func_8011B314();                  /* extern */
extern M2C_UNK D_80150340;
extern s32 D_80150350;
extern s32 D_80150354;

typedef struct {
    s32 unk0;
    s32 unk4;
    s8 unk8;
    s8 unk9;
    s8 padA[2];
    union {
        s32 values[4];
        struct {
            s32 unkC;
            s32 unk10;
            s32 unk14;
            s32 unk18;
        } fields;
    } tail;
} Func79EFCArg;

void func_80079EFC(void) {
    Func79EFCArg arg;
    s32 temp_v0;

    arg.unk0 = 0x30;
    arg.unk4 = 0x40;
    arg.unk8 = 0x10;
    arg.tail.values[0] = (s32) &D_80150340;
    arg.tail.values[1] = 0;
    arg.tail.values[2] = 0;
    arg.tail.values[3] = 0;
    arg.unk9 = 0;
    temp_v0 = func_80112140(0, 0, &D_80150340, 1, 0x88);
    D_80150350 = temp_v0;
    func_8011B314(temp_v0, &arg);
    D_80150354 = func_80112140(0, 0, &D_80150340, 1, 0x1C);
}
