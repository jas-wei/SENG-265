#ifndef COUNT_LIST_H
#define COUNT_LIST_H

#include "count.h"

/**
 * @brief Struct representing a node in the linked list for Q1_count
 */
typedef struct q1_count_node {
    Q1_count q1_count;               // Data for Q1_count
    struct q1_count_node *next;
    int freed;                       // Flag to indicate if the node has been freed
} q1_count_node;

/**
 * @brief Struct representing a node in the linked list for Q2_count
 */
typedef struct q2_count_node {
    Q2_count q2_count;               // Data for Q2_count
    struct q2_count_node *next;
    int freed;                       // Flag to indicate if the node has been freed
} q2_count_node;

/**
 * @brief Struct representing a node in the linked list for Q3_count
 */ 
typedef struct q3_count_node {
    Q3_count q3_count;               // Data for Q3_count
    struct q3_count_node *next;  
    int freed;                       // Flag to indicate if the node has been freed
} q3_count_node;

/**
 * Function protypes associated with a linked list.
 */
q1_count_node *q1_count_new_node(Q1_count q1_count);
q1_count_node *q1_count_add_inorder(q1_count_node *list, q1_count_node *new_node, char field[]);

q2_count_node *q2_count_new_node(Q2_count q2_count);
q2_count_node *q2_count_add_inorder(q2_count_node *list, q2_count_node *new_node, char field[]);

q3_count_node *q3_count_new_node(Q3_count q3_count);
q3_count_node *q3_count_add_inorder(q3_count_node *list, q3_count_node *new_node, char field[]);

#endif // COUNT_LIST_H