/* func_800F5178 -- the adaptive model's initial state, as LZARI's StartModel sets it up.
 *
 * Every symbol starts with frequency one, so the cumulative table counts down from 314 to 0; the
 * position table is the running sum of 10000 / (i + 200) over the 4096-entry window. */

#define N 4096
#define N_CHAR 314

extern int D_8035CD30[N_CHAR];     /* char_to_sym */
extern int D_8035D220[N_CHAR + 1]; /* sym_to_char */
extern int D_8035D710[N_CHAR + 1]; /* sym_freq */
extern int D_8035DC00[N_CHAR + 1]; /* sym_cum */
extern int D_8035E0F0[N + 1];      /* position_cum */

void func_800F5178(void) {
    int ch, sym, i;

    D_8035DC00[N_CHAR] = 0;
    for (sym = N_CHAR; sym >= 1; sym--) {
        ch = sym - 1;
        D_8035CD30[ch] = sym;
        D_8035D220[sym] = ch;
        D_8035D710[sym] = 1;
        D_8035DC00[sym - 1] = D_8035DC00[sym] + D_8035D710[sym];
    }
    D_8035D710[0] = 0;
    D_8035E0F0[N] = 0;
    for (i = N; i >= 1; i--)
        D_8035E0F0[i - 1] = D_8035E0F0[i] + 10000 / (i + 200);
}
