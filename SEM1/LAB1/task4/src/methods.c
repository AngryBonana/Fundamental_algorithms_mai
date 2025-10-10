#include "../include/methods.h"
#include <math.h>
#include <stdbool.h>

return_code dichotomy(double (*function) (const double, const double), const double a, const double b, const double e, double *ans)
{
    double left = a, right = b, mid;
    if (function(a, e) * function(b, e) > 0)
    {
        return BAD_BOUNDARY;
    }
    int n = 0;
    while (fabs(right - left) > e)
    {
        if (n >= 1e7)
        {
            *ans = left;
            return ACCURACY_ERROR;
        }
        mid = (left + right) / 2;
        if (function(left, e) * function(mid, e) > 0)
        {
            left = mid;
        }
        else
        {
            right = mid;    
        }
        n++;
    }

    *ans = left;
    return OK;
}


return_code newtone(double (*func) (const double, const double), double (*func_d) (const double, const double), const double x0, const double e, double *ans)
{
    double prev = x0;
    double next = prev - func(prev, e) / func_d(prev, e);
    int n = 1;
    while (fabs(next - prev) > e)
    {
        if (n >= 1e5)
        {
            *ans = next;
            return ACCURACY_ERROR;
        }
        prev = next;
        next = prev - func(prev, e) / func_d(prev, e);
        n++;
    }
    *ans = next;
    return OK;

}
