/* func_800DDCA4 -- initialises a header in place: its data pointer to just past the header, four halfwords to zero and the last to 0xF8; returns the header. */

typedef struct { void *unk0; short unk4; short unk6; short unk8; short unkA; short unkC; } S;
S *func_800DDCA4(S *arg0) {
    arg0->unk0 = (char *)arg0 + 0x10;
    arg0->unk4 = 0;
    arg0->unk6 = 0;
    arg0->unk8 = 0;
    arg0->unkA = 0;
    arg0->unkC = 0xF8;
    return arg0;
}
