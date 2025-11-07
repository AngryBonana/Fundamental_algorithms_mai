#include "../include/interface.h"
#include <stddef.h>
#include <stdio.h>


void print_usage ()
{
    char msg[] = "Commands:\n" \
    "1 - print all students\n" \
    "2 - sort students\n" \
    "3 - get students by id/name/surename/group\n" \
    "4 - print student by id in file\n" \
    "5 - print students with average mark more than total average in file\n" \
    "6 - print Usage\n" \
    "7 - close program\n";
    printf("%s", msg);
}

void get_interface (Student ** students, size_t count)
{
    clear_buffer();
    printf("Get by:\n1 - id\n2 - name\n3 - surename\n4 - group\nelse - back\nYour choice: ");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
        {
            unsigned int id;
            printf("Input id: ");
            scanf("%u", &id);
            find_and_print_by_id(students, count, id);
        }
        break;

        case 2:
        {
            char name[100];
            printf("Input name: ");
            scanf("%99s", name);
            find_and_print_by_name(students, count, name);
        }
        break;

        case 3:
        {
            char surname[100];
            printf("Input surname: ");
            scanf("%99s", surname);
            find_and_print_by_surname(students, count, surname);
        }
        break;

        case 4:
        {
            char group[100];
            printf("Input group: ");
            scanf("%99s", group);
            find_and_print_by_group(students, count, group);
        }
        break;

        default:
        {
            printf("Operation canceled\n");
        }
        break;
    }
}


void sort_interface (Student ** students, size_t count, sort_status * status)
{
    clear_buffer();
    printf("Sort by:\n1 - id\n2 - name\n3 - surename\n4 - group\nelse - back\nYour choice: ");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
        {
            if (*status != BY_ID)
            {
                qsort(students, count, sizeof(Student *), compare_by_id);
            }
            *status = BY_ID;
            printf("Done!\n");
        }
        break;
        case 2:
        {
            if (*status != BY_NAME)
            {
                qsort(students, count, sizeof(Student *), compare_by_first_name);
            }
            *status = BY_NAME;
            printf("Done!\n");
        }
        break;
        case 3:
        {
            if (*status != BY_SURENAME)
            {
                qsort(students, count, sizeof(Student *), compare_by_last_name);
            }
            *status = BY_SURENAME;
            printf("Done!\n");
        }
        break;
        case 4:
        {
            if (*status != BY_GROUP)
            {
                qsort(students, count, sizeof(Student *), compare_by_group);
            }
            *status = BY_GROUP;
            printf("Done!\n");
        }
        break;
        default:
        {
            printf("Operation canceled\n");
        }
        break;
    }
}

void error_handler (return_code error)
{
    switch (error) {
        case INCORRECT_FILE:
        {
            printf("ERROR: Input file has incorrect string!\n");
        }
        break;
        case MEMORY_ERROR:
        {
            printf("ERROR: Program can't get memory!\n");
        }
        break;
        case WRONG_PTR:
        {
            printf("ERROR: Function got wrong pointer!\n");
        }
        break;
        default:
        {
            printf("ERROR: Unxpected error!\n");
        }
        break;
    }
}


float average_grage (Student * student)
{
    float average = 0;
    for (size_t i = 0; i < 5; i++)
    {
        average += student->grades[i];
    }
    average /= 5;
    return average;
}


float total_average (Student ** students, size_t count)
{
    float average = 0;
    for (size_t i = 0; i < count; ++i)
    {
        average += average_grage(students[i]);
    }
    average /= count;
    return average;
}


void fprintf_by_id (FILE * stream, Student ** students, size_t count)
{
    clear_buffer();
    unsigned int id;
    printf("Input id: ");
    scanf("%u", &id);
    int counter = 0;
    for (size_t i = 0; i < count; ++i)
    {
        Student * current = students[i];
        if (current->id == id)
        {
            counter++;
            float average = average_grage(current);
            fprintf(stream, "%-5u %-25s %-25s %-25s %-6.2f\n", id, current->first_name, current->last_name, current->group, average);
        }
    }
    if (counter == 0)
    {
        printf("Nothing is found!\n");
    }
    else
    {
        fprintf(stream, "\n");
        printf("Done!\n");
    }
}


void fprintf_more_than_average (FILE * stream, Student ** students, size_t count)
{
    float average = total_average(students, count);
    int counter = 0;
    for (size_t i = 0; i < count; i++)
    {
        Student * current = students[i];
        float tmp_average = average_grage(current);
        if (tmp_average > average)
        {
            counter++;
            fprintf(stream, "%-5u %-25s %-25s %-25s %-5.2f\n", current->id, current->first_name, current->first_name, current->group, tmp_average);
        }
    }
    if (counter == 0)
    {
        printf("Nothing is found!\n");
    }
    else  
    {
        fprintf(stream, "\n");
        printf("Count of written students: %d\n", counter);
    }
}


void clear_buffer ()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}