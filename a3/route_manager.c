/** @file route_manager.c
 *  @brief A small program to analyze airline routes data.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Jasmine Wei
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "list.h"
#include "count_list.h"

#define MAX_LINE_LEN 80
#define MAX_ROUTES 100
#define BUFFER_SIZE 256

/**
 * @brief this function parses command-line arguments
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @param data_file The yaml file of airline routes were looking through
 * @param question The question number
 * @param n The number of items we are outputting
 * @return void: nothing
 *
 */
void parse_arguments(int argc, char *argv[], char *data_file, int *question, int *n) {
    // Loop through each argument
    for (int i = 1; i < argc; i++) {
        // Check if the argument starts with --DATA=
        if (strncmp(argv[i], "--DATA=", 7) == 0) {
            // Copy the value after --DATA= into data_file
            strcpy(data_file, argv[i] + 7);
        }
        // Check if the argument starts with --QUESTION=
        else if (strncmp(argv[i], "--QUESTION=", 11) == 0) {
            // Convert the value after --QUESTION= to an integer and store in question
            *question = atoi(argv[i] + 11);
        }
        // Check if the argument starts with --N=
        else if (strncmp(argv[i], "--N=", 4) == 0) {
            // Convert the value after --N= to an integer and store in n
            *n = atoi(argv[i] + 4);
        }
    }
}

/**
 * @brief this function trims leading whitespace
 * @param str the string to trim
 * @return char *: the trimmed string
 *
 */
char *trim_leading_spaces(char *str) {
    while (*str == ' ') str++;
    return str;
}

/**
 * @brief this function parses each line of the yaml file, assigning variables to respective fields
 *
 * @param line the current line of the yaml file for tokenization
 * @param route route struct instance used to fill its feilds
 * @return void: nothing
 *
 */
void parse_line(char *line, Route *route) {
   // Tokenize the input line to get the key
    char *key = strtok(line, ":");

    // Tokenize again to get the value
    char *value = strtok(NULL, ":");

    // Check if both key and value are not NULL
    if (key && value) {
        // Trim leading spaces from key and value
        key = trim_leading_spaces(key);
        value = trim_leading_spaces(value);

        // Remove newline character from value if present
        value[strcspn(value, "\n")] = '\0';

        // Compare key and copy the value to the corresponding field in the Route structure
        if (strcmp(key, "- airline_name") == 0) {
            strncpy(route->airline_name, value, sizeof(route->airline_name) - 1);
        } else if (strcmp(key, "airline_icao_unique_code") == 0) {
            strncpy(route->airline_icao_unique_code, value, sizeof(route->airline_icao_unique_code) - 1);
        } else if (strcmp(key, "airline_country") == 0) {
            strncpy(route->airline_country, value, sizeof(route->airline_country) - 1);
        } else if (strcmp(key, "from_airport_name") == 0) {
            strncpy(route->from_airport_name, value, sizeof(route->from_airport_name) - 1);
        } else if (strcmp(key, "from_airport_city") == 0) {
            strncpy(route->from_airport_city, value, sizeof(route->from_airport_city) - 1);
        } else if (strcmp(key, "from_airport_country") == 0) {
            strncpy(route->from_airport_country, value, sizeof(route->from_airport_country) - 1);
        } else if (strcmp(key, "from_airport_icao_unique_code") == 0) {
            strncpy(route->from_airport_icao_unique_code, value, sizeof(route->from_airport_icao_unique_code) - 1);
        } else if (strcmp(key, "from_airport_altitude") == 0) {
            strncpy(route->from_airport_altitude, value, sizeof(route->from_airport_altitude) - 1);
        } else if (strcmp(key, "to_airport_name") == 0) {
            strncpy(route->to_airport_name, value, sizeof(route->to_airport_name) - 1);
        } else if (strcmp(key, "to_airport_city") == 0) {
            strncpy(route->to_airport_city, value, sizeof(route->to_airport_city) - 1);
        } else if (strcmp(key, "to_airport_country") == 0) {
            strncpy(route->to_airport_country, value, sizeof(route->to_airport_country) - 1);
        } else if (strcmp(key, "to_airport_icao_unique_code") == 0) {
            strncpy(route->to_airport_icao_unique_code, value, sizeof(route->to_airport_icao_unique_code) - 1);
        } else if (strcmp(key, "to_airport_altitude") == 0) {
            strncpy(route->to_airport_altitude, value, sizeof(route->to_airport_altitude) - 1);
        }
    }
}

/**
 * @brief this function adds all of each route struct node into the general linked list in order,
 *        with costraints defined by question number
 *
 * @param new_node the node to be added into the general linked list
 * @param head_ref the begining of the general linked list of route structs
 * @param question the question number that is being answered
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int question_add_node(node_t *new_node, node_t **head_ref, int question){
    if ((question == 1) && (strcmp(new_node->route.to_airport_country, "Canada") == 0)) {
        *head_ref = add_inorder(*head_ref, new_node, "airline_name");
    } else if (question == 2){
        if (new_node->route.to_airport_country[0] == '\'') {
            // Calculate the length of the original string
            size_t len = strlen(new_node->route.to_airport_country);

            // Allocate memory for the new string
            char *new_country = (char *)malloc(len - 2); // Allocate memory for the new string

            // Copy the string without the first two and last characters
            strncpy(new_country, new_node->route.to_airport_country + 2, len - 3);
            new_country[len - 3] = '\0'; // Ensure the new string is null-terminated

            // Assign the new string to the node's route.to_airport_country
            strcpy(new_node->route.to_airport_country, new_country);

            // Free the allocated memory
            free(new_country);
        }
        *head_ref = add_inorder(*head_ref, new_node, "to_airport_country");
    } else if (question == 3){
        *head_ref = add_inorder(*head_ref, new_node, "to_airport_name");
    }
    return 1;
}

/**
 * @brief this function reads the yaml file containing routes of airplanes, and compiles them all into a general linked list
 *        of route structs
 *
 * @param data_file the yaml file containing routes of airplanes
 * @param head_ref the begining of the general linked list of route structs
 * @param question the question number that is being answered
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int read_yaml(const char *data_file, node_t **head_ref, int question) {
    // File pointer
    FILE *file;
    char line[256];
    Route new_route;
    int is_first_line = 1; // Flag to check if it's the first line

    // Open the file in read mode
    file = fopen(data_file, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        return 1;
    }

    // Initialize the new Route instance with empty strings
    memset(&new_route, 0, sizeof(Route));

    // Read each line from the file and parse it
    while (fgets(line, sizeof(line), file)) {
        if (is_first_line) {
            // Skip the first line (header or initial content)
            is_first_line = 0;
        } else if (strstr(line, "- airline_name") != NULL) {
            // If a new route begins, add the previous one to the list
            node_t *new_node = (node_t *)malloc(sizeof(node_t));
            new_node->route = new_route;
            new_node->next = NULL;

            // Add the new node to the list based on the question parameter
            question_add_node(new_node, head_ref, question);

            // Reset the Route instance for the new route
            memset(&new_route, 0, sizeof(Route));
        }
        // Parse the line into the current route
        parse_line(line, &new_route);
    }

    // Add the last route to the list
    node_t *new_node = (node_t *)emalloc(sizeof(node_t));
    new_node->route = new_route;
    new_node->next = NULL;

    // Add the new node to the list based on the question parameter
    question_add_node(new_node, head_ref, question);

    // Close the file
    fclose(file);
    return 0;
}

/**
 * @brief this function answers and outputs the contents of the linked list containing vals to be outputted
 *        in a formatted manner
 *
 * @param head the begining of the linked list containing vals to be outputted
 * @param n the number of elements that will be outputted
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int q1_output_vals(q1_count_node *head, int n) {
    // Open the file "output.csv" for writing
    FILE *file = fopen("output.csv", "w");
    if (file == NULL) {
        fprintf(stderr, "Could not open file for writing\n");
        return 1;
    }

    // Write the CSV header
    fputs("subject,statistic\n", file);
    
    for (int i = 0; i < n; i++) {
        // If the list is empty, break out of the loop
        if (head == NULL) {
            break;
        }

        // Initialize pointers to find the node with the maximum count
        q1_count_node *prev_temp = NULL;
        q1_count_node *temp = head;
        q1_count_node *max_count = temp;
        q1_count_node *max_count_prev = NULL;

        // Traverse the list to find the node with the maximum count
        while (temp != NULL) {
            if (temp->q1_count.count > max_count->q1_count.count) {
                max_count_prev = prev_temp;
                max_count = temp;
            }
            prev_temp = temp;
            temp = temp->next;
        }

        // Print the max_count node details to the file
        if (max_count != NULL) {
            fprintf(file, "%s (%s),%d\n", max_count->q1_count.airline_name, max_count->q1_count.airline_icao_unique_code,
                                          max_count->q1_count.count);
                                          
            // Remove the max_count node from the linked list
            if (max_count_prev == NULL) {
                // If max_count is the head of the list
                head = max_count->next;
            } else {
                // If max_count is not the head of the list
                max_count_prev->next = max_count->next;
            }
            
            // Set the freed flag
            max_count->freed = 1;
        } else {
            // No nodes left in the list to process
            break;
        }
    }

    // Close the file
    fclose(file);
    return 0;
}

/**
 * @brief this function intializes the fields of a node for the linked list with values to be outputted
 *
 * @param new_q1_count_node the pointer to the current node of the linked list with values to be outputted
 * @param temp the pointer to the current node of general route linked list
 * @return void: nothing
 *
 */
void init_q1_count_fields(q1_count_node *new_q1_count_node, node_t *temp) {
    // Copy the airline name from the route to the q1_count field
    strncpy(new_q1_count_node->q1_count.airline_name, temp->route.airline_name, sizeof(new_q1_count_node->q1_count.airline_name) - 1);
    new_q1_count_node->q1_count.airline_name[sizeof(new_q1_count_node->q1_count.airline_name) - 1] = '\0'; // Ensure null termination

    // Copy the airline ICAO unique code from the route to the q1_count field
    strncpy(new_q1_count_node->q1_count.airline_icao_unique_code, temp->route.airline_icao_unique_code, sizeof(new_q1_count_node->q1_count.airline_icao_unique_code) - 1);
    new_q1_count_node->q1_count.airline_icao_unique_code[sizeof(new_q1_count_node->q1_count.airline_icao_unique_code) - 1] = '\0'; // Ensure null termination

    // Initialize the count field to 1
    new_q1_count_node->q1_count.count = 1;
}

/**
 * @brief this function creates the linked list with nodes to be outputted into output.csv 
 *        from the gneeral linked list of routes, and outputs formatted information
 *
 * @param temp the pointer to the current node of general route linked list
 * @param curr_to_airport_name the number of elements that will be outputted
 * @param count_head the pointer to the current node of linked list with information to be outputted into file specific to q3
 * @return void: nothing
 *
 */
void make_q1_count_list(node_t *temp, char curr_airline_name[], q1_count_node *count_head) {
    // Traverse the list of routes
    while (temp != NULL) {
        // Check if the current airline name is different from the last one processed
        if (strcmp(temp->route.airline_name, curr_airline_name) != 0) {
            // Update the current airline name
            strcpy(curr_airline_name, temp->route.airline_name);
            
            // Create a new Q1_count and corresponding q1_count_node
            Q1_count new_q1_count;
            q1_count_node *new_q1_count_node = q1_count_new_node(new_q1_count); // Declare as a pointer

            // Initialize the fields of the new q1_count_node
            init_q1_count_fields(new_q1_count_node, temp);

            // Add the new node to the linked list in order
            count_head = q1_count_add_inorder(count_head, new_q1_count_node, "airline_name");
        } else {
            // If the airline name is the same, find the corresponding count node and increment the count
            q1_count_node *count_cur = count_head;
            while (count_cur != NULL && strcmp(count_cur->q1_count.airline_name, temp->route.airline_name) != 0) {
                count_cur = count_cur->next;
            }

            // If the count node is found, increment the count
            if (count_cur != NULL) {
                count_cur->q1_count.count++;
            } else {
                // Error handling if the count node is not found
                fprintf(stderr, "Error: Could not find the count node for airline %s\n", temp->route.airline_name);
            }
        }
        // Move to the next node in the list
        temp = temp->next;
    }
}

/**
 * @brief this function answers q1: What are the top N airlines that offer the greatest number of routes with destination country as Canada?  
 *        it reads the routes of the provided yaml file, compiles them into a general sorted linked list,
 *        compiles that into a linked list with nodes to be outputted into output.csv, and outputs formatted information
 *
 * @param data_file the yaml file full of airline route information
 * @param n the number of elements that will be outputted
 * @return void: nothing
 *
 */
void q1(char data_file[], int n) { 
    node_t *head = NULL;
    //read the yaml fil
    read_yaml(data_file, &head, 1);
    node_t *temp = head;

    char curr_airline_name[BUFFER_SIZE];
    strcpy(curr_airline_name, "");// Use strcpy to copy the string

    if (temp != NULL) {
        strcpy(curr_airline_name, temp->route.airline_name);
    }

    // Init head pointer and node
    q1_count_node *count_head = NULL;
    Q1_count new_q1_count;
    q1_count_node *new_q1_count_node = q1_count_new_node(new_q1_count); // Make new count node. Declare as a pointer
    
    // Init count node's fields
    init_q1_count_fields(new_q1_count_node, temp);

    // Make this new node the head
    count_head = new_q1_count_node;
    temp = temp->next;

    make_q1_count_list(temp, curr_airline_name, count_head);

    // Print the count linked list
    q1_count_node *count_temp = count_head;
    q1_output_vals(count_temp, n);
    
    // Free the allocated memory for the original list
    while (head != NULL) {
        node_t *temp = head;
        head = head->next;
        free(temp);
    }

    // Free the allocated memory for the count list only if not already freed
    q1_count_node *cur = count_head;
    while (cur != NULL) {
        q1_count_node *next = cur->next;
        if (!cur->freed) {
            free(cur);
        }
        cur = next;
    }
}

/**
 * @brief this function answers and outputs the contents of the linked list containing vals to be outputted
 *        in a formatted manner
 *
 * @param head the begining of the linked list containing vals to be outputted
 * @param n the number of elements that will be outputted
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int q2_output_vals(q2_count_node *head, int n) {
    // Open the file "output.csv" for writing
    FILE *file = fopen("output.csv", "w");
    if (file == NULL) {
        fprintf(stderr, "Could not open file for writing\n");
        return 1;
    }

    // Write the CSV header
    fputs("subject,statistic\n", file);
    
    for (int i = 0; i < n; i++) {
        // If the list is empty, break out of the loop
        if (head == NULL) {
            break;
        }

        // Initialize pointers to find the node with the minimum count
        q2_count_node *prev_temp = NULL;
        q2_count_node *temp = head;
        q2_count_node *min_count = temp;
        q2_count_node *min_count_prev = NULL;

        // Traverse the list to find the node with the minimum count
        while (temp != NULL) {
            if (temp->q2_count.count < min_count->q2_count.count) {
                min_count_prev = prev_temp;
                min_count = temp;
            }
            prev_temp = temp;
            temp = temp->next;
        }

        // Print the min_count node details to the file
        if (min_count != NULL) {
            fprintf(file, "%s,%d\n", min_count->q2_count.to_airport_country, min_count->q2_count.count);

            // Remove the min_count node from the linked list
            if (min_count_prev == NULL) {
                // If min_count is the head of the list
                head = min_count->next;
            } else {
                // If min_count is not the head of the list
                min_count_prev->next = min_count->next;
            }
            // Set the freed flag
            min_count->freed = 1;
        } else {
            // No nodes left in the list to process
            break;
        }
    }

    // Close the file
    fclose(file);
    return 0;
}

/**
 * @brief This function initializes the fields of a node for the linked list with values to be outputted.
 *
 * @param new_q2_count_node The pointer to the current node of the linked list with values to be outputted.
 * @param temp The pointer to the current node of the general route linked list.
 * @return void: nothing.
 *
 */
void init_q2_count_fields(q2_count_node *new_q2_count_node, node_t *temp) {
    // Copy the destination country from the route to the q2_count field
    strncpy(new_q2_count_node->q2_count.to_airport_country, temp->route.to_airport_country, sizeof(new_q2_count_node->q2_count.to_airport_country) - 1);
    new_q2_count_node->q2_count.to_airport_country[sizeof(new_q2_count_node->q2_count.to_airport_country) - 1] = '\0'; // Ensure null termination

    // Initialize the count field to 1
    new_q2_count_node->q2_count.count = 1;
}

/**
 * @brief This function creates the linked list with nodes to be outputted into output.csv
 *        from the general linked list of routes, and outputs formatted information.
 *
 * @param temp The pointer to the current node of the general route linked list.
 * @param curr_to_airport_country The current country being processed.
 * @param count_head The pointer to the head of the linked list with information to be outputted into the file specific to q2.
 * @return void: nothing.
 *
 */
void make_q2_count_list(node_t *temp, char curr_to_airport_country[], q2_count_node *count_head) {
    // Traverse the list of routes
    while (temp != NULL) {
        // Check if the current destination country is different from the last one processed
        if (strcmp(temp->route.to_airport_country, curr_to_airport_country) != 0) {
            // Update the current destination country
            strcpy(curr_to_airport_country, temp->route.to_airport_country);
            
            // Create a new Q2_count and corresponding q2_count_node
            Q2_count new_q2_count;
            q2_count_node *new_q2_count_node = q2_count_new_node(new_q2_count); // Declare as a pointer
            
            // Initialize the fields of the new q2_count_node
            init_q2_count_fields(new_q2_count_node, temp);

            // Add the new node to the linked list in order
            count_head = q2_count_add_inorder(count_head, new_q2_count_node, "to_airport_country");
        } else {
            // If the destination country is the same, find the corresponding count node and increment the count
            q2_count_node *count_cur = count_head;
            while (count_cur != NULL && strcmp(count_cur->q2_count.to_airport_country, temp->route.to_airport_country) != 0) {
                count_cur = count_cur->next;
            }

            // If the count node is found, increment the count
            if (count_cur != NULL) {
                count_cur->q2_count.count++;
            } else {
                // Error handling if the count node is not found
                fprintf(stderr, "Error: Could not find the count node for country %s\n", temp->route.to_airport_country);
            }
        }
        // Move to the next node in the list
        temp = temp->next;
    }
}

/**
 * @brief This function answers q2: What are the top N countries with the least appearances as destination countries on the routes data?
 *        It reads the routes from the provided YAML file, compiles them into a general sorted linked list,
 *        compiles that into a linked list with nodes to be outputted into output.csv, and outputs formatted information.
 *
 * @param data_file The YAML file full of airline route information.
 * @param n The number of elements that will be outputted.
 * @return void: nothing.
 *
 */
void q2(char data_file[], int n) {
    node_t *head = NULL;
    //read the yaml fil
    read_yaml(data_file, &head, 2);
    node_t *temp = head->next;

    char curr_to_airport_country[BUFFER_SIZE];
    strcpy(curr_to_airport_country, ""); // Use strcpy to copy the string

    if (temp != NULL) {
        strcpy(curr_to_airport_country, temp->route.to_airport_country);
    }

    // Initialize head pointer and node
    q2_count_node *count_head = NULL;
    Q2_count new_q2_count;
    q2_count_node *new_q2_count_node = q2_count_new_node(new_q2_count); // Make new count node. Declare as a pointer
    
    // Initialize count node's fields
    init_q2_count_fields(new_q2_count_node, temp);

    // Make this new node the head
    count_head = new_q2_count_node;
    temp = temp->next;

    // Create the count list
    make_q2_count_list(temp, curr_to_airport_country, count_head);

    // Print the count linked list
    q2_count_node *count_temp = count_head;
    q2_output_vals(count_temp, n);

    // Free the allocated memory for the original list
    while (head != NULL) {
        node_t *temp = head;
        head = head->next;
        free(temp);
    }

    // Free the allocated memory for the count list only if not already freed
    q2_count_node *cur = count_head;
    while (cur != NULL) {
        q2_count_node *next = cur->next;
        if (!cur->freed) {
            free(cur);
        }
        cur = next;
    }
}

/**
 * @brief This function answers and outputs the contents of the linked list containing values to be outputted
 *        in a formatted manner.
 *
 * @param head The beginning of the linked list containing values to be outputted.
 * @param n The number of elements that will be outputted.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int q3_output_vals(q3_count_node *head, int n) {
    // Open the file "output.csv" for writing
    FILE *file = fopen("output.csv", "w");
    if (file == NULL) {
        fprintf(stderr, "Could not open file for writing\n");
        return 1;
    }

    // Write the CSV header
    fputs("subject,statistic\n", file);
    
    for (int i = 0; i < n; i++) {
        // If the list is empty, break out of the loop
        if (head == NULL) {
            break;
        }

        // Initialize pointers to find the node with the maximum count
        q3_count_node *prev_temp = NULL;
        q3_count_node *temp = head;
        q3_count_node *max_count = temp;
        q3_count_node *max_count_prev = NULL;

        // Traverse the list to find the node with the maximum count
        while (temp != NULL) {
            if (temp->q3_count.count > max_count->q3_count.count) {
                max_count_prev = prev_temp;
                max_count = temp;
            }
            prev_temp = temp;
            temp = temp->next;
        }

        // Print the max_count node details to the file
        if (max_count != NULL) {
            fprintf(file, "\"%s (%s), %s, %s\",%d\n", max_count->q3_count.to_airport_name, max_count->q3_count.to_airport_icao_unique_code, 
                                                      max_count->q3_count.to_airport_city, max_count->q3_count.to_airport_country, max_count->q3_count.count);

            // Remove the max_count node from the linked list
            if (max_count_prev == NULL) {
                // If max_count is the head of the list
                head = max_count->next;
            } else {
                // If max_count is not the head of the list
                max_count_prev->next = max_count->next;
            }

            // Set the freed flag
            max_count->freed = 1;
        } else {
            // No nodes left in the list to process
            break;
        }
    }

    // Close the file
    fclose(file);
    return 0;
}

/**
 * @brief This function initializes the fields of a node for the linked list with values to be outputted.
 *
 * @param new_q3_count_node The pointer to the current node of the linked list with values to be outputted.
 * @param temp The pointer to the current node of the general route linked list.
 * @return void: nothing.
 *
 */
void init_q3_count_fields(q3_count_node *new_q3_count_node, node_t *temp) {
    // Copy the destination airport name from the route to the q3_count field
    strncpy(new_q3_count_node->q3_count.to_airport_name, temp->route.to_airport_name, sizeof(new_q3_count_node->q3_count.to_airport_name) - 1);
    new_q3_count_node->q3_count.to_airport_name[sizeof(new_q3_count_node->q3_count.to_airport_name) - 1] = '\0'; // Ensure null termination

    // Copy the destination airport ICAO unique code from the route to the q3_count field
    strncpy(new_q3_count_node->q3_count.to_airport_icao_unique_code, temp->route.to_airport_icao_unique_code, sizeof(new_q3_count_node->q3_count.to_airport_icao_unique_code) - 1);
    new_q3_count_node->q3_count.to_airport_icao_unique_code[sizeof(new_q3_count_node->q3_count.to_airport_icao_unique_code) - 1] = '\0'; // Ensure null termination

    // Copy the destination airport city from the route to the q3_count field
    strncpy(new_q3_count_node->q3_count.to_airport_city, temp->route.to_airport_city, sizeof(new_q3_count_node->q3_count.to_airport_city) - 1);
    new_q3_count_node->q3_count.to_airport_city[sizeof(new_q3_count_node->q3_count.to_airport_city) - 1] = '\0'; // Ensure null termination

    // Copy the destination airport country from the route to the q3_count field
    strncpy(new_q3_count_node->q3_count.to_airport_country, temp->route.to_airport_country, sizeof(new_q3_count_node->q3_count.to_airport_country) - 1);
    new_q3_count_node->q3_count.to_airport_country[sizeof(new_q3_count_node->q3_count.to_airport_country) - 1] = '\0'; // Ensure null termination

    // Initialize the count field to 1
    new_q3_count_node->q3_count.count = 1;
}

/**
 * @brief This function creates the linked list with nodes to be outputted into output.csv
 *        from the general linked list of routes, and outputs formatted information.
 *
 * @param temp The pointer to the current node of the general route linked list.
 * @param curr_to_airport_name The current destination airport being processed.
 * @param count_head The pointer to the head of the linked list with information to be outputted into the file specific to q3.
 * @return void: nothing.
 *
 */
void make_q3_count_list(node_t *temp, char curr_to_airport_name[], q3_count_node *count_head) {
    // Traverse the list of routes
    while (temp != NULL) {
        // Check if the current destination airport is different from the last one processed
        if (strcmp(temp->route.to_airport_name, curr_to_airport_name) != 0) {
            // Update the current destination airport
            strcpy(curr_to_airport_name, temp->route.to_airport_name);
            
            // Create a new Q3_count and corresponding q3_count_node
            Q3_count new_q3_count;
            q3_count_node *new_q3_count_node = q3_count_new_node(new_q3_count); // Declare as a pointer

            // Initialize the fields of the new q3_count_node
            init_q3_count_fields(new_q3_count_node, temp);

            // Add the new node to the linked list in order
            count_head = q3_count_add_inorder(count_head, new_q3_count_node, "to_airport_name");
        } else {
            // If the destination airport is the same, find the corresponding count node and increment the count
            q3_count_node *count_cur = count_head;
            while (count_cur != NULL && strcmp(count_cur->q3_count.to_airport_name, temp->route.to_airport_name) != 0) {
                count_cur = count_cur->next;
            }

            // If the count node is found, increment the count
            if (count_cur != NULL) {
                count_cur->q3_count.count++;
            } else {
                // Error handling if the count node is not found
                fprintf(stderr, "Error: Could not find the count node for airport %s\n", temp->route.to_airport_name);
            }
        }
        // Move to the next node in the list
        temp = temp->next;
    }
}

/**
 * @brief This function answers q3: What are the top N destination airports?
 *        It reads the routes from the provided YAML file, compiles them into a general sorted linked list,
 *        compiles that into a linked list with nodes to be outputted into output.csv, and outputs formatted information.
 *
 * @param data_file The YAML file full of airline route information.
 * @param n The number of elements that will be outputted.
 * @return void: nothing.
 *
 */
void q3(char data_file[], int n) {
    node_t *head = NULL;
    //read the yaml file
    read_yaml(data_file, &head, 3);
    node_t *temp = head->next;

    char curr_to_airport_name[BUFFER_SIZE];
    strcpy(curr_to_airport_name, ""); // Use strcpy to copy the string

    if (temp != NULL) {
        strcpy(curr_to_airport_name, temp->route.to_airport_name);
    }

    // Initialize head pointer and node
    q3_count_node *count_head = NULL;
    Q3_count new_q3_count;
    q3_count_node *new_q3_count_node = q3_count_new_node(new_q3_count); // Make new count node. Declare as a pointer
    
    // Initialize count node's fields
    init_q3_count_fields(new_q3_count_node, temp);

    // Make this new node the head
    count_head = new_q3_count_node;
    temp = temp->next;

    // Create the count list
    make_q3_count_list(temp, curr_to_airport_name, count_head);

    // Print the count linked list
    q3_count_node *count_temp = count_head;
    q3_output_vals(count_temp, n);

    // Free the allocated memory for the original list
    while (head != NULL) {
        node_t *temp = head;
        head = head->next;
        free(temp);
    }

    // Free the allocated memory for the count list only if not already freed
    q3_count_node *cur = count_head;
    while (cur != NULL) {
        q3_count_node *next = cur->next;
        if (!cur->freed) {
            free(cur);
        }
        cur = next;
    }
}

/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[]) {
    char data_file[256];
    int question = 0;
    int n = 0;

    // Initialize the variables
    memset(data_file, 0, sizeof(data_file));

    // Parse the command-line arguments
    parse_arguments(argc, argv, data_file, &question, &n);

    // Determine which question to answer based on the command-line arguments
    if (question == 1) {
        q1(data_file, n);
    } else if (question == 2) {
        q2(data_file, n);
    } else if (question == 3) {
        q3(data_file, n);
    }

    return 0;
}
