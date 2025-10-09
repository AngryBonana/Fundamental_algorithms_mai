#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/return_codes.h"
#include "include/functions.h"



int main (void)
{
    unsigned int size = 20;
    unsigned int count = 0;
    long long *nums = (long long *)malloc(sizeof(long long) * size);
    if (nums == NULL)
    {
        printf("ERROR: Memory Error\nProgram can't get memory\n");
        return MEMORY_ERROR;
    }

    int base;
    printf("Введите основание: ");
    scanf("%d", &base);
    if (base > 36 || base < 2)
    {
        printf("ERROR: Argument Error\nBase must be more than 1 and less than 37\n");
        free(nums);
        nums = NULL;
        return ARGUMENT_ERROR;
    }

    char input[65] = {};
    while(true)
    {
        scanf("%64s", input);
        if (stopCheck(input))
        {
            break;
        }
        if (!validation(base, input))
        {
            printf("Incorrect number for base %d\n", base);
            continue;
        }

        if (count == size)
        {
            size *= 2;
            nums = (long long *)realloc(nums, sizeof(long long) * size);
            if (nums == NULL)
            {
                printf("ERROR: Memory Error\nProgram can't get memory\n");
                free(nums);
                nums = NULL;
                return MEMORY_ERROR;
            }
        }

        if(convert_to_dec(input, base, &nums[count]) == LL_OVERFLOW)
        {
            printf("Number is too big and won't be processed\n");
            continue;
        }
        count++;
        
        
    }
    if (count == 0)
    {
        printf("No nums to find max\n");
        return 0;
    }

    long long ans;
    if (findMax(nums, count, &ans) == WRONG_PTR)
    {
        printf("ERROR: Wrong Pointer\nIncorrect pointer\n");
        free(nums);
        nums = NULL;
        return WRONG_PTR;
    }

    char *str = convert_to_base(ans, base);
    if (str == NULL)
    {
        printf("ERROR: Memory Error\nProgram can't get memory\n");
        free(nums);
        nums = NULL;
        return MEMORY_ERROR;
    }
    printf("Max number:\n");
    printf("base %d: %s\n", base, str);
    free(str);
    str = NULL;
    for (int i = 9; i <= 36; i += 9)
    {
        if (i == base) // Пропускаем, если уже выводили
        {
            continue;
        }
        str = convert_to_base(ans, i);
        if (str == NULL)
        {
            printf("ERROR: Memory Error\nProgram can't get memory\n");
            free(nums);
            nums = NULL;
            return MEMORY_ERROR;
        }
        printf("base %d: %s\n", i, str);
        free(str);
        str = NULL;
    }

    
    free(nums);
    nums = NULL;
    return 0;
}