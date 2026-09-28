/* func_8011ECA4 -- dispatches a command code on one object: code 3 appends the argument to the
 * object's node list (tail at 0x40, head at 0x3C), code 4 and code 9 set status fields and forward
 * the literal code to the parent's handler at parent+0x8, code 1 replaces the parent pointer, and
 * anything else just forwards the code unchanged. The sh at 0x1A fixes that field as a halfword and
 * the sw stores fix 0x38/0x48 as words; the calls go through jalr, so the handler is a pointer.
 */
typedef struct Node {
    struct Node *next;
} Node;

typedef struct Obj {
    char pad0[0x8];
    void (*unk_8)(struct Obj *, int, void *);
} Obj;

typedef struct Owner {
    Obj *owner;
    char pad04[0x1A - 0x04];
    short unk_1A;
    char pad1C[0x38 - 0x1C];
    int unk_38;
    Node *head;
    Node *tail;
    char pad44[0x48 - 0x44];
    int unk_48;
} Owner;

int func_8011ECA4(Owner *self, int cmd, void *arg) {
    switch (cmd) {
    case 3:
        if (self->tail != 0) {
            self->tail->next = (Node *)arg;
        } else {
            self->head = (Node *)arg;
        }
        self->tail = (Node *)arg;
        break;
    case 4:
        self->unk_38 = 1;
        self->unk_48 = 0;
        self->unk_1A = 1;
        if (self->owner != 0) {
            self->owner->unk_8(self->owner, 4, arg);
        }
        break;
    case 9:
        self->unk_48 = 1;
        if (self->owner != 0) {
            self->owner->unk_8(self->owner, 9, arg);
        }
        break;
    case 1:
        self->owner = (Obj *)arg;
        break;
    default:
        if (self->owner != 0) {
            self->owner->unk_8(self->owner, cmd, arg);
        }
        break;
    }
    return 0;
}
