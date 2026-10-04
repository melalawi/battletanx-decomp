#include "span_1000/code_8011E3F0.h"
#include "types.h"

struct Shape_func_8011E3F0;
typedef struct Shape_func_8011E3F0 Shape_func_8011E3F0;



struct Shape_func_8011E3F0 {
    char unk0[0x14];
    int unk14;
    int unk18;
};

/* Registers a pair of callbacks for the object with kind 3, then clears the
   object's word at 0x14 and sets the one at 0x18 to 1. The two lui/addiu
   pairs on function symbols fixed arguments two and three as function
   pointers, and the sw pair fixed both fields as words. */


extern void func_80121434(void);
extern void func_80121400(void);
extern void func_8011F7F0(Shape_func_8011E3F0 *obj, void (*first)(void), void (*second)(void), int kind);

void func_8011E3F0(Shape_func_8011E3F0 *obj) {
    func_8011F7F0(obj, func_80121434, func_80121400, 3);
    obj->unk14 = 0;
    obj->unk18 = 1;
}
