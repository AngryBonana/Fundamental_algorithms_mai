#include "../include/mystring.h"
#include "../include/errors.h"
#include <stddef.h>
#include <stdlib.h>


void *memchr(const void *str, int c, size_t n)
{
    const unsigned char *ptr = (const unsigned char *)str;
    unsigned char ref = (unsigned char)c;
    for (size_t i = 0; i < n; ++i)
    {
        if (*(ptr + i) == ref)
        {
            return (void *)(str + i);
        }
    }
    return NULL;
}


int memcmp(const void *str1, const void *str2, size_t n)
{
    const unsigned char *s1 = (const unsigned char *)str1;
    const unsigned char *s2 = (const unsigned char *)str2;
    for (size_t i = 0; i < n; ++i)
    {
        if (*(s1 + i) != *(s2 + i))
        {
            return *(s1 + i) > *(s2 + i) ? 1 : -1;
        }
    }
    return 0;
}

void *memcpy(void *dest, const void *src, size_t n)
{
    unsigned char * d = (unsigned char *)dest;
    const unsigned char * s = (const unsigned char *)src;
    for (size_t i = 0; i < n; ++i)
    {
        d[i] = s[i];
    }
    return dest;

}


void *memset(void *str, int c, size_t n)
{
    unsigned char *s = (unsigned char *)str;
    unsigned char sym = (unsigned char)c;
    for (size_t i = 0; i < n; ++i)
    {
        s[i] = sym;
    }
    return str;
}


char *strncat(char *dest, const char *src, size_t n)
{
    char * d = dest;
    while (*d != '\0')
    {
        ++d;
    }
    for (size_t i = 0; i < n; ++i)
    {
        if (*src == '\0')
        {
            break;
        }
        *d = *src;
        ++d;
        ++src;
    }
    *d = '\0';
    return dest;
}


char *strchr(const char *str, int c)
{
    unsigned char sym = (unsigned char)c;
    const unsigned char * s = (const unsigned char *)str;
    while (*s != '\0')
    {
        if (*s == sym)
        {
            return (char *)s;
        }
        s++;
    }
    if (sym == '\0')
    {
        return (char *)s;
    }
    return NULL;
}


int strncmp(const char *str1, const char *str2, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (str1[i] != str2[i])
        {
            return str1[i] > str2[i] ? 1 : -1;
        }
        if (str1[i] == '\0')
        {
            break;
        }
    }

    return 0;
}


char *strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; ++i)
    {
        dest[i] = src[i];
    }
    for (; i < n; ++i)
    {
        dest[i] = '\0';
    }
    return dest;
}


size_t strcspn(const char *str1, const char *str2)
{
    size_t len = 0;
    for (size_t i = 0; str1[i] != '\0'; ++i)
    {
        for (size_t j = 0; str2[j] != '\0'; ++j)
        {
            if (str1[i] == str2[j])
            {
                return len;
            }
        }
        ++len;
    }
    return len;
}


char *strerror(int errnum) {
    const char* error_messages[] = ERROR_MESSAGES;

    #ifdef __APPLE__
        #define MAX_ERRNO 107
    #elif __linux__ 
        #define MAX_ERRNO 133
    #endif

    if (errnum < 0 || errnum > MAX_ERRNO) {
        return "Unknown error";
    }

    const char *msg = error_messages[errnum];
    return (char*)msg;
}


size_t strlen(const char *str)
{
    size_t len = 0;
    while (*str != '\0')
    {
        ++len;
        ++str;
    }
    return len;
}


char *strpbrk(const char *str1, const char *str2)
{
    for (size_t i = 0; str1[i] != '\0'; i++)
    {
        for (size_t j = 0; str2[j] != '\0'; j++)
        {
            if (str1[i] == str2[j])
            {
                return (char *)(str1 + i);
            }
        }
    }
    return NULL;
}


char *strrchr(const char *str, int c)
{
    unsigned char * last = NULL;
    unsigned char sym = (unsigned char)c;
    do
    {
        if ((unsigned char)*str == sym)
        {
            last = (unsigned char *)str;
        }
    } while (*str++);
    return (char *)last;
}


char *strstr(const char *haystack, const char *needle)
{
    if (*needle == '\0')
    {
        return (char *)haystack;
    }
    while(*haystack != '\0')
    {
        const char * h = haystack;
        const char * n = needle;
        while (*h && *n && *h == *n)
        {
            ++h;
            ++n;
        }
        if (*n == '\0')
        {
            return (char *)haystack;
        }
        ++haystack;
    }
    return NULL;
}


size_t strskipdel(const char * str, const char * delim)
{
    size_t count = 0;
    for (size_t i = 0; str[i] != '\0'; ++i)
    {
        size_t found = 0;
        for (size_t j = 0; delim[j] != '\0'; ++j)
        {
            if (str[i] == delim[j])
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            break;
        }
        ++count;
    }
    return count;
}

static char * strtok_last_ptr = NULL;

char *strtok(char *str, const char *delim) {
    if (str == NULL)
    {
        str = strtok_last_ptr;
    }
    str += strskipdel(str, delim);

    if (*str == '\0')
    {
        strtok_last_ptr = str;
        return NULL;
    }

    char *end = strpbrk(str, delim);

    if (end != NULL)
    {
        *end = '\0';
        strtok_last_ptr = end + 1;
    } 
    else 
    {
        strtok_last_ptr = str + strlen(str); 
    }

    return str;
}

