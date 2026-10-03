#ifndef UNBAKE_FUNC_800EEBEC_H
#define UNBAKE_FUNC_800EEBEC_H
#include "types.h"

struct FuncEEBECObject;
typedef struct FuncEEBECObject FuncEEBECObject;
typedef struct FuncEEBECOutput FuncEEBECOutput;
typedef struct FuncEEBECStatus FuncEEBECStatus;

struct FuncEEBECOutput;

struct FuncEEBECStatus;







struct FuncEEBECObject {
    char pad0[0x24];
    f32 unk24;
};
struct FuncEEBECOutput {
    s32 code;
    s32 *data;
};
struct FuncEEBECStatus {
    char pad_0[8];
    s32 field_8;
    s32 field_c;
};
#endif
