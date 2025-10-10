#include "../include/gamma.h"
#include <math.h>
#include "../include/mathFunctions.h"
#include <stdlib.h>


double for_lim_gamma(const int m, const int k, const long long fact)
{
    double res = (double)combinations(m, k) * pow(-1, k) / k;
    res *= log(fact);
    return res;
}

return_code limit_gamma(const int m, double *ans)
{   
    if (m == 0)
    {
        return 0;
    }
    double res = 0;
    long long fact = 1;
    for (int k = 1; k <= m; k++)
    {
        fact *= k;
        if (fact < 0)
        {
            return ACCURACY_ERROR;
        }
        res += for_lim_gamma(m, k, fact);
    }

    *ans = res;
    return OK;
}

return_code gamma_lim(const double e, double *ans)
{
    double prev;
    double next;
    limit_gamma(2, &prev);
    limit_gamma(3, &next);
    int m = 4;
    while(fabs(next - prev) > e)
    {
        prev = next;
        switch(limit_gamma(m, &next))
        {
            case ACCURACY_ERROR:
            {
                *ans = next;
                return ACCURACY_ERROR;
            }
            break;
            default:
                m++;
                continue;
                break;

        }
    }

    *ans = next;
    return OK;
}

double row_gamma(const int n, const double pi)
{
    double res = - pi * pi / 6;
    int tmp;
    for(int k = 2; k <= n; k++)
    {
        tmp = (int)sqrt(k);
        tmp *= tmp;
        res += (1 / (double)tmp - 1 / (double)k);
    }

    return res;
}

double gamma_sum(const double e, const double pi)
{
    double prev = row_gamma(1e7, pi);
    double next = row_gamma(1e7 + 1e3, pi);
    int n = 1e7 + 2e3;
    while(fabs(next - prev) > e )
    {
        prev = next;
        next = row_gamma(n, pi);
        n += 1e3;
    }

    return next;
}

double lim_c(const int t, int *nums)
{
    double res = log(t);
    for(int i = 0; i <= t; i++)
    {
        if (nums[i] != 0)
        {
            res *= ((double)(i - 1) / i);
        }
    }
    return res;
}

double lim_t(const double e, int *nums, int n)
{
    double prev = lim_c(200, nums);
    double next = lim_c(300, nums);
    int t = 400;
    while(fabs(next - prev) > e && t < n)
    {
        prev = next;
        next = lim_c(t, nums);
        t += 100;
    }


    
    return next;
}

double gamma_eq(const double x, const double e)
{   
    int n = 1e6;
    int *nums = primeNums(n);
    if (nums == NULL)
    {
        return 0;
    }
    double ans = exp(-x) - lim_t(e, nums, n);
    free(nums);
    nums = NULL;
    return ans;
}

double gamma_eq_d(const double x, const double e)
{
    double ans = -exp(-x);
    return ans;
}