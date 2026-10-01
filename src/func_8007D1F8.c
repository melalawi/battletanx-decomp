#ifdef NON_MATCHING
/* NON_MATCHING: equivalent dispatch; tool cannot currently score the jump-table version. */
struct State { int type; int pad[2]; int ids[0x72]; int values[1]; };
struct Info { unsigned char pad[0x3c]; unsigned char value; };
extern struct Info *func_800A68C0(int);
int func_8007D1F8(struct State *arg0, int arg1) {
    int type = arg0->type;
    if (type == 9) goto values;
    if ((unsigned)type < 3) { values: return arg0->values[arg1]; }
    if ((unsigned)(type - 3) < 5)
        return func_800A68C0(arg1 == 0 ? arg0->ids[0] :
            (arg0->ids[arg1] == arg0->ids[0] ? 9 : arg0->ids[arg1]))->value;
    if (type == 8)
        return 5 | (-(arg1 != 0) & 7);
    return 0;
}
#endif
