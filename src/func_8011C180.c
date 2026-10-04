#include "span_1000/code_8011B830.h"
#include "types.h"

struct Shape_func_8011C150;
typedef struct Shape_func_8011C150 Shape_func_8011C150;



struct Shape_func_8011C150 {
    struct Shape_func_8011C150 *prev;
    struct Shape_func_8011C150 *next;
};

/* Links a node in ahead of a list node: the new node takes the list node's
 * predecessor as its own and becomes that predecessor's successor.
 * Both links are words, at 0x0 for the predecessor and 0x4 for the successor. The
 * predecessor is read twice because writing the new node's own 0x0 may alias it, which
 * is what the second lw of 0x0($a1) says. */



void func_8011C180(Shape_func_8011C150 *node, Shape_func_8011C150 *list) {
    node->prev = list->prev;
    node->next = list;
    if (list->prev != 0) {
        list->prev->next = node;
    }
    list->prev = node;
}
