#include "callback_queue.h"
#include "span_1000/code_800EA1EC.h"
#include "types.h"
#include "types.h"

struct func_800E9894_S1;
typedef struct func_800E9894_S1 func_800E9894_S1;
typedef struct func_800E9894_S2 func_800E9894_S2;
typedef struct func_800E9894_S3 func_800E9894_S3;
typedef struct func_800E9894_S4 func_800E9894_S4;

struct func_800E9894_S2;

struct func_800E9894_S3;

struct func_800E9894_S4;









struct func_800E9894_S1 {
    void * unk0;
    void * unk4;
    struct func_800E9894_S3 * unk8;
    void * unkC;
    void * unk10;
    s32 unk14;
    s16 unk18;
    s16 unk1A;
    u8 unk1C;
    char pad1C[0x40 - 0x1C - sizeof(u8)];
    s32 unk40;
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

extern struct CallbackDescriptor *D_80137888[0x1E];

/* Pops pending callbacks from the object's queue at its shared +16 field. */
void func_800EA1FC(func_800E9894_S1 *arg0, u32 arg1) {
    s32 (*temp_v0)(void *);
    u32 *arg0_2;
    u32 *temp_v0_2;
    if (arg1 < (u32) *(u32 *)arg0->unk10) {
        temp_v0_2 = arg0->unk10;
        do {
            temp_v0 = D_80137888[((struct CallbackQueueSlot *)((u32)temp_v0_2 - (-(*temp_v0_2 * sizeof(struct CallbackQueueSlot)))))->kind]->callback;
            if (temp_v0 != 0) {
                temp_v0(arg0);
            }
            arg0_2 = arg0->unk10;
            *arg0_2 -= 1;
        } while (arg1 < (u32) *(temp_v0_2 = arg0->unk10));
    }
}
