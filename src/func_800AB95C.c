#include "shared/func_800ab95c.h"
/* func_800AB95C -- selects one of five modes, taking the mode's value from a five-entry table as the current value, and returns the mode that was set before. */


extern M D_803275F0;
int func_800AB95C(unsigned int a) {
    int old = D_803275F0.mode;
    switch (a) {
    case 0: D_803275F0.mode = 0; D_803275F0.cur = D_803275F0.tbl[0]; break;
    case 1: D_803275F0.mode = 1; D_803275F0.cur = D_803275F0.tbl[1]; break;
    case 2: D_803275F0.mode = 2; D_803275F0.cur = D_803275F0.tbl[2]; break;
    case 3: D_803275F0.mode = 3; D_803275F0.cur = D_803275F0.tbl[3]; break;
    case 4: D_803275F0.mode = 4; D_803275F0.cur = D_803275F0.tbl[4]; break;
    }
    return old;
}
