#include "../include/functions.h"
#include <math.h>

double func_a(double x, const double e)
{
    if (fabs(x) < e)
    {
        return  1.0;
    }
    return log(1 + x) / x;
}

double func_b(double x, const double e)
{
    return exp(- x * x / 2);
}

double func_c(double x, const double e)
{
    if (fabs(x - 1) < e)
    {
        x = 1.0 - e;
    }

    return -log(1 - x);
}

double func_d(double x, const double e)
{
    return pow(x, x);
}