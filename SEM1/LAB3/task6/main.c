#include <stdio.h>
#include <stdlib.h>
#include "include/solution.h"


int main (void)
{
    char * str = NULL;
    char c;
    size_t pos = 0;
    size_t size = 64;

    str = (char *)malloc(sizeof(char) * size);
    if (!str)
    {
        printf("MEMORY ERROR!\n");
        return -1;
    }

    while (1)
    {
        c = getchar();
        if (pos == size)
        {
            size *= 2;
            char * tmp = (char *)realloc(str, sizeof(char) * size);
            if (!tmp)
            {
                free(str);
                printf("MEMORY ERROR!\n");
                return -1;
            }
            str = tmp;
            tmp = NULL;
        }
        if (c == '\n')
        {
            str[pos] = '\0';
            break;
        }
        str[pos++] = c;
    }

    int res = check_brackets(str);
    free(str);
    if (res == -1)
    {
        printf("MEMORY ERROR!\n");
        return -1;
    }
    else if (res == 1) 
    {   
        printf("String is balanced by brackets!\n");
    }
    else  
    {
        printf("String is NOT balanced by brackets!\n");
    }

    return 0;

}