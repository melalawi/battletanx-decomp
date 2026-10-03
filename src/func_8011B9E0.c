#include "shared/typemap.h"
#include "shared/func_8011b9e0.h"
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
