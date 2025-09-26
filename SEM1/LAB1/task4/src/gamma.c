#include "../include/exponent.h"
#include <math.h>
#include "../include/mathFunctions.h"
#include <stdlib.h>

double for_lim_gamma(const int m, const int k)
{
    double res = (double)combinations(m, k) * pow(-1, k) / k;
    res *= log(factorial(k));
    return res;
}

double limit_gamma(const int m)
{   
    if (m == 0)
    {
        return 0;
    }
    double res = 0;
    for (int k = 1; k <= m; k++)
    {
        res += for_lim_gamma(m, k);
    }

    return res;
}

double gamma_lim(const double e)
{
    double prev = limit_gamma(2);
    double next = limit_gamma(3);
    int m = 4;
    while(fabs(next - prev) > e && m < 20)
    {
        prev = next;
        next = limit_gamma(m);
        m++;
    }

    return next;
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
    double prev = row_gamma(100000000, pi);
    double next = row_gamma(100001000, pi);
    int n = 100002000;
    while(fabs(next - prev) > e)
    {
        prev = next;
        next = row_gamma(n, pi);
        n += 1000;
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

double lim_t(const double e)
{
    int n = 1e6;
    int *nums = primeNums(n);
    double prev = lim_c(200, nums);
    double next = lim_c(300, nums);
    int t = 400;
    while(fabs(next - prev) > e && t < n)
    {
        prev = next;
        next = lim_c(t, nums);
        t += 100;
    }


    free(nums);
    return next;
}

double gamma_eq(const double e)
{   
    double eq = lim_t(e);
    double step = 0.577;
    while(fabs(exp(-step) - eq) > e && step < 0.58)
    {
        step += e;
    } 

    return step;
}