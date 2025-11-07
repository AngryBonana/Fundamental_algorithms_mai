#include "../include/transfer.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


return_code read_line_without_start_spaces(FILE * stream, char ** buf, size_t * size, size_t * length)
{
    if (!buf || !*buf || !size || !length)
        return WRONG_PTR;

    int tmp;
    size_t pos = 0;
    *length = 0;

    while ((tmp = getc(stream)) != EOF)
    {
        if (tmp != ' ' && tmp != '\t') 
        {
            ungetc(tmp, stream);
            break;
        }
    }

    if (tmp == EOF)
    {
        *length = 0;
        return END;
    }

    while (1) 
    {
        tmp = getc(stream);
        if (tmp == EOF || tmp == '\n')
        {
            (*buf)[pos] = '\0';
            *length = pos;
            return OK;
        }

        if (pos >= *size - 1)
        { 
            *size *= 2;
            char * t_ptr = realloc(*buf, *size);
            if (!t_ptr)
            {
                *size /= 2;
                return MEMORY_ERROR;
            }
            *buf = t_ptr;
        }

        (*buf)[pos] = (char)tmp;
        pos++;
    }
}


return_code rclear_spaces (char * buf, size_t * length)
{
    if (!buf)
    {
        return WRONG_PTR;
    }
    while (buf[*length - 1] == ' ' || buf[*length - 1] == '\t')
    {
        buf[*length - 1] = '\0';
        (*length)--;
        if (*length == 0)
        {
            break;
        }
    }

    return OK;
}


return_code parse_words (char * buf, size_t * size, size_t * count, char ** words[])
{
    if (!buf)
    {
        return WRONG_PTR;
    }
    char * ptr = strtok(buf, " \t");
    
    while (ptr != 0)
    {
        if (*count == *size)
        {
            *size *= 2;
            char **tmp = (char**)realloc(*words, sizeof(char *) * (*size));
            if (!tmp)
            {
                *size /= 2;
                return MEMORY_ERROR;
            }
            *words = tmp;
            tmp = NULL;
        }
        (*words)[*count] = ptr;
        (*count)++;
        ptr = strtok(NULL, " \t");
    }

    return OK;
}


return_code make_str_80length(char ** dest, size_t * size_of_dest, size_t amount_of_words, char * first_word[], size_t * words_used)
{
    if (!dest || !*dest || !first_word || !words_used)
    {    
        return WRONG_PTR;
    }

    if (amount_of_words > 0 && strlen(first_word[0]) >= 80)
    {
        size_t len = strlen(first_word[0]);
        if (*size_of_dest <= len)
        {
            *size_of_dest = len + 1;
            char *tmp = realloc(*dest, *size_of_dest);
            if (!tmp) return MEMORY_ERROR;
            *dest = tmp;
        }
        strcpy(*dest, first_word[0]);
        *words_used = 1;
        return OK;
    }

    
    size_t used = 0;
    size_t total_len = 0;

    while (used < amount_of_words)
    {
        size_t word_len = strlen(first_word[used]);
        size_t needed = total_len + word_len + (used > 0 ? 1 : 0);
        if (needed > 80)
        {
            break;
        }
        total_len = needed;
        used++;
    }

    if (used == 0)
    {
        *words_used = 0;
        return OK;
    }

    size_t required_size = (used == 1) ? (strlen(first_word[0]) + 1) : 81;
    if (*size_of_dest < required_size) {
        *size_of_dest = required_size;
        char *tmp = realloc(*dest, *size_of_dest);
        if (!tmp) return MEMORY_ERROR;
        *dest = tmp;
    }

    (*dest)[0] = '\0';

    if (used == 1)
    {
        strcpy(*dest, first_word[0]);
    } 
    else 
    {
        int extra_spaces = 80 - (int)total_len; 
        int gaps = (int)used - 1;
        int base_add = extra_spaces / gaps;     
        int extra = extra_spaces % gaps;        

        for (size_t i = 0; i < used; i++)
        {
            strcat(*dest, first_word[i]);
            if (i == used - 1) break;

            int spaces = 1 + base_add + (i < (size_t)extra ? 1 : 0);
            for (int s = 0; s < spaces; s++)
            {
                strcat(*dest, " ");
            }
        }
    }

    *words_used = used;
    return OK;
}


return_code transfer (FILE * input_file, FILE * output_file)
{
    if (!input_file || !output_file)
    {
        return WRONG_PTR;
    }
    size_t size = 256; // Размер буффера
    size_t length = 0; // Длина считанной строки
    char * buf = (char *)malloc(sizeof(char) * size); // Буффер
    if (!buf)
    {
        return MEMORY_ERROR;
    }

    size_t size_of_words = 32; // Размер 
    size_t amount_of_words = 0; // Сколько считано
    char ** words = (char **)malloc(sizeof(char *) * size_of_words); // Указатели на слова
    if (!words)
    {
        free(buf);
        return MEMORY_ERROR;
    } 
    return_code code;
    while (1) 
    {
        code = read_line_without_start_spaces(input_file, &buf, &size, &length);
        if (code == END)
        {
            break;
        }
        if (code != OK)
        {
            free(buf);
            free(words);
            return code;
        }
        if (length == 0)
        {
            continue;
        }
        code = rclear_spaces(buf, &length);
        if (code != OK)
        {
            free(buf);
            free(words);
            return code;
        }
        if (length < 80)
        {
            if (fputs(buf, output_file) == EOF)
            {
                free(buf);
                free(words);
                return WRITING_ERROR;
            }
            fputc('\n', output_file);
            continue;
        }
        // Если 80 и больше
        amount_of_words = 0;
        code = parse_words(buf, &size_of_words, &amount_of_words, &words); // Парсим все слова
        if (code != OK)
        {
            free(words);
            free(buf);
            return code;
        }

        size_t size_of_str = 128;
        char * str = (char *)malloc(sizeof(char) * size_of_str); // Под отформатированную строку
        if (!str)
        {
            free(buf);
            free(words);
            return MEMORY_ERROR;
        }
        size_t words_used = 0;
        char ** current_word = words;
        while (amount_of_words) 
        {
            code = make_str_80length(&str, &size_of_str, amount_of_words, current_word, &words_used);
            if (code != OK)
            {
                free(str);
                free(buf);
                free(words);
                return code;
            }
            if (fputs(str, output_file) == EOF)
            {
                free(buf);
                free(words);
                free(str);
                return WRITING_ERROR;
            }
            fputc('\n', output_file);
            amount_of_words -= words_used;
            current_word += words_used;
            words_used = 0;
        }
        
        free(str);
        str = NULL;


    }
    free(words);
    free(buf);

    return OK;
}