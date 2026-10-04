#include "span_1000/code_80077930.h"
#include "types.h"

struct InitArgs;
typedef struct InitArgs InitArgs;



struct InitArgs {
    s32 pad[6];
};

#include "types.h"

extern void func_80110C00(void *, s32);
extern void func_801124C0(s32, s32);
extern void func_801185D0(void *, s32, s32, s32, s32, s32, s32 *);
extern void func_80119240(s32 *, s32, s32);
extern s32 D_8014C0B0;

/* Initializes the shared game data after preparing its startup arguments. */
void func_80077930(s32 arg0, s32 arg1, s32 arg2) {
    InitArgs args;
    s32 temp;

    if (arg2 != 0) {
        func_80110C00(&args, 0x18);
        func_80110C00(&temp, 4);
        func_801124C0(arg1, arg2);
        func_801185D0(&args, 0, 0, arg0, arg1, arg2, &D_8014C0B0);
        func_80119240(&D_8014C0B0, 0, 1);
    }
}
