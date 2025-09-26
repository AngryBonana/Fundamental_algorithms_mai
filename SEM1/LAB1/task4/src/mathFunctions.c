#include "../include/mathFunctions.h"
#include <stdlib.h>

long long factorial(const int n)
{
    long long res = 1;
    if (n == 0)
    {
        return res;
    }
    for (int i = 1; i <= n; i++)
    {
        res *= i;
    }

    return res;
}


long long combinations(const int n, const int k)
{
    long long res = (factorial(n) / factorial(k)) / factorial(n - k);
    return res;
}

int *primeNums(int n)
{
    int *nums = (int *)malloc(sizeof(int) * n);
    if (!nums)
    {
        return NULL;
    }
    for (int i = 0; i < n; i++)
    {
        nums[i] = i;
    }
    nums[0] = 0;
    nums[1] = 0;
    for (int i = 2; i < n; i++)
    {
        if(nums[i] == 0)
        {
            continue;
        }
        for (int j = i + i; j < n; j += i)
        {
            nums[j] = 0;
        }
    }
    return nums;
}