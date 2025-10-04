#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/flags.h"


int main(int argc, char * argv[])
{
    if (argc < 3)
    {
        printf("Usage: ./program <flag> <filename> <optional_filename>\n");
        return ARGUMENT_ERROR;
    }

    char flag;
    bool n_flag;
    if (flagValidation(argv[1], &n_flag, &flag) == INVALID_FLAG)
    {
        printf("ERROR: Invalid Flag\nSupported: -d, -i, -s, -a, -nd, -ni, -ns, -na\n");
        return INVALID_FLAG;
    }

    if (n_flag && argc != 4)
    {
        printf("ERROR: Argument Error\nUsage: ./program -n%c <filename> <output_filename>\n", flag);
        return ARGUMENT_ERROR;
    }
    if (!n_flag && argc != 3)
    {
        printf("ERROR: Argument Error\nUsage: ./program -%c <filename>\n", flag);
        return ARGUMENT_ERROR;

    }
    
    FILE *input_file = fopen(argv[2], "r");
    if (input_file == NULL)
    {
        printf("ERROR: Invalid Path\nCan't open file '%s'\n", argv[2]);
        return INVALID_PATH;
    }

    FILE *output_file = NULL;
    if (n_flag)
    {
        output_file = fopen(argv[3], "w");
        if (output_file == NULL)
        {
            printf("ERROR: Invalid Path\nCan't open file '%s'\n", argv[3]);
            fclose(input_file);
            input_file = NULL;
            return INVALID_PATH;
        }
    }
    else
    {
        char * name;
        if(createName(argv[2], &name) == MEMORY_ERROR)
        {
            printf("ERROR: Memory Error\nCan't create output filename\n");
            fclose(input_file);
            input_file = NULL;
            return MEMORY_ERROR;
        }
        output_file = fopen(name, "w");
        if (output_file == NULL)
        {
            printf("ERROR: Invalid Path\nCan't open file '%s'\n", name);
            fclose(input_file);
            input_file = NULL;
            free(name);
            name = NULL;
            return INVALID_PATH;
        }
        free(name);
        name = NULL;
    }

    switch (flag) {
        case 'd':
            if (d_flag(input_file, output_file) == NULL_PTR)
            {
                fclose(input_file);
                fclose(output_file);
                input_file = NULL;
                output_file = NULL;
                printf("ERROR: NULL_PTR\nFunction got null_ptr argument\n");
                return NULL_PTR;
            }
            break;
        case 'i':
            if (i_flag(input_file, output_file) == NULL_PTR)
            {
                fclose(input_file);
                fclose(output_file);
                input_file = NULL;
                output_file = NULL;
                printf("ERROR: NULL_PTR\nFunction got null_ptr argument\n");
                return NULL_PTR;
            }
            break;
        case 's':
            if (s_flag(input_file, output_file) == NULL_PTR)
            {
                fclose(input_file);
                fclose(output_file);
                input_file = NULL;
                output_file = NULL;
                printf("ERROR: NULL_PTR\nFunction got null_ptr argument\n");
                return NULL_PTR;
            }
            break;
        case 'a':
            if (a_flag(input_file, output_file) == NULL_PTR)
            {
                fclose(input_file);
                fclose(output_file);
                input_file = NULL;
                output_file = NULL;
                printf("ERROR: NULL_PTR\nFunction got null_ptr argument\n");
                return NULL_PTR;
            }
            break;
    }



    fclose(input_file);
    fclose(output_file);
    input_file = NULL;
    output_file = NULL;
    return 0;
}