#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "emalloc.h"

/**
 * @brief Dynamically allocates memory for a new node and initializes it with a given Route.
 *
 * @param route The Route to initialize the new node with.
 * @return node_t* Pointer to the newly allocated and initialized node.
 *
 */
node_t *new_node(Route route) {
    // Allocate memory for the new node
    node_t *temp = (node_t *)emalloc(sizeof(node_t));
    if (temp == NULL) {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // Initialize the new node with the provided route and set the next pointer to NULL
    temp->route = route;
    temp->next = NULL;
    return temp;
}

/**
 * @brief Adds a new node into the list in sorted order based on a specified field.
 *
 * @param list The head of the linked list.
 * @param new_node The new node to be added to the list.
 * @param field The field by which the list should be sorted ("airline_name", "to_airport_country", or "to_airport_name").
 * @return node_t* The head of the updated linked list.
 *
 */
node_t *add_inorder(node_t *list, node_t *new_node, char field[]) {
    node_t *prev = NULL;
    node_t *curr = list;

    // Determine which field to use for sorting
    if (strcmp(field, "airline_name") == 0) {
        // Traverse the list to find the correct position based on airline_name
        while (curr != NULL && strcmp(new_node->route.airline_name, curr->route.airline_name) > 0) {
            prev = curr;
            curr = curr->next;
        }
    } else if (strcmp(field, "to_airport_country") == 0) {
        // Traverse the list to find the correct position based on to_airport_country
        while (curr != NULL && strcmp(new_node->route.to_airport_country, curr->route.to_airport_country) > 0) {
            prev = curr;
            curr = curr->next;
        }
    } else if (strcmp(field, "to_airport_name") == 0) {
        // Traverse the list to find the correct position based on to_airport_name
        while (curr != NULL && strcmp(new_node->route.to_airport_name, curr->route.to_airport_name) > 0) {
            prev = curr;
            curr = curr->next;
        }
    }

    // Insert the new node into the list
    new_node->next = curr;

    // If the new node is to be the new head of the list
    if (prev == NULL) {
        return new_node;
    } else {
        // Otherwise, insert the new node after the previous node
        prev->next = new_node;
        return list;
    }
}