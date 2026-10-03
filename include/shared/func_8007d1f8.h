#ifndef UNBAKE_FUNC_8007D1F8_H
#define UNBAKE_FUNC_8007D1F8_H
#include "types.h"

struct Info;
struct State;




struct Info {
    unsigned char pad[0x3c];
    unsigned char value;
};
struct State {
    int type;
    int pad[2];
    int ids[0x72];
    int values[1];
};
#endif
