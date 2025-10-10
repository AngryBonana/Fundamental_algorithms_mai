#include "../include/exponent.h"
#include <math.h>
#include "../include/mathFunctions.h"


double limit(const double n)
{
    const double tmp = 1 + 1 / n;
    double res = tmp;
    for (int i = 0; i < n; i++)
    {
        res *= tmp;
    }
    return res;
}

double exp_lim(const double e)
{
    double prev = limit(1);
    double next = limit(2);
    double n = 3;
    while(!(fabs(next - prev) < e))
    {
        prev = next;
        next = limit(n);
        n++;
    } 

    return next;
}

double row(const double prev, const int n)
{
    double next = prev + (1/(double)factorial(n));
    return next;
}

double exp_sum(const double e)
{
    double prev = row(0, 0);
    double next = row(prev, 1);
    int n = 2;
    while (!(fabs(next - prev) < e) && n < 21)
    {
        prev = next;
        next = row(prev, n);
        n++;
    } 

    return next;
}


double exp_eq(const double x, const double e)
{
    double ans = log(x) - 1;
    return ans;
}