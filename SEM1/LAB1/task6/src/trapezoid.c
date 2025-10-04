#include "../include/trapezoid.h"
#include <math.h>

double count(double (*func) (double, const double), const double a, const double b, const int n, const double e)
{
    double step = (b - a) / n;
    double tmp = a + step;
    double ans = (func(a, e) + func(b, e)) / 2;
    for (int i = 0; i < n - 1; i++)
    {
        ans += func(tmp, e);
        tmp += step;
    }
    ans *= step;
    return ans;
}

return_code trapezoid(double (*func) (double, const double), const double a, const double b, double *ans, const double e)
{
    int n = 2;
    double prev = count(func, a, b, n, e);
    n *= 2;
    double next = count(func, a, b, n, e);
    while(fabs(next - prev) > 3 * e) // Правило Рунге
    {
        if (n >= 1e7)
        {
            *ans = next;
            return ACCURACY_ERROR;
        }
        n *= 2;
        prev = next;
        next = count(func, a, b, n, e);
        
    }
    next = round(next / e) * e; // Округляем до указанного знака
    *ans = next;
    return OK;
}
