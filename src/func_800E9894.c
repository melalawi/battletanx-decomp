#include "span_1000/code_800A6864.h"
#include "span_1000/code_800E9200.h"
#include "span_1000/code_800E9B9C.h"
#include "types.h"


























#include "types.h"


void *func_800A03B8();                      /* extern */
void *func_800A6688();                            /* extern */











/* Initializes an object from the selected resource and its metadata. */
void func_800E9894(func_800E9894_S1_Shared800EA1FC *arg0, s16 arg1) {
    s16 temp_a1;
    u8 temp_v1;
    func_800E9894_S3_Shared800EA1FC *temp_a0;
    func_800E9894_S2_Shared800EA1FC *temp_v0;
    func_800A74AC_S3_Shared800A74AC *temp_v0_2;

    temp_a1 = arg1 & 0xFF;
    arg0->unk14 = 2;
    arg0->unk18 = temp_a1;
    temp_v0 = func_800A03B8(arg1, temp_a1);
    arg0->unk8 = temp_v0;
    arg0->unk1A = (s16) temp_v0->unk4;
    temp_v0_2 = func_800A6688(arg0->unk8->unk4);
    arg0->unk4 = temp_v0_2;
    temp_v1 = temp_v0_2->unk1AE;
    temp_a0 = arg0->unk8;
    arg0->unk40 = 0;
    arg0->unk44 = 0;
    arg0->unk1C = temp_v1;
    arg0->unk0 = (void *) ((s8 *)(&D_8033A980) + ((temp_v1 & 0xFF) * 0x52));
    arg0->unkC = (void *)&temp_a0->unk9C;
    arg0->unk10 = (void *)&temp_a0->unkCC;
}
