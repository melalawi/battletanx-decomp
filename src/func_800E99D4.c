#include "span_1000/code_800E9538.h"
#include "types.h"

struct ResetState;


struct ResetState {
    char pad[0x40];
    int field40;
    int field44;
};



void func_800E99D4(struct ResetState *arg0) {
    arg0->field40 = 0;
    arg0->field44 = 0;
}
