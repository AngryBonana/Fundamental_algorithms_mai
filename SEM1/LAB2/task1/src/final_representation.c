#include "../include/final_representation.h"
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

long long gcd_ll(long long a, long long b)
{
    a = llabs(a);
    b = llabs(b);
    while (a != 0 && b != 0)
    {
        if (a > b)
        {
            a %= b;
        }
        else
        {
            b %= a;
        }
    }
    return a + b;
}


bool find_denominator_and_numerator(const double num, long long *numerator, long long *denominator)
{
    long long scale = 1e10;
    double copy_num = num;
    long long denom = scale;
    long long numer = llround(copy_num * scale);
    if (numer <= 0 || numer >= denom)
    {
        return false;
    }
    long long g = gcd_ll(numer, denom);
    denom /= g;
    numer /= g;
    
    *numerator = numer;
    *denominator = denom;
    return true;
}


long long reduce_common(const long long n, const int base)
{
    long long number = n;
    long long g = gcd_ll(number, base);
    while (g != 1)
    {
        while (number % g == 0)
        {
            number /= g;
        }
        g = gcd_ll(number, (long long)base);
    }
    return number;
}


bool frepr_exist(const int base, const double num, return_code *code)
{
    long long numerator, denominator;

    if (!find_denominator_and_numerator(num, &numerator, &denominator))
    {
        *code = ACCURACY_ERROR;
        return false;
    }

    long long n = reduce_common(denominator, base);
    *code = OK;
    return n == 1;
}



bool * final_repr(return_code *code, const int base, const int n, ...)
{
    if (base < 2)
    {
        *code = WRONG_BASE;
        return NULL;
    }
    if (n < 1)
    {
        *code = WRONG_NUM_OF_ARGUMENTS;
        return NULL;
    }
    bool * result = (bool *)malloc(sizeof(bool) * n);
    if (result == NULL)
    {
        *code = MEMORY_ERROR;
        return NULL;
    }

    va_list args;
    va_start(args, n);

    bool current = false;
    double num;
    for (int i = 0; i < n; ++i)
    {
        num = va_arg(args, double);
        if (num <= 0.0 || num >= 1.0)
        {
            *code = ARGUMENT_ERROR;
            free(result);
            result = NULL;
            va_end(args);
            return NULL;
        }
        return_code fr;
        current = frepr_exist(base, num, &fr);
        if (fr == ACCURACY_ERROR)
        {
            free(result);
            result = NULL;
            *code = ACCURACY_ERROR;
            va_end(args);
            return NULL;
        }
        result[i] = current;
    }

    va_end(args);
    *code = OK;
    return result;
}



