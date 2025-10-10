#include "../include/pi.h"
#include <math.h>

double lim(const int n, long long fact, long long fact2)
{
    double res = pow(16, n) * pow(fact, 4);
    res /= (n * pow(fact2, 2));
    return res;
}

return_code pi_lim(const double e, double *ans)
{
    double prev = lim(0, 1, 1);
    double next = lim(1, 1, 2 );
    int n = 2;
    long long fact = 1;
    long long fact2 = 2;
    while(fabs(next - prev) > e)
    {   
        fact *= n;
        fact2 = fact;
        for (int i = n + 1; i <= 2 * n; i++)
        {
            fact2 *= i;
        }
        if (fact2 < 0)
        {
            *ans = next;
            return ACCURACY_ERROR;
        }
        prev = next;
        next = lim(n, fact, fact2);
        n++;
    } 

    *ans = next;
    return OK;

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
