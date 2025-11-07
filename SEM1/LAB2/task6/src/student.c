#include "../include/student.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_valid_name(const char * name)
{
    if (!name)
    {
        return 0;
    }
    if (strlen(name) == 0)
    {
        return 0;
    }
    for (size_t i = 0; name[i] != '\0'; ++i)
    {
        if (!(name[i] >= 'A' && name[i] <= 'Z') && !(name[i] >= 'a' && name[i] <= 'z'))
        {
            return 0;
        }
    }
    return 1;
}


int is_valid_group(const char * group)
{
    if (!group)
    {
        return 0;
    }
    if (strlen(group) == 0)
    {
        return 0;
    }
    return 1;
}


Student * read_one_student (FILE * stream, return_code * code)
{
    if (!stream)
    {
        *code = WRONG_PTR;
        return NULL;
    }
    
    unsigned int id = 0;
    char* first_name = (char*)malloc(sizeof(char)*100);
    char* last_name = (char*)malloc(sizeof(char)*100);
    char* group = (char*)malloc(sizeof(char)*100);
    unsigned char * marks = (unsigned char *)malloc(sizeof(unsigned int) * 5);

    if (!first_name || !last_name || !group || !marks)
    {
        free(first_name);
        free(last_name);
        free(group);
        free(marks);
        *code = MEMORY_ERROR;
        return NULL;
    }

    unsigned int g0, g1, g2, g3, g4;
    int res = fscanf(stream, "%u %99s %99s %99s %u %u %u %u %u", &id, first_name, last_name, group, &g0, &g1, &g2, &g3, &g4);
    if (res == EOF)
    {
        *code = OK;
        free(first_name);
        free(last_name);
        free(group);
        free(marks);
        return NULL;
    }
    if (res != 9)
    {
        *code = INCORRECT_FILE;
        free(first_name);
        free(last_name);
        free(group);
        free(marks);
        return NULL;
    }

    if (g0 > 255 || g1 > 255 || g2 > 255 || g3 > 255 || g4 > 255)
    {
        *code = INCORRECT_FILE;
        free(first_name);
        free(last_name);
        free(group);
        free(marks);
        return NULL;
    }

    marks[0] = (unsigned char)g0;
    marks[1] = (unsigned char)g1;
    marks[2] = (unsigned char)g2;
    marks[3] = (unsigned char)g3;
    marks[4] = (unsigned char)g4;

    if (!is_valid_group(group) || !is_valid_name(first_name) || !is_valid_name(last_name))
    {
        *code = INCORRECT_FILE;
        free(first_name);
        free(last_name);
        free(group);
        free(marks);
        return NULL;
    }

    Student * student = (Student *)malloc(sizeof(Student));
    if (!student)
    {
        free(first_name);
        free(last_name);
        free(group);
        free(marks);
        *code = MEMORY_ERROR;
        return NULL;
    }
    student->id = id;
    student->first_name = first_name;
    student->last_name = last_name;
    student->group = group;
    student->grades = marks;

    *code = OK;
    return student;
}

return_code unique_id (Student ** students, size_t count)
{
    unsigned int * ids = (unsigned int *)malloc(sizeof(unsigned int) * count);
    int repeats = 0;
    if (!ids)
    {
        return MEMORY_ERROR;
    }
    for (size_t i = 0; i < count; ++i)
    {
        ids[i] = students[i]->id;
        for (size_t j = 0; j < i; ++j)
        {
            if (ids[j] == ids[i])
            {
                repeats = 1;
                break;
            }
        }
        if (repeats)
        {
            break;
        }
    }
    free(ids);
    if (repeats)
    {
        return INCORRECT_FILE;
    }
    return OK;
}

return_code read_students (FILE * stream, Student *** students, size_t * size, size_t * count)
{
    if (!stream)
    {
        return WRONG_PTR;
    }

    *count = 0;
    *size = 32;
    *students = (Student **)malloc(sizeof(Student *) * (*size));

    if (!(*students))
    {
        return MEMORY_ERROR;
    }

    while (1)
    {
        return_code code;
        
        Student * new_student = read_one_student(stream, &code);
        if (code != OK)
        {
            free_students(*students, *count);
            *students = NULL;
            *size = 0;
            *count = 0;
            return code;
        }
        if (new_student == NULL)
        {
            break;
        }

        if (*count == *size)
        {
            (*size) *= 2;
            Student ** tmp = (Student **)realloc(*students, sizeof(Student *) * (*size));
            if (!tmp)
            {
                free_students(*students, *count);
                *students = NULL;
                *size = 0;
                *count = 0;
                return MEMORY_ERROR;
            }
            *students = tmp;
            tmp = NULL;
        }

        (*students)[*count] = new_student;
        new_student = NULL;

        (*count)++;
    }

    return_code code = unique_id(*students, *count);
    if (code != OK)
    {
        free_students(*students, *count);
        *students = NULL;
        *size = 0;
        *count = 0;
        return code;
    }

    return OK;
}


int free_students(Student ** students, size_t count)
{
    if (students == NULL)
    {
        return 0;
    }

    for (size_t i = 0; i < count; i++)
    {
        Student * current = students[i];
        current->id = 0;
        free(current->first_name);
        free(current->last_name);
        free(current->group);
        free(current->grades);
        free(current);
    }

    free(students);

    return 1;
}


int print_students(Student ** students, size_t count)
{
    if (students == NULL)
    {
        return -1;
    }
    int counter = 0;
    for (size_t i = 0; i < count; i++)
    {
        Student * current = students[i];
        unsigned int id = current->id;
        char * name = current->first_name;
        char * last_name = current->last_name;
        char * group = current->group;
        int g0 = (int)current->grades[0];
        int g1 = (int)current->grades[1];
        int g2 = (int)current->grades[2];
        int g3 = (int)current->grades[3];
        int g4 = (int)current->grades[4];
        printf("%-5u %-25s %-25s %-25s %-3d %-3d %-3d %-3d %-3d\n", id, name, last_name, group, g0, g1, g2, g3, g4);
        counter++;
    }
    return counter;
}


int compare_by_id (const void * void_st1, const void * void_st2)
{
    const Student * st1 = *(const Student **)void_st1;
    const Student * st2 = *(const Student **)void_st2;
    if (st1->id > st2->id)
    {
        return 1;
    }
    if (st1->id == st2->id)
    {
        return 0;
    }
    return -1;
}


int compare_by_first_name (const void * void_st1, const void * void_st2)
{
    const Student * st1 = *(const Student **)void_st1;
    const Student * st2 = *(const Student **)void_st2;
    return strcmp(st1->first_name, st2->first_name);
}


int compare_by_last_name (const void * void_st1, const void * void_st2)
{
    const Student * st1 = *(const Student **)void_st1;
    const Student * st2 = *(const Student **)void_st2;
    return strcmp(st1->last_name, st2->last_name);
}


int compare_by_group (const void * void_st1, const void * void_st2)
{
    const Student * st1 = *(const Student **)void_st1;
    const Student * st2 = *(const Student **)void_st2;
    return strcmp(st1->group, st2->group);
}


void find_and_print_by_id (Student ** students, size_t count, const unsigned int id)
{
    size_t counter = 0;
    for (size_t i = 0; i < count; i++)
    {
        Student * current = students[i];
        if (current->id == id)
        {
            char * name = current->first_name;
            char * last_name = current->last_name;
            char * group = current->group;
            int g0 = (int)current->grades[0];
            int g1 = (int)current->grades[1];
            int g2 = (int)current->grades[2];
            int g3 = (int)current->grades[3];
            int g4 = (int)current->grades[4];
            printf("%-5u %-25s %-25s %-25s %-3d %-3d %-3d %-3d %-3d\n", id, name, last_name, group, g0, g1, g2, g3, g4);
            counter++;
        }
    }
    if (counter == 0)
    {
        printf("Nothing is found!\n");
    }
}


void find_and_print_by_name (Student ** students, size_t count, char * str)
{
    size_t counter = 0;
    for (size_t i = 0; i < count; i++)
    {
        Student * current = students[i];
        if (strcmp(str, current->first_name) == 0)
        {
            unsigned int id = current->id;
            char * last_name = current->last_name;
            char * group = current->group;
            int g0 = (int)current->grades[0];
            int g1 = (int)current->grades[1];
            int g2 = (int)current->grades[2];
            int g3 = (int)current->grades[3];
            int g4 = (int)current->grades[4];
            printf("%-5u %-25s %-25s %-25s %-3d %-3d %-3d %-3d %-3d\n", id, str, last_name, group, g0, g1, g2, g3, g4);
            counter++;
        }
    }
    if (counter == 0)
    {
        printf("Nothing is found!\n");
    }
}


void find_and_print_by_surname (Student ** students, size_t count, char * str)
{
    size_t counter = 0;
    for (size_t i = 0; i < count; i++)
    {
        Student * current = students[i];
        if (strcmp(str, current->last_name) == 0)
        {
            unsigned int id = current->id;
            char * name = current->first_name;
            char * group = current->group;
            int g0 = (int)current->grades[0];
            int g1 = (int)current->grades[1];
            int g2 = (int)current->grades[2];
            int g3 = (int)current->grades[3];
            int g4 = (int)current->grades[4];
            printf("%-5u %-25s %-25s %-25s %-3d %-3d %-3d %-3d %-3d\n", id, name, str, group, g0, g1, g2, g3, g4);
            counter++;
        }
    }
    if (counter == 0)
    {
        printf("Nothing is found!\n");
    }
}


void find_and_print_by_group (Student ** students, size_t count, char * str)
{
    size_t counter = 0;
    for (size_t i = 0; i < count; i++)
    {
        Student * current = students[i];
        if (strcmp(str, current->group) == 0)
        {
            unsigned int id = current->id;
            char * name = current->first_name;
            char * surname = current->last_name;
            int g0 = (int)current->grades[0];
            int g1 = (int)current->grades[1];
            int g2 = (int)current->grades[2];
            int g3 = (int)current->grades[3];
            int g4 = (int)current->grades[4];
            printf("%-5u %-25s %-25s %-25s %-3d %-3d %-3d %-3d %-3d\n", id, name, surname, str, g0, g1, g2, g3, g4);
            counter++;
        }
    }
    if (counter == 0)
    {
        printf("Nothing is found!\n");
    }
}