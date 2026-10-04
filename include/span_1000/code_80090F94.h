#ifndef UNBAKE_SPAN_1000_CODE_80090F94_H
#define UNBAKE_SPAN_1000_CODE_80090F94_H
#include "common/types.h"
struct QueryObject;
typedef struct QueryObject QueryObject;

struct QueryResult;
typedef struct QueryResult QueryResult;

struct QueryWork;
typedef struct QueryWork QueryWork;

struct QueryWork;
struct QueryWork {
        QueryBox box;
        short alignment[3];
        QueryResult *results[32];
        char callbackData[32];
        char callbackOutput[16];
        int count;
};
extern float func_80091108_us(void * arg0);
extern unsigned short func_800917C4(void * arg0, void * arg1);
extern int func_8009189C_us(int arg0, void * arg1, void * arg2, void * arg3);
extern float func_80092408_us(void * arg0);
extern float func_8009249C_us(void * arg0);
#endif
