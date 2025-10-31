#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "include/final_representation.h"


int main(void)
{
    return_code code;
    int n = 4;
    int base = 2;
    bool * res = final_repr(&code, 2, 4, 0.5, 0.25, 0.2, 0.125);
    switch (code) {
        case WRONG_BASE:
        {
            printf("ERROR: Wrong base! Base must be more than 1\n");
            return WRONG_BASE;
        }
        break;
        case WRONG_NUM_OF_ARGUMENTS:
        {
            printf("ERROR: Wrong num of argumments! At least 1 argument is required\n");
            return WRONG_NUM_OF_ARGUMENTS;
        }
        break;
        case ARGUMENT_ERROR:
        {
            printf("ERROR: Argument error! All arguments must be between 0 and 1\n");
            return ARGUMENT_ERROR;
        }
        break;
        case ACCURACY_ERROR:
        {
            printf("ERROR: Accuracy error! Num is too small\n");
            return ACCURACY_ERROR;
        }
        break;
        case MEMORY_ERROR:
        {
            printf("ERROR: Memory error! Program can't get memory\n");
            return WRONG_NUM_OF_ARGUMENTS;
        }
        break;
        case OK:
        {
            for (int i = 0; i < n; i++)
            {
                if (res[i])
                {
                    printf("Number %d has final representation in base %d\n", i, base);
                }
                else  
                {
                    printf("Number %d has no final representation in base %d\n", i, base);
                }
            }
            free(res);
            res = NULL;
        }
        break;
    }

    return 0;
}