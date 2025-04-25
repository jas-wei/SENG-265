#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "count_list.h"

/**
 * @brief Dynamically allocates memory for a new q1_count_node and initializes it with a given Q1_count.
 *
 * @param q1_count The Q1_count to initialize the new node with.
 * @return q1_count_node* Pointer to the newly allocated and initialized node.
 */
q1_count_node *q1_count_new_node(Q1_count q1_count) {
    // Dynamically allocate memory for a new node
    q1_count_node *temp = (q1_count_node *)malloc(sizeof(q1_count_node));
    if (temp == NULL) {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    // Initialize the new node with the provided Q1_count
    temp->q1_count = q1_count;
    temp->next = NULL;
    temp->freed = 0; // Initialize the flag
    
    return temp;
}

/**
 * @brief Adds a new q1_count_node into the list in sorted order based on a specified field.
 *
 * @param list The head of the linked list.
 * @param new_node The new node to be added to the list.
 * @param field The field by which the list should be sorted ("airline_name").
 * @return q1_count_node* The head of the updated linked list.
 */
q1_count_node *q1_count_add_inorder(q1_count_node *list, q1_count_node *new_node, char field[]) {
    q1_count_node *prev = NULL;
    q1_count_node *curr = list;

    // Traverse the list to find the correct position based on airline_name
    while (curr != NULL && strcmp(new_node->q1_count.airline_name, curr->q1_count.airline_name) > 0) {
        prev = curr;
        curr = curr->next;
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

/**
 * @brief Dynamically allocates memory for a new q2_count_node and initializes it with a given Q2_count.
 *
 * @param q2_count The Q2_count to initialize the new node with.
 * @return q2_count_node* Pointer to the newly allocated and initialized node.
 */
q2_count_node *q2_count_new_node(Q2_count q2_count) {
    // Dynamically allocate memory for a new node
    q2_count_node *temp = (q2_count_node *)malloc(sizeof(q2_count_node));
    if (temp == NULL) {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    // Initialize the new node with the provided Q2_count
    temp->q2_count = q2_count;
    temp->next = NULL;
    temp->freed = 0; // Initialize the flag
    
    return temp;
}

/**
 * @brief Adds a new q2_count_node into the list in sorted order based on a specified field.
 *
 * @param list The head of the linked list.
 * @param new_node The new node to be added to the list.
 * @param field The field by which the list should be sorted ("to_airport_country").
 * @return q2_count_node* The head of the updated linked list.
 */
q2_count_node *q2_count_add_inorder(q2_count_node *list, q2_count_node *new_node, char field[]) {
    q2_count_node *prev = NULL;
    q2_count_node *curr = list;

    // Traverse the list to find the correct position based on to_airport_country
    while (curr != NULL && strcmp(new_node->q2_count.to_airport_country, curr->q2_count.to_airport_country) > 0) {
        prev = curr;
        curr = curr->next;
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

/**
 * @brief Dynamically allocates memory for a new q3_count_node and initializes it with a given Q3_count.
 *
 * @param q3_count The Q3_count to initialize the new node with.
 * @return q3_count_node* Pointer to the newly allocated and initialized node.
 */
q3_count_node *q3_count_new_node(Q3_count q3_count) {
    // Dynamically allocate memory for a new node
    q3_count_node *temp = (q3_count_node *)malloc(sizeof(q3_count_node));
    if (temp == NULL) {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    // Initialize the new node with the provided Q3_count
    temp->q3_count = q3_count;
    temp->next = NULL;
    temp->freed = 0; // Initialize the flag
    
    return temp;
}

/**
 * @brief Adds a new q3_count_node into the list in sorted order based on a specified field.
 *
 * @param list The head of the linked list.
 * @param new_node The new node to be added to the list.
 * @param field The field by which the list should be sorted ("to_airport_country").
 * @return q3_count_node* The head of the updated linked list.
 */
q3_count_node *q3_count_add_inorder(q3_count_node *list, q3_count_node *new_node, char field[]) {
    q3_count_node *prev = NULL;
    q3_count_node *curr = list;

    // Traverse the list to find the correct position based on to_airport_country
    while (curr != NULL && strcmp(new_node->q3_count.to_airport_country, curr->q3_count.to_airport_country) > 0) {
        prev = curr;
        curr = curr->next;
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