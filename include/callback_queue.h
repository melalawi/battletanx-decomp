#ifndef BATTLETANX_CALLBACK_QUEUE_H
#define BATTLETANX_CALLBACK_QUEUE_H
#include "types.h"
/* EA1FC loads the callback at +4; EA1B8 loads payload at +12.
 * Both select this table by an entry kind. Queue entries have stride 8. */
struct CallbackDescriptor {
    u32 reserved0;
    s32 (*callback)(void *);
    u32 reserved8;
    u32 payload;
};
struct CallbackQueueSlot {
    u32 kind;
    u32 payload;
};
#endif
