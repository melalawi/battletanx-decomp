#ifndef UNBAKE_FUNC_80115474_H
#define UNBAKE_FUNC_80115474_H
#include "types.h"

struct Ctx;
typedef struct Ctx Ctx;
typedef struct Header Header;

struct Header;





struct Ctx {
    char pad_0[4];
    int unk_4;
    int unk_8;
    char pad_c[0x65 - 0xC];
    unsigned char unk_65;
};
struct Header {
    int unk_0;
    int unk_4;
    unsigned long long unk_8;
    unsigned long long unk_10;
    unsigned short unk_18;
    unsigned char unk_1A;
    unsigned char unk_1B;
    short unk_1C;
    short unk_1E;
};
#endif
