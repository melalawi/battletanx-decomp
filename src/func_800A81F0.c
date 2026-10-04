#include "span_1000/code_800A7ABC.h"
/* func_800A81F0 -- transposes the 3x3 part of a 4-float-row matrix into another. */

void func_800A81F0(float src[][4], float dst[][4]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            dst[j][i] = src[i][j];
        }
    }
}
