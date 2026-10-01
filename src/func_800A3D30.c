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
M2C_UNK func_80078634();                 /* extern */
M2C_UNK func_80078680();                 /* extern */
s32 func_8007AAA0();                                /* extern */
void *func_800A03B8();                           /* extern */
extern M2C_UNK D_80126128;                          /* unable to generate initializer: unknown type; const */
extern M2C_UNK D_80126140;                          /* unable to generate initializer: unknown type; const */

typedef struct func_800A3D30_S1 func_800A3D30_S1;
typedef struct func_800A3D30_S2 func_800A3D30_S2;
typedef struct { s32 value[3]; } FuncA3D30Table;
struct func_800A3D30_S1 { char pad0[0x20]; s16 unk20; char pad20[0x22]; u16 unk44; };
struct func_800A3D30_S2 {
    char pad0[1]; u8 unk1; char pad1[0x18 - 2]; s32 unk18;
    char pad18[0x504 - 0x1C]; s32 unk504;
};

void func_800A3D30(void *arg0) {
    func_800A3D30_S1 *ptr;
    s32 var_v0;
    void *temp_s0;
    func_800A3D30_S2 *temp_v0;

    ptr = arg0;
    temp_v0 = func_800A03B8(ptr->unk20);
    if (temp_v0->unk1 != 0) {
        if (ptr->unk44 == 1) {
            var_v0 = func_8007AAA0();
            temp_s0 = (var_v0 >= 3) ? (FuncA3D30Table *)&D_80126140 + 1 : &D_80126140;
        } else {
            var_v0 = func_8007AAA0();
            temp_s0 = (var_v0 >= 3) ? (FuncA3D30Table *)&D_80126128 + 1 : &D_80126128;
        }
        func_80078680((s8 *)ptr + 0x48, ((FuncA3D30Table *)temp_s0)->value[temp_v0->unk18]);
        temp_s0 = (s8 *)ptr + 0x48;
        func_80078634(temp_s0, temp_v0->unk504);
    }
}
