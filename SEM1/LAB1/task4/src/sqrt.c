#include "../include/sqrt.h"
#include <math.h>
#include "../include/mathFunctions.h"


double lim_counter(const double prev)
{
    double next = prev - prev * prev / 2 + 1;
    return next;
}

double sqrt_lim(const double e)
{
    double prev = -0.5;
    double next = lim_counter(prev);
    while(fabs(next - prev) > e)
    {
        prev = next;
        next = lim_counter(prev);
    }
    return next;
}

double mult_sqrt(const double prev, const int k)
{
    double res = prev * pow(2, pow(2, -1 * k));
    return res;
}

double sqrt_mult(const double e)
{
    double prev = 1;
    double next = mult_sqrt(prev, 2);
    int k = 3;
    while(fabs(next - prev) > e)
    {
        prev = next;
        next = mult_sqrt(prev, k);
        k++;
    }
    return next;
}


double sqrt_eq(const double x, const double e)
{
    double ans = x * x - 2;
    return ans;
}