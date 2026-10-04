#include "span_1000/code_8007C6D8.h"
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

#include "types.h"





extern struct Info *func_800A68C0(int);
int func_8007D1F8(struct State *arg0, int arg1) {
    switch (arg0->type) {
    case 0: case 1: case 2: case 9: return arg0->values[arg1];
    case 3: case 4: case 5: case 6: case 7:
        if (arg1 == 0) return func_800A68C0(arg0->ids[0])->value;
        { int id = arg0->ids[arg1];
          if (id == arg0->ids[0]) return func_800A68C0(9)->value;
          return func_800A68C0(id)->value;
        }
    case 8: return 5 | (-(arg1 != 0) & 7);
    default: return 0;
    }
}
