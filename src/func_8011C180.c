/* Links a node in ahead of a list node: the new node takes the list node's
 * predecessor as its own and becomes that predecessor's successor.
 * Both links are words, at 0x0 for the predecessor and 0x4 for the successor. The
 * predecessor is read twice because writing the new node's own 0x0 may alias it, which
 * is what the second lw of 0x0($a1) says. */

typedef struct Node {
    struct Node *prev;
    struct Node *next;
} Node;

void func_8011C180(Node *node, Node *list) {
    node->prev = list->prev;
    node->next = list;
    if (list->prev != 0) {
        list->prev->next = node;
    }
    list->prev = node;
}
