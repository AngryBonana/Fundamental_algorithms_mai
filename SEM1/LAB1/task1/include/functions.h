#include <stdbool.h>

typedef enum 
{
    OK,
    INVALID_INPUT,
    INVALID_NUMBER,
    INT_OVERFLOW,
    INVALID_FLAG,

} return_code;


return_code numValidation(char *str, int *num);


return_code flagValidation(char *str, char *c);


return_code factorial(int *ans, int num);

long long sumOfElemts(int num);

bool isPrime(int num);

int hexanalization(char digits[], int num);

void powNums(long long nums[]);