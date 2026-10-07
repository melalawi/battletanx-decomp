#include "span_1000/code_800E9B9C.h"
#include "callback_queue.h"
#include "types.h"
#include "types.h"


























extern struct CallbackDescriptor *D_80137888[0x1E];

/* Pops pending callbacks from the object's queue at its shared +16 field. */
void func_800EA1FC(func_800E9894_S1_Shared800EA1FC *arg0, u32 arg1) {
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
