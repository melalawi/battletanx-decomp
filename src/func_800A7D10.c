#include "span_1000/code_800A7ABC.h"
#include "types.h"














#include "types.h"









/* Transforms a vector by the supplied matrix and translation. */
void func_800A7D10(func_800A7D10_S3_Shared800A7D10 *arg0, func_800A7D10_S1_Shared800A7D10 *arg1, func_800A7D10_S1_Shared800A7D10 *arg2) {
    arg2->unk0 = (f32) ((arg1->unk0 * arg0->unk0) + (arg1->unk4 * arg0->unk10) + (arg1->unk8 * arg0->unk20) + arg0->unk30);
    arg2->unk4 = (f32) ((arg1->unk0 * arg0->unk4) + (arg1->unk4 * arg0->unk14) + (arg1->unk8 * arg0->unk24) + arg0->unk34);
    arg2->unk8 = (f32) ((arg1->unk0 * arg0->unk8) + (arg1->unk4 * arg0->unk18) + (arg1->unk8 * arg0->unk28) + arg0->unk38);
}
