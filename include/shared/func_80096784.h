#ifndef UNBAKE_FUNC_80096784_H
#define UNBAKE_FUNC_80096784_H
#include "types.h"

struct Func_80096784_Record;
struct Func_80096784_Value;




struct Func_80096784_Output;
struct Func_80096784_Output {
    u8 mode;
    u8 channel;
    char pad_2[2];
    s32 value;
};
struct Func_80096784_Record {
    u16 value;
    u8 mode;
    u8 channel;
    char pad_4[2];
};
struct Func_80096784_Value {
    u16 value;
    char pad_2[4];
};


#endif
