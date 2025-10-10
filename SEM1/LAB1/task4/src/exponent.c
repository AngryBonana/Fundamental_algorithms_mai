#include "../include/exponent.h"
#include <math.h>


double limit(const int n)
{
    const double tmp = 1 + 1 / (double)n;
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
    int n = 3;
    while(!(fabs(next - prev) < e))
    {
        prev = next;
        next = limit(n);
        n++;
    } 
    return next;
}

return_code exp_sum(const double e, double *ans)
{
    long long fact = 1;
    double prev = 0 + 1/(double)fact; //0!
    double next = prev + 1/(double)fact; //1!
    int n = 2;
    while (!(fabs(next - prev) < e))
    {
        fact *= n;
        if (fact < 0)
        {
            *ans = next;
            return ACCURACY_ERROR;
        }
        prev = next;
        next = prev + 1/(double)fact;
        n++;
    } 
    *ans = next;
    return OK;
}


double exp_eq(const double x, const double e)
{
    double ans = log(x) - 1;
    return ans;
}