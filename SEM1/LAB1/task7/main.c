#include <stdio.h>
#include "include/return_codes.h"
#include "include/functions.h"


int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Using: ./program <input_file_path> <output_file_path>\n");
        return WRONG_ARGUMENT;
    }
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Can't open file '%s'\n", argv[1]);
        return INVALID_PATH;
    }
    FILE *output_file = fopen(argv[2], "w");
    if (input_file == NULL)
    {
        printf("Can't open file '%s'\n", argv[2]);
        return INVALID_PATH;
    }

    switch (find_and_print_base(input_file, output_file)) {
        case WRONG_PTR:
        {
            printf("ERROR: Wrong Ptr\nFunction find_and_print_base() got null ptr\n");
            fclose(input_file);
            fclose(output_file);
            input_file = NULL;
            output_file = NULL;
            return WRONG_ARGUMENT;
        }
        break;
        case OK:
        {
            printf("Succes! Result in file '%s'\n", argv[2]);
        }
        break;
        case UNEXPECTED_CHAR:
        {
            printf("ERROR: Unexpected character in '%s'\nProgram is stopped\nAll before is converted and printed in %s\n", argv[1], argv[2]);
            fclose(input_file);
            fclose(output_file);
            input_file = NULL;
            output_file = NULL;
            return UNEXPECTED_CHAR;
        }
        default:
        {
            printf("ERROR: Unexpected Error!\nSomething goes wrong!\n");
            fclose(input_file);
            fclose(output_file);
            input_file = NULL;
            output_file = NULL;
            return UNEXPECTED_ERROR;
        }
        break;
    }


    fclose(input_file);
    fclose(output_file);
    input_file = NULL;
    output_file = NULL;
    return 0;
}