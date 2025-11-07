#ifndef STUDENT_H
#define STUDENT_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    OK,
    MEMORY_ERROR,
    WRONG_PTR,
    INCORRECT_FILE,
    FOPEN_ERROR,

} return_code;


typedef struct {
    unsigned int id;
    char * first_name;
    char * last_name;
    char * group;
    unsigned char * grades;

} Student;


int is_valid_name (const char * name);

int is_valid_group (const char * group);

return_code read_students (FILE * stream, Student *** students, size_t * size, size_t * count);

int free_students(Student ** students, size_t count);

int print_students(Student ** students, size_t count);


int compare_by_id (const void * void_st1, const void * void_st2);

int compare_by_first_name (const void * void_st1, const void * void_st2);

int compare_by_last_name (const void * void_st1, const void * void_st2);

int compare_by_group (const void * void_st1, const void * void_st2);

void find_and_print_by_id (Student ** students, size_t count, const unsigned int id);

void find_and_print_by_name (Student ** students, size_t count, char * str);

void find_and_print_by_surname (Student ** students, size_t count, char * str);

void find_and_print_by_group (Student ** students, size_t count, char * str);





#endif