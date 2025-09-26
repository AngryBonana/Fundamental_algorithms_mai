#include "../include/exponent.h"
#include <math.h>
#include "../include/mathFunctions.h"


double lim_count(const double n)
{
    double res = n * (pow(2, 1 / n) - 1);
    return res;
}

double log_lim(const double e)
{
    double prev = lim_count(1);
    double next = lim_count(2);
    int n = 3;
    while(fabs(next - prev) > e)
    {
        prev = next;
        next = lim_count(n);
        n++;
    }

    return next;
}

double row_log(const double prev, const double n)
{
    double res = prev;
    res += pow(-1, n - 1) / n;
    return res;
}

double log_sum(const double e)
{
    double prev = row_log(0, 1);
    double next = row_log(prev, 2);
    int n = 3;
    while(fabs(next - prev) > e && n < 10000000)
    {
        prev = next;
        next = row_log(prev, n);
        n++;
    }

    return next;
}

double log_eq(const double e)
{
    double step = 0.69;
    while (fabs(exp(step) - 2) > e) {
        step += e;
    }

    return step;
}