#ifndef BATTLETANX_CALLBACK_WORD_H
#define BATTLETANX_CALLBACK_WORD_H
#include "types.h"
/* Word at 0x10 and byte at 0x14 loaded by adjacent callback getters. */
typedef struct CallbackWord { u8 reserved[0x10]; s32 value; u8 flag; } CallbackWord;
#endif
