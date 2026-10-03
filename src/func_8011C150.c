#include "shared/func_8011c150.h"
/* func_8011C150 -- unlinks one node from a doubly linked list, skipping either update when that
 * neighbour is absent. The two words the cartridge loads from the node are its previous and next
 * pointers, and each neighbour's opposite link is written back through the other.
 */


void func_8011C150(Shape_func_8011C150 *node) {
    if (node->prev != 0) {
        node->prev->next = node->next;
    }
    if (node->next != 0) {
        node->next->prev = node->prev;
    }
}
