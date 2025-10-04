#include "../include/flags.h"
#include <ctype.h>
#include <stdio.h>


return_code d_flag(FILE *input, FILE *output)
{
    if (input == NULL || output == NULL)
    {
        return NULL_PTR;
    }
    char tmp;
    while((tmp = fgetc(input)) != EOF)
    {
        if (tmp - '0' >= 0 && tmp - '0' < 10)
        {
            continue;
        }
        fputc(tmp, output);
    }

    return OK;
}


return_code i_flag(FILE *input, FILE *output)
{
    if (input == NULL || output == NULL)
    {
        return NULL_PTR;
    } 

    char buffer[512];
    int ans[26] = {};

    while (fgets(buffer, 511, input) != NULL)
    {
        for (int i = 0; buffer[i] != '\0'; i++)
        {
            char tmp = toupper(buffer[i]); 
            if (tmp - 'A' >= 0 && tmp - 'A' < 26)
            {
                ans[tmp - 'A']++;
            }
        }


        for (int i = 0; i < 26; i++)
        {
            fprintf(output, "%c - %d; ", i + 'A', ans[i]);
            ans[i] = 0;
        }
        fprintf(output, "\n");
        
        for (int i = 0; i < 512; i++)
        {
            buffer[i] = '\0';
        }
    }

    return OK;
}


return_code s_flag(FILE *input, FILE *output)
{
    if (input == NULL || output == NULL)
    {
        return NULL_PTR;
    } 

    char buffer[512];
    int ans = 0;

    while (fgets(buffer, 511, input) != NULL)
    {
        for (int i = 0; buffer[i] != '\0'; i++)
        {
            char tmp = toupper(buffer[i]);
            if ((tmp - 'A' >= 0 && tmp - 'A' < 26) || (tmp -'0' >= 0 && tmp - '0' < 10) || (tmp == ' ') || (tmp == '\n'))
            {
                continue;
            }
            ans++;
        }


        fprintf(output, "%d\n", ans);
        ans = 0;
        
        for (int i = 0; i < 512; i++)
        {
            buffer[i] = '\0';
        }
    }

    return OK;
}


return_code a_flag(FILE *input, FILE *output)
{
    if (input == NULL || output == NULL)
    {
        return NULL_PTR;
    } 

    char tmp;
    while((tmp = fgetc(input)) != EOF)
    {
        if (tmp - '0' >= 0 && tmp - '0' < 10)
        {
            fputc(tmp, output);
            continue;
        }
        fprintf(output, "/%X", tmp);
    }
    
    return OK;
}