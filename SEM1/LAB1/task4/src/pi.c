#include "../include/pi.h"
#include <math.h>
#include "../include/mathFunctions.h"

double lim(const int n)
{
    double res = pow(pow(2, n) * factorial(n), 4);
    res /= (double)(n * pow(factorial(2 * n), 2));
    return res;
}

double pi_lim(const double e)
{
    double prev = lim(1);
    double next = lim(2);
    int n = 3;
    while(fabs(next - prev) > e && n < 11)
    {
        prev = next;
        next = lim(n);
        n++;
    } 

    return next;

}


double row_pi(const double prev, const int n)
{
    double next = prev;
    next += 4 * pow(-1, n - 1) / (double)(2 * n - 1);
    return next;
}


double pi_sum(const double e)
{
    double prev = 0;
    double next = row_pi(prev, 1);
    int n = 2;
    while (fabs(next - prev) > e && n < 10000000) {
        prev = next;
        next = row_pi(prev, n);
        n++;
    }

    return next;
}


double pi_eq(const double x, const double e)
{
    double ans = cos(x) + 1;
    return ans;
}

double pi_eq_d(const double x, const double e)
{
    double ans = -sin(x);
    if (fabs(ans) < e)
    {
        ans = e;
    }
    return ans;
}
