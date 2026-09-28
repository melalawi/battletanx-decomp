/* func_80090F10 -- picks an index at random, weighted by the byte table D_802D5BA0 whose total is D_802D5BB7. */

extern unsigned int func_800F38F4(void);
extern unsigned char D_802D5BA0[];
extern unsigned char D_802D5BB7;
int func_80090F10(void) {
    int r;
    int i = 0;
    r = func_800F38F4() % D_802D5BB7;
    while (r >= D_802D5BA0[i]) {
        r -= D_802D5BA0[i++];
    }
    return i;
}
