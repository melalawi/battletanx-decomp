/* Returns the word at offset 0x28 of the 48-byte slot the owner's current
   index names. The index scaled by 48 fixed the slot size, and the addu with
   the scaled offset as its first operand fixed the access as offset-plus-base
   pointer arithmetic. */
typedef struct Slot {
    char unk0[0x28];
    int unk28;
    char unk2C[4];
} Slot;

typedef struct Owner {
    char unk0[0x3C];
    int current;
    Slot *slots;
} Owner;

int func_8011C300(Owner *owner) {
    Slot *slots;

    slots = owner->slots;
    return ((Slot *)(owner->current * sizeof(Slot) + (char *)slots))->unk28;
}
