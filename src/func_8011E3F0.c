/* Registers a pair of callbacks for the object with kind 3, then clears the
   object's word at 0x14 and sets the one at 0x18 to 1. The two lui/addiu
   pairs on function symbols fixed arguments two and three as function
   pointers, and the sw pair fixed both fields as words. */
typedef struct Obj {
    char unk0[0x14];
    int unk14;
    int unk18;
} Obj;

extern void func_80121434(void);
extern void func_80121400(void);
extern void func_8011F7F0(Obj *obj, void (*first)(void), void (*second)(void), int kind);

void func_8011E3F0(Obj *obj) {
    func_8011F7F0(obj, func_80121434, func_80121400, 3);
    obj->unk14 = 0;
    obj->unk18 = 1;
}
