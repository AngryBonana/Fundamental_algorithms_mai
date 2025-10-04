#include <stdio.h>
#include "include/validation.h"
#include "include/return_codes.h"
#include "include/trapezoid.h"
#include "include/functions.h"



int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("ERROR: Invalid Argument\nUsage: ./program <double>\n");
        return INVALID_ARGUMENT;
    }
    double e;
    if (validation(argv[1], &e) == INVALID_ARGUMENT)
    {
        printf("ERROR: Invalid Argument\nArgument must be the double\n");
        return INVALID_ARGUMENT;
    }
    if (e > 1e-1 || e < 1e-15)
    {
        printf("ERROR: Invalid Argument\nArgument must be the double more than 1e-15 and less than 1e-1\n");
        return INVALID_ARGUMENT;
    }
    double ans;
    // a
    printf("Count integral log(1+x)/x from 0 to 1\nWait...\n");
    if(trapezoid(func_a, 0, 1, &ans, e) == ACCURACY_ERROR)
    {
        printf("Can't reach the accuracy. Last value: %.10f\n", ans);
    }
    else 
    {
        printf("%.10f\n", ans);
    }

    // b
    printf("Count integral e^(-x^2/2) from 0 to 1\nWait...\n");
    if(trapezoid(func_b, 0, 1, &ans, e) == ACCURACY_ERROR)
    {
        printf("Can't reach the accuracy. Last value: %.10f\n", ans);
    }
    else 
    {
        printf("%.10f\n", ans);
    }

    // c
    printf("Count integral log(1/(1-x)) from 0 to 1\nWait...\n");
    if(trapezoid(func_c, 0, 1, &ans, e) == ACCURACY_ERROR)
    {
        printf("Can't reach the accuracy. Last value: %.10f\n", ans);
    }
    else 
    {
        printf("%.10f\n", ans);
    }

    // d
    printf("Count integral x^x from 0 to 1\nWait...\n");
    if(trapezoid(func_d, 0, 1, &ans, e) == ACCURACY_ERROR)
    {
        printf("Can't reach the accuracy. Last value: %.10f\n", ans);
    }
    else 
    {
        printf("%.10f\n", ans);
    }

    return 0;
}