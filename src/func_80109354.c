#include "span_1000/code_8010698C.h"
#include "types.h"

struct Record;
typedef struct Record Record;



struct Record {
    short unk0;
    short unk2;
    short unk4;
    char unk6[0xA];
    short unk10;
};

/* Stores three halfwords into the record at offsets 2, 4 and 0x10. All three
   stores are sh with no narrowing of the incoming registers, which fixed the
   fields as shorts and the arguments as plain words. */


void func_80109354(Record *record, int a, int b, int c) {
    record->unk2 = a;
    record->unk4 = b;
    record->unk10 = c;
}
