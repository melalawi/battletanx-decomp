#include "common/types_f8bfabebf96f.h"
#include "span_1000/code_8011B9E0.h"
#include "types.h"

struct Command;
typedef struct Command Command;
typedef struct Shape_func_8011B9E0_2 Shape_func_8011B9E0_2;

struct Shape_func_8011B9E0_2;





struct Command {
    short type;
    char unk2[0xE];
};
struct Shape_func_8011B9E0_2 {
    char unk0[0x48];
    struct Shape_func_8011B9E0 queue;
};

/* Builds a 16-byte command whose only set field is the 0x11 type code and
   hands it, with the queue at offset 0x48 of the owner, to the queue
   submitter. The sh fixed the type field as a short and the frame's 16-byte
   local slot fixed the command size. */






extern void func_8011B60C(struct Shape_func_8011B9E0 *queue, Command *command, int flag);

void func_8011B9E0(Shape_func_8011B9E0_2 *owner) {
    Command command;

    command.type = 0x11;
    func_8011B60C(&owner->queue, &command, 0);
}
