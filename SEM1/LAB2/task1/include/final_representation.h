#ifndef FINAL_REPRESENTATION_H
#define FINAL_REPRESENTATION_H

#include <stdbool.h>

typedef enum {
    OK,
    WRONG_BASE,
    WRONG_NUM_OF_ARGUMENTS,
    ARGUMENT_ERROR,
    MEMORY_ERROR,
    ACCURACY_ERROR
} return_code;

bool * final_repr(return_code *code, const int base, const int n, ...);

#endif