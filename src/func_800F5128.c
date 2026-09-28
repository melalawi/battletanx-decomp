/* func_800F5128 -- shifts seventeen fresh bits from func_800F58F0 into D_8035CD24. */

extern int func_800F58F0(void);
extern int D_8035CD24;
void func_800F5128(void) {
    int i;
    for (i = 0; i <= 16; i++) {
        D_8035CD24 = D_8035CD24 * 2 + func_800F58F0();
    }
}
