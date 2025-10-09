#include "../include/functions.h"
#include "string.h"
#include <stdbool.h>
#include <stdlib.h>

bool validation(int base, char *str)
{
    int code;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (i == 0 && str[i] == '-')
        {
            continue;
        }

        code = str[i] - '0';
        if (code >= 0 && code <= 9 && code < base)
        {
            continue;
        }
        code = str[i] - 'A' + 10;
        if (code >= 10 && code <= 35 && code < base)
        {
            continue;
        }
        return false;

    }

    return true;
}

return_code convert_to_dec(char *str, const int base, long long *ans)
{
    bool minus = false;
    if (*str == '-')
    {
        minus = true;
        str++;
    }

    long long num = 0;
    while(*str != '\0')
    {
        num *= base;
        if (*str - '0' >= 0 && *str - '0' <= 9)
        {
            num += *str - '0';
        }
        else if (*str - 'A' >= 0 && *str - 'A' <= 25)
        {
            num += *str - 'A' + 10;
        }

        if (num < 0) {
            return LL_OVERFLOW;
        }
        str++;
    }

    if (minus)
    {
        num = -num;
    }
    *ans = num;

    return OK;
}

char * convert_to_base(long long num, const int base)
{
    char *ans = (char *)malloc(sizeof(char) * 64);
    
    if (ans == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < 64; i++)
    {
        ans[i] = '\0';
    }
    
    int position = 63;
    int tmp;
    bool minus = false;
    int counter = 0;

    if (num < 0)
    {
        minus = true;
        num = -num;
    }

    while (num != 0)
    {
        tmp = num % base;
        num /= base;
        if (tmp < 10)
        {
            ans[position] = tmp + '0';
        }
        else 
        {
            ans[position] = tmp - 10 + 'A';
        }
        position--;
        counter++;
    }

    if (minus)
    {
        ans[0] = '-';
    }
    
    for (int i = 0; i < counter; i++)
    {
        if (minus)
        {
            ans[i + 1] = ans[position + 1];
        }
        else
        {
            ans[i] = ans[position + 1];
        }
        position++;
    }
    return ans;
}

bool stopCheck(char *str)
{
    if (strcmp(str, "Stop") == 0)
    {
        return true;
    }
    return false;
}

long long llabs(const long long num)
{
    if (num < 0)
    {
        return num * (-1);
    }

    return num;
}

return_code findMax(long long *nums, const unsigned int size, long long *ans)
{
    if (nums == NULL)
    {
        return WRONG_PTR;
    }
    long long max = 0;
    for (int i = 0; i < size; i++)
    {
        if (llabs(nums[i]) > llabs(max))
        {
            max = nums[i];
        }
    }

    *ans = max;

    return OK;
}