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
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
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
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy
#define M2C_LOAD_SR() (0)
#define M2C_LOAD_GBR() (0)
#define M2C_LOAD_VBR() (0)
#define M2C_STORE_SR(a)
#define M2C_STORE_GBR(a)
#define M2C_STORE_VBR(a)
#define M2C_CMP_STR(a, b) (0)
#define M2C_TAS_B(a) (0)
M2C_UNK func_800A7650();
M2C_UNK func_800A7744();
M2C_UNK func_800EC7A8();
typedef struct func_80078D90_S1 func_80078D90_S1;
typedef struct func_80078D90_S2 func_80078D90_S2;
struct func_80078D90_S1 { char pad0[0xC]; u8 unkC; char padC[1]; u16 unkE; s32 unk10; s32 unk14; };
struct func_80078D90_S2 { char pad0[4]; s32 unk4; };
/* note: Dispatches by the object's state to the appropriate update routine. */
void func_80078D90(func_80078D90_S1 *arg0, s32 arg1, s32 arg2, func_80078D90_S2 *arg3, s32 arg4) {
    u8 temp_v1;
    s32 state;
    if (arg2 == 1) {
        temp_v1 = arg0->unkC;
        state = temp_v1;
        if (temp_v1 != arg2) {
            if (state < 2) {
                if (temp_v1 != 0) {
                    return;
                }
            } else if (state >= 4) {
                return;
            }
            func_800A7650(arg4);
            func_800A7744(arg4, arg0->unk14, 0, arg0->unk10, (s32) arg0->unkE);
        } else {
            func_800EC7A8(arg4, arg3->unk4);
        }
    }
}
