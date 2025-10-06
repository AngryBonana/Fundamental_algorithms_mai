#include "../include/functions.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

void print_result(FILE *output, char* str, int size)
{
    long long dec = 0;
    bool isMinus = false;
    char max = '1';
    int base = 2;

    if (str[0] == '-' && str[1] == '\0') // If only minus
    {
        return;
    }

    if (str[0] == '-')
    {   
        isMinus = true;
        size--;
        str++;
    }

    while(*str == '0')
    {
        str++;
        size--;
        if (size == 0) // If only '0'
        {
            fprintf(output, "Num: 0\tbase: 2\tdec: 0\n");
            return;
        }

    }

    fprintf(output, "Num: ");
    if (isMinus)
    {
        putc('-', output);
    }

    for (int i = 0; i < size; i++)
    {
        putc(str[i], output);
        if (str[i] > max)
        {
            max = str[i];
        }
    }

    fprintf(output, "\tbase: ");

    if (max >= 'A')
    {
        base = max - 'A' + 11;
    }
    else  
    {
        base = max - '0' + 1;
    }
    fprintf(output, "%d\tdec: ", base);

    char tmp;
    
    for (int i = 0; i < size; i++)
    {
        tmp = str[i];
        if (tmp >= 'A')
        {
            dec += pow(base, size - 1 - i) * (tmp - 'A' + 10);
        }
        else  
        {
            dec += pow(base, size - 1 - i) * (tmp - '0');
        }

        if (dec < 0)
        {
            fprintf(output, "too big to convert\n");
            return;
        }
    }
    if (isMinus)
    {
        putc('-', output);
    }
    fprintf(output, "%lld\n", dec);
    return;
}

void clear_str(char *str, int size)
{
    for (int i = 0; i < size; i++)
    {
        str[i] = '\0';
    }
}

return_code find_and_print_base(FILE *input, FILE *output)
{
    if (input == NULL || output == NULL)
    {
        return WRONG_PTR;
    }

    char tmp;
    bool isNumber = false;
    bool isMinus = false;
    int count = 0;
    char num[100] = {};
    while ((tmp = toupper(getc(input))) != EOF)
    {
        if (tmp == ' ' || tmp == '\t' || tmp == '\n')
        {
            if (isNumber)
            {
                print_result(output, num, count);
                isNumber = false;
                isMinus = false;
                clear_str(num, count);
                count = 0;
            }

        }
        else if (tmp == '-')
        {
            if (isMinus && num[1] == '\0')
            {
                isMinus = false;
                num[0] = '\0';
                isNumber = false;
                count = 0;
            }
            else if (isNumber)
            {
                print_result(output, num, count);
                isNumber = false;
                isMinus = false;
                clear_str(num, count);
                count = 0;
            }
            else  
            {
                num[0] = '-';
                count = 1;
                isMinus = true;
            }

            
        }
        else if ((tmp >= '0' && tmp <= '9') || (tmp >= 'A' && tmp <= 'Z'))
        {
            num[count] = tmp;
            count++;
            isNumber = true;
            if (count == 100)
            {
                print_result(output, num, count);
                isNumber = false;
                isMinus = false;
                clear_str(num, count);
                count = 0;
            }
        }
        else  
        {
            if (isNumber)
            {
                print_result(output, num, count);
                isNumber = false;
                isMinus = false;
                clear_str(num, count);
                count = 0;
            }
            return UNEXPECTED_CHAR;
        }
    }
    if (isNumber)
    {
        print_result(output, num, count);
        isNumber = false;
        isMinus = false;
        clear_str(num, count);
        count = 0;
    }

    return OK;
}