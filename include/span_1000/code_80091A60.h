#ifndef UNBAKE_SPAN_1000_CODE_80091A60_H
#define UNBAKE_SPAN_1000_CODE_80091A60_H
#include "../types.h"
#include "common/types_d507c48987bb.h"
#include "types.h"
struct QueryObject;
/* unbake published declaration: published_ffda6f322a4231fed9aa2c1c */
union InterpVertex;
typedef union InterpVertex InterpVertex;

union InterpVertex {
    struct {
        s16 position[3];
        u16 flag;
        s16 texture[2];
        u8 color[4];
    } v;
    u64 force_structure_alignment;
};
struct QueryObject { char prefix[0x18]; int index; };

struct QueryObject;
struct QueryResult;
/* unbake published declaration: published_03ae61c8f4341395548337e8 */
typedef void ( *QueryCallback)(struct QueryResult *, struct QueryObject *, int, void *, void *);

struct QueryWork;
/* unbake published declaration: published_1c2d79c8c1aa035409008f65 */
typedef struct QueryWork QueryWork;

struct QueryResult;
/* unbake published declaration: published_4de71db0263339d0bea590ce */
typedef struct QueryResult QueryResult;

struct QueryRecord;
/* unbake published declaration: published_4f3b6ae5c25773f639fa08cb */
typedef struct QueryRecord QueryRecord;

struct QueryDispatch;
/* unbake published declaration: published_57be063eb00b2fe00782e2da */
struct QueryDispatch { QueryCallback callback; int tail[2]; };

/* unbake published declaration: published_5b62b1e82ac51e0306fdd229 */
extern void func_80093F34(void);

struct QueryRecord;
/* unbake published declaration: published_6583957d4c24afbee3ec6e52 */
struct QueryRecord { QueryBox box; char tail[22]; };

struct QueryObject;
/* unbake published declaration: published_a6b0a828f3fd8f6f47514456 */
typedef struct QueryObject QueryObject;

/* unbake published declaration: published_c0b8d1b6f711ea1386b92d5f */
extern QueryRecord D_803B8254[];

struct QueryDispatch;
/* unbake published declaration: published_d0cd53c1949f9999497577f1 */
typedef struct QueryDispatch QueryDispatch;

/* unbake published declaration: published_e29eea54071038c5e99d17b8 */
extern QueryDispatch D_802C3804[];

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

/* unbake published declaration: published_f153a908d36d0e89b3e7bfdc */
extern int func_80091D04(void *unused, int *out);

/* unbake published declaration: published_f8d579c0439535dd5850948f */
extern float D_80071EA0;

extern void func_80093D30_us();
extern int func_80093EF8_us(void * arg0, void * arg1);


#endif
