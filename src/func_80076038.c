/* func_80076038 -- ORs its argument into what func_800771F4 returns and hands the result to func_80077200. */

extern int func_800771F4(void);
extern void func_80077200(int);
void func_80076038(int a) {
    func_80077200(func_800771F4() | a);
}
