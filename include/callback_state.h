#ifndef CALLBACK_STATE_H
#define CALLBACK_STATE_H
#include "types.h"
/* func_800F2120 stores a word at offset 0x18. */
typedef struct CallbackState {
    u8 reserved[0x18];
    s32 state;
} CallbackState;
/* func_80119568 loads a word at offset 0x0C. */
typedef struct CallbackValue {
    u8 reserved[0x0C];
    s32 value;
} CallbackValue;
#endif
