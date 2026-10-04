#ifndef UNBAKE_SPAN_1000_CODE_80090F94_H
#define UNBAKE_SPAN_1000_CODE_80090F94_H
#include "common/types.h"
#include "../types.h"
struct QueryWork;
/* unbake published declaration: published_1c2d79c8c1aa035409008f65 */
typedef struct QueryWork QueryWork;

struct QueryResult;
/* unbake published declaration: published_4de71db0263339d0bea590ce */
typedef struct QueryResult QueryResult;

struct QueryObject;
/* unbake published declaration: published_a6b0a828f3fd8f6f47514456 */
typedef struct QueryObject QueryObject;

struct QueryWork;
/* unbake published declaration: published_e95da79a40ba0d74f99fb770 */
struct QueryWork {
        QueryBox box;
        short alignment[3];
        QueryResult *results[32];
        char callbackData[32];
        char callbackOutput[16];
        int count;
};

extern float func_80091108_us(void * arg0);
extern int func_8009189C_us(int arg0, void * arg1, void * arg2, void * arg3);
extern int func_80091D04(void *unused, int *out);
extern float func_80092408_us(void * arg0);
extern float func_8009249C_us(void * arg0);
#endif
