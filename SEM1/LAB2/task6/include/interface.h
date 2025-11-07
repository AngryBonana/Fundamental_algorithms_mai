#ifndef INTERFACE_H
#define INTERFACE_H
#include "student.h"

typedef enum {
    NOT_SORTED,
    BY_ID,
    BY_NAME,
    BY_SURENAME,
    BY_GROUP
} sort_status;

void error_handler (return_code error);

void print_usage ();

void sort_interface (Student ** students, size_t count, sort_status *status);

void get_interface (Student ** students, size_t count);

void fprintf_by_id (FILE * stream, Student ** students, size_t count);

void fprintf_more_than_average (FILE * stream, Student ** students, size_t count);

void clear_buffer ();


#endif