#ifndef BATTLETANX_CALLBACK_CONTROL_H
#define BATTLETANX_CALLBACK_CONTROL_H
#include "types.h"
/* Halfword written by func_800A4368 at offset 0x20. */
typedef struct CallbackControl { u8 reserved[0x20]; s16 value; } CallbackControl;
/* The direct caller overwrites v0 immediately after this call. */
extern void func_800A4368_us(s32);
#endif
