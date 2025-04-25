#ifndef LIST_H
#define LIST_H

#include "route.h"

/**
 * @brief An struct that represents a node in the linked list.
 */
typedef struct node {
    Route route;
    struct node *next;
} node_t;

/**
 * Function protypes associated with a linked list.
 */
node_t *new_node(Route route);
node_t *add_inorder(node_t *list, node_t *new_node, char field[]);

#endif // LIST_H