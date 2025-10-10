#include "../include/flags.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

    int ans[26] = {};
    int size = 100;
    char *buffer = (char *)malloc(sizeof(char) * size);
    if (buffer == NULL)
    {
        return MEMORY_ERROR;
    }
    int pos = 0;
    bool end = false;
    while (true)
    {
        if (pos == size)
        {
            size *= 2;
            char *tmp = (char *)realloc(buffer, sizeof(char) * size);
            if (tmp == NULL)
            {
                free(buffer);
                buffer = NULL;
                return MEMORY_ERROR;
            }
            buffer = tmp;
            tmp = NULL;
        }
        buffer[pos] = fgetc(input);
        if (buffer[pos] == EOF)
        {
            end = true;
        }
        if (buffer[pos] == EOF || buffer[pos] == '\n')
        {
            buffer[pos] = '\0';
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
        
            for (int i = 0; i <= pos; i++)
            {
                buffer[i] = '\0';
            }
            pos = 0;
        }
        else  
        {
            pos++;
        }
        if (end)
        {
            break;
        }
    }

    free(buffer);
    buffer = NULL;
    return OK;
}


return_code s_flag(FILE *input, FILE *output)
{
    if (input == NULL || output == NULL)
    {
        return NULL_PTR;
    } 

    int size = 100;
    char *buffer = (char *)malloc(sizeof(char) * size);
    if (buffer == NULL)
    {
        return MEMORY_ERROR;
    }
    int pos = 0;
    bool end = false;
    
    int ans = 0;

    while (true)
    {
        if (pos == size)
        {
            size *= 2;
            char *tmp = (char *)realloc(buffer, sizeof(char) * size);
            if (tmp == NULL)
            {
                free(buffer);
                buffer = NULL;
                return MEMORY_ERROR;
            }
            buffer = tmp;
            tmp = NULL;
        }
        buffer[pos] = fgetc(input);
        if (buffer[pos] == EOF)
        {
            end = true;
        }
        if (buffer[pos] == EOF || buffer[pos] == '\n')
        {
            buffer[pos] = '\0';
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
        
            for (int i = 0; i <= pos; i++)
            {
                buffer[i] = '\0';
            }
            pos = 0;
        }
        else  
        {
            pos++;
        }
        if (end)
        {
            break;
        }
    }

    free(buffer);
    buffer = NULL;
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