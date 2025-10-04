#include "../include/validation.h"
#include <math.h>
#include <stdlib.h>

return_code validation(const char *str, double *num)
{
    char *endptr;
    double ans = strtod(str, &endptr);
    if (*endptr != '\0' || ans == HUGE_VAL || ans == -HUGE_VAL)
    {
        return INVALID_ARGUMENT;
    }

    *num = ans;
    return OK;
}