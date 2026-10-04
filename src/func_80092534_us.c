#include "common/types.h"
#include "span_1000/code_80090F94.h"
/* Scale the query box, collect nearby results, and dispatch their callbacks. */
#include "types.h"
void func_80092534_us(QueryObject *object) {
    QueryWork work;
    int i;
    float f0, f1, f2, f3, f4;
    work.box = D_803B8254[object->index].box;
    f0 = work.box.values[3] * D_80071EA0;
    f1 = work.box.values[4] * D_80071EA0;
    f2 = work.box.values[5] * D_80071EA0;
    f3 = work.box.values[6] * D_80071EA0;
    f4 = work.box.values[7] * D_80071EA0;
    work.box.values[3] = (int)f0;
    work.box.values[4] = (int)f1;
    work.box.values[5] = (int)f2;
    work.box.values[6] = (int)f3;
    work.box.values[7] = (int)f4;
    func_80107A14_us(&work.box, 0x20, work.results, &work.count);
    for (i = 0; i < work.count; i++) {
        if ((u32)work.results[i] >= 4 && D_802C3804[work.results[i]->kind].callback != 0) {
            D_802C3804[work.results[i]->kind].callback(work.results[i], object, 0, work.callbackData, work.callbackOutput);
        }
    }
}
