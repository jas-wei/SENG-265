// route.h
#ifndef ROUTE_H
#define ROUTE_H

#define BUFFER_SIZE 256

/**
 * @brief Struct representing an airline route.
 */
typedef struct {
    char airline_name[BUFFER_SIZE];
    char airline_icao_unique_code[BUFFER_SIZE];
    char airline_country[BUFFER_SIZE];
    char from_airport_name[BUFFER_SIZE];
    char from_airport_city[BUFFER_SIZE];
    char from_airport_country[BUFFER_SIZE];
    char from_airport_icao_unique_code[BUFFER_SIZE];
    char from_airport_altitude[BUFFER_SIZE];
    char to_airport_name[BUFFER_SIZE];
    char to_airport_city[BUFFER_SIZE];
    char to_airport_country[BUFFER_SIZE];
    char to_airport_icao_unique_code[BUFFER_SIZE];
    char to_airport_altitude[BUFFER_SIZE];
} Route;

#endif // ROUTE_H