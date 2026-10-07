#include "span_1000/code_800F45C8.h"

/* func_800F5128 -- shifts seventeen fresh bits from func_800F58F0 into D_8035CD24. */



void func_800F5128(void) {
    int i;
    for (i = 0; i <= 16; i++) {
        D_8035CD24 = D_8035CD24 * 2 + func_800F58F0();
    }
}

/* func_800F5178 -- the adaptive model's initial state, as LZARI's StartModel sets it up.
 *
 * Every symbol starts with frequency one, so the cumulative table counts down from 314 to 0; the
 * position table is the running sum of 10000 / (i + 200) over the 4096-entry window. */

extern int D_8035CD30[314];     /* char_to_sym */
extern int D_8035D220[314 + 1]; /* sym_to_char */
extern int D_8035D710[314 + 1]; /* sym_freq */
extern int D_8035DC00[314 + 1]; /* sym_cum */
extern int D_8035E0F0[4096 + 1];      /* position_cum */

void func_800F5178(void) {
    int ch, sym, i;

    D_8035DC00[314] = 0;
    for (sym = 314; sym >= 1; sym--) {
        ch = sym - 1;
        D_8035CD30[ch] = sym;
        D_8035D220[sym] = ch;
        D_8035D710[sym] = 1;
        D_8035DC00[sym - 1] = D_8035DC00[sym] + D_8035D710[sym];
    }
    D_8035D710[0] = 0;
    D_8035E0F0[4096] = 0;
    for (i = 4096; i >= 1; i--)
        D_8035E0F0[i - 1] = D_8035E0F0[i] + 10000 / (i + 200);
}
