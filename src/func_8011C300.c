#include "shared/func_8011c300.h"
/* Returns the word at offset 0x28 of the 48-byte slot the owner's current
   index names. The index scaled by 48 fixed the slot size, and the addu with
   the scaled offset as its first operand fixed the access as offset-plus-base
   pointer arithmetic. */




int func_8011C300(Shape_func_8011C300 *owner) {
    Slot *slots;

    slots = owner->slots;
    return ((Slot *)(owner->current * sizeof(Slot) + (char *)slots))->unk28;
}
