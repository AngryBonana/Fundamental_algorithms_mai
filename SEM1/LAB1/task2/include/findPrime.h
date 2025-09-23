#include <stdlib.h>


typedef enum{
    OK,
    INVALID_INPUT,
    INT_OVERFLOW,
    MEMORY_ERROR
} return_code;


return_code findPrime (int *numbers, int *result, const int size, const int max);