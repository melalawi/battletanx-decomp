/* When arg2 and the status field at offset 8 are zero, sets output code 10 and sign-specific data if func_800E3470 succeeds and the corresponding flag is set, otherwise setting code 1. */
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
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
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
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy
#define M2C_LOAD_SR(...) (0)
#define M2C_LOAD_GBR(...) (0)
#define M2C_LOAD_VBR(...) (0)
#define M2C_STORE_SR(a)
#define M2C_STORE_GBR(a)
#define M2C_STORE_VBR(a)
#define M2C_CMP_STR(a, b) (0)
#define M2C_TAS_B(a) (0)
#endif

s32 func_800E3470();

extern u8 D_8033B630;
extern u8 D_8033B631;
extern M2C_UNK D_8013957C;
extern M2C_UNK D_801395B8;

typedef struct { char pad0[0x24]; f32 unk24; } FuncEECA0Object;
typedef struct { char pad0[8]; s32 unk8; s32 unkC; } FuncEECA0Status;
typedef struct { s32 code; M2C_UNK *data; } FuncEECA0Output;

void func_800EECA0(FuncEECA0Object *arg0, FuncEECA0Status *arg1, s32 arg2, void *arg3, FuncEECA0Output *arg4) {
    s32 temp_arg3;
    s32 temp_arg0;

    temp_arg0 = (s32) arg0;
    temp_arg3 = (s32) arg4;

    if ((arg2 == 0) && (arg1->unk8 == 0)) {
        if (func_800E3470(arg1->unkC) != 0) {
            if (((FuncEECA0Object *) temp_arg0)->unk24 < 0.0f) {
                if (D_8033B630 != 0) {
                    ((FuncEECA0Output *) temp_arg3)->code = 0xA;
                    ((FuncEECA0Output *) temp_arg3)->data = &D_8013957C;
                    return;
                }
            } else if (D_8033B631 != 0) {
                ((FuncEECA0Output *) temp_arg3)->code = 0xA;
                ((FuncEECA0Output *) temp_arg3)->data = &D_801395B8;
                return;
            }
        }
        ((FuncEECA0Output *) temp_arg3)->code = 1;
    }
}
