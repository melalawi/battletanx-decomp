/* Builds a 16-byte command whose only set field is the 0x11 type code and
   hands it, with the queue at offset 0x48 of the owner, to the queue
   submitter. The sh fixed the type field as a short and the frame's 16-byte
   local slot fixed the command size. */
typedef struct Command {
    short type;
    char unk2[0xE];
} Command;

typedef struct Queue {
    int unk0;
} Queue;

typedef struct Owner {
    char unk0[0x48];
    Queue queue;
} Owner;

extern void func_8011B60C(Queue *queue, Command *command, int flag);

void func_8011B9E0(Owner *owner) {
    Command command;

    command.type = 0x11;
    func_8011B60C(&owner->queue, &command, 0);
}
