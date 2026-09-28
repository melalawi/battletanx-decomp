/* Polls the status word, reports whether its 0x100 bit was set, and when the
   0x80 bit is also set folds that report into the object's flag word at 0x4
   and clears bit 1 there. Every field and local is touched with lw/sw, so all
   are words; nothing is live across the call inside a loop, so both locals
   sit in the frame. */
typedef struct Obj {
    char unk0[4];
    int flags;
} Obj;

extern int func_8011D180(void);

int func_8011D100(Obj *obj) {
    int status;
    int pressed;

    status = func_8011D180();
    if ((status & 0x100) != 0) {
        pressed = 1;
    } else {
        pressed = 0;
    }
    if ((status & 0x80) != 0) {
        obj->flags = obj->flags | pressed;
        obj->flags = obj->flags & ~2;
    }
    return pressed;
}
