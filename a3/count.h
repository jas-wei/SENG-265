#ifndef COUNT_H
#define COUNT_H

#define BUFFER_SIZE 256

/**
 * @brief Struct representing the count of airline routes for question 1.
 */
typedef struct {
    char airline_name[BUFFER_SIZE];           
    char airline_icao_unique_code[BUFFER_SIZE]; 
    int count; // The count of routes associated with the airline
} Q1_count;

/**
 * @brief Struct representing the count of destination countries for question 2.
 */
typedef struct {
    char to_airport_country[BUFFER_SIZE];     
    int count; // The count of routes to the destination country
} Q2_count;

/**
 * @brief Struct representing the count of destination airports for question 3.
 */
typedef struct {
    char to_airport_name[BUFFER_SIZE];
    char to_airport_icao_unique_code[BUFFER_SIZE]; 
    char to_airport_city[BUFFER_SIZE];      
    char to_airport_country[BUFFER_SIZE];     
    int count; // The count of routes to the destination airport
} Q3_count;

#endif // COUNT_H