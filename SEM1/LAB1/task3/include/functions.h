#include <stdbool.h>

typedef enum {
    OK,
    INVALID_ARGUMENT,
    INVALID_FLAG,
    INVALID_INTEGER,
    INTEGER_OVERFLOW,
    INVALID_FLOAT,
    FLOAT_OVERFLOW,
    
} return_code;


typedef enum {
    INFINITY_SOLUTION,
    NO_SOLUTION,
    ONE_SOLUTION,
    TWO_SOLUTION
} solution_code;

return_code flagValidation(char * forValidation, char * flag);


return_code intValidation(char *str, int *num);


return_code floatValidation(char *str, float *num);


bool multiplicity(int num1, int num2);


bool triangle(const float a, const float b, const float c, const float e);


solution_code quadro(const float a, const float b, const float c, const float e, double *ans1, double *ans2);


void printAnswer(solution_code code_ans, const float a, const float b, const float c, const double ans1, const double ans2);