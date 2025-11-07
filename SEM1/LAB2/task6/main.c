#include "include/student.h"
#include "include/interface.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>



int main (int argc, char * argv[])
{
    char * input_filename = NULL;
    char * output_filename = NULL;
    bool tras = false;
    switch (argc)
    {
        case 2:
        {
            input_filename = argv[1];
        }
        break;
        case 3:
        {
            input_filename = argv[1];
            output_filename = argv[2];
            tras = true;
        }
        break;
        default:
        {
            printf("Using: %s <input_filename> <output_filename (optional)>\n", argv[0]);
            return -1;
        }
        break;
    }

    FILE * input = (FILE *)fopen(input_filename, "r");
    if (!input)
    {
        printf("ERROR: Program can't open file '%s'\n", input_filename);
        return FOPEN_ERROR;
    }
    FILE * output = NULL;
    if (tras)
    {
        output = (FILE *)fopen(output_filename, "w");
        if (!output)
        {
            printf("ERROR: Program can't open file '%s'\n", output_filename);
            fclose(input);
            return FOPEN_ERROR;
        }
    }



    Student ** students;
    size_t size_of_students;
    size_t count_of_students;
    return_code code = read_students(input, &students, &size_of_students, &count_of_students);
    fclose(input);

    if (code != OK)
    {
        error_handler(code);
        if (tras)
        {
            fclose(output);
        }
        return code;
    }

    if (count_of_students == 0)
    {
        printf("Input file has no students!\n");
        free_students(students, count_of_students);
        if (tras)
        {
            fclose(output);
        }
        return 0;
    }

    sort_status status = NOT_SORTED;
    print_usage();
    bool working = true;
    while (working)
    {
        printf("Input command: ");
        int command;
        scanf("%d", &command);
        switch (command)
        {
            case 1:
            {
                print_students(students, count_of_students);
            }
            break;
            case 2:
            {
                sort_interface(students, count_of_students, &status);
            }
            break;
            case 3:
            {
                get_interface(students, count_of_students);
            }
            break;
            case 4:
            {
                if (tras)
                {
                    fprintf_by_id(output, students, count_of_students);
                }
                else  
                {
                    printf("Output file is not specified!\nRestart program with output file\n");
                }
            }
            break;
            case 5:
            {
                if (tras)
                {
                    fprintf_more_than_average(output, students, count_of_students);
                }
                else  
                {
                    printf("Output file is not specified!\nRestart program with output file\n");
                }
            }
            break;
            case 6:
            {
                print_usage();
            }
            break;
            case 7:
            {
                working = false;
            }
            break;
            default:
            {
                printf("Unsupported command! Enter '6' to get Usage\n");
            }
            break;
        }
        printf("\n");
        clear_buffer();
    }


    if (tras)
    {
        fclose(output);
    }
    free_students(students,  count_of_students);
    return 0;

}

