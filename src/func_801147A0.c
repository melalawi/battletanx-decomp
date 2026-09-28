/*
 * Writes a 4x4 identity matrix: for every row i and column j it stores 1.0f when
 * i == j and 0.0f otherwise, keeping the row pointer as the loop's induction
 * variable.
 * Types came from the disassembly: every store is a 32-bit swc1, so the matrix is
 * float and not double; the 1.0f comes from `lui $at, 0x3F80` plus `mtc1`, and the
 * 0.0f from `mtc1 $zero`, so both are single-precision literals. The inner j loop
 * is unrolled by the compiler, which is why i is compared against the literals
 * 0, 1, 2 and 3 held in registers.
 */
void func_801147A0(float (*m)[4]) {
    int i;
    int j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == j) {
                m[i][j] = 1.0f;
            } else {
                m[i][j] = 0.0f;
            }
        }
    }
}
