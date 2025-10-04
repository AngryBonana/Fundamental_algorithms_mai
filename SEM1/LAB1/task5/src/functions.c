#include "../include/functions.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


return_code flagValidation (char *str, bool *n_flag, char *flag)
{
    if (*(str)  != '/' && *(str) != '-')
    {
        return INVALID_FLAG;
    }
    switch (*(str + 1)) {
        case 'n':
            *n_flag = true;
            break;
        case 'd':
        case 'i':
        case 'a':
        case 's':
            *flag = *(str + 1);
            if (*(str + 2) != '\0')
            {
                return INVALID_FLAG;
            }
            return OK;
            break;
        default:
            return INVALID_FLAG;
    }
    
    if (*n_flag)
    {
        switch (*(str + 2)) {
            case 'd':
            case 'i':
            case 'a':
            case 's':
                *flag = *(str + 2);
                if (*(str + 3) != '\0')
                {
                    return INVALID_FLAG;
                }
                return OK;
                break;
            default:
                return INVALID_FLAG;
        }

    }
    return OK;
}


return_code createName (char *str, char **name)
{
    int length = strlen(str);

    *name = (char *)malloc(sizeof(char) * (length + 5));
    if (*name == NULL)
    {
        return MEMORY_ERROR;
    }
    strcpy(*name, "out_");

    strcat(*name, str);

    return OK;
}
