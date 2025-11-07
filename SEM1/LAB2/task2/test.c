#include <stdio.h>
#include <stdlib.h>
#include "include/mystring.h"


void test_print_size_t(const char *name, size_t first, size_t second)
{
    printf("%-35s: ", name);
    if (first == second)
    {
        printf("OK\n");
        return;
    }
    printf("FAILED (got %zu, expected %zu)\n", first, second);
}

void test_print_int(const char *name, int first, int second)
{
    printf("%-35s: ", name);
    if ((first == 0 && second == 0) || (first < 0 && second < 0) || (first > 0 && second > 0))
    {
        printf("OK\n");
        return;
    }
    printf("FAILED (got %d, expected %d)\n", first, second);
}

void test_print_ptr(const char *name, void *first, void *second)
{
    printf("%-35s: ", name);
    if (first == second)
    {
        printf("OK\n");
        return;
    }
    printf("FAILED (got %p, expected %p)\n", (void *)first, (void *)second);
}

void test_print_string(const char *name, const char *first, const char *second)
{
    printf("%-35s: ", name);
    if (!first && !second)
    {
        printf("OK\n");
        return;
    }
    if (!first || !second)
    {
        printf("FAILED (NULL mismatch)\n");
        return;
    }
    while (*first && *second && *first == *second)
    {
        first++;
        second++;
    }
    if (*first == '\0' && *second == '\0')
        printf("OK\n");
    else
        printf("FAILED (string mismatch)\n");
}

void test_print_error_msg(const char *name, const char *my_msg, const char *expected_msg)
{
    test_print_string(name, my_msg, expected_msg);
}

int sign(int x) {
    if (x == 0)
    { 
        return 0;
    }
    return x > 0 ? 1 : -1;
}


void test_memchr(void)
{
    const char s[] = "hello world";
    test_print_ptr("memchr(\"hello world\", 'o', 4)", memchr(s, 'o', 4), NULL);
    test_print_ptr("memchr(\"hello world\", 'o', 6)", memchr(s, 'o', 6), (void*)(s + 4));
    test_print_ptr("memchr(\"hello world\", '\\0', 12)", memchr(s, '\0', 12), (void*)(s + 11));
    test_print_ptr("memchr(\"hello world\", 'x', 12)", memchr(s, 'x', 12), NULL);
}

void test_memcmp(void)
{
    test_print_int("memcmp(\"ab\", \"ac\", 2)", sign(memcmp("ab", "ac", 2)), -1);
    test_print_int("memcmp(\"ac\", \"ab\", 2)", sign(memcmp("ac", "ab", 2)), 1);
    test_print_int("memcmp(\"ab\", \"ab\", 2)", memcmp("ab", "ab", 2), 0);

    char x[] = {1, 2, 3, 0, 5};
    char y[] = {1, 2, 3, 0, 6};
    test_print_int("memcmp with \\0 inside", sign(memcmp(x, y, 5)), -1);
}

void test_memcpy(void)
{
    char dest[20];
    const char src[] = "hello";
    memcpy(dest, src, 6);
    test_print_string("memcpy(\"hello\")", dest, "hello");
}

void test_memset(void)
{
    char buf[10];
    memset(buf, 'A', 5);
    buf[5] = '\0';
    test_print_string("memset('A', 5)", buf, "AAAAA");
}

void test_strncat(void)
{
    char dest[20] = "hello";
    strncat(dest, " world", 6);
    test_print_string("strncat basic", dest, "hello world");

    char dest2[10] = "hi";
    strncat(dest2, "", 5);
    test_print_string("strncat empty src", dest2, "hi");
}

void test_strchr(void)
{
    const char *s = "hello";
    test_print_ptr("strchr(\"hello\", 'e')", strchr(s, 'e'), (char*)s + 1);
    test_print_ptr("strchr(\"hello\", 'x')", strchr(s, 'x'), NULL);
    test_print_ptr("strchr(\"hello\", '\\0')", strchr(s, '\0'), (char*)s + 5);
    test_print_ptr("strchr(\"\")", strchr("", '\0'), (char*)"");
}

void test_strncmp(void)
{
    test_print_int("strncmp(\"hello\",\"hallo\",5)", sign(strncmp("hello", "hallo", 5)), 1);
    test_print_int("strncmp(\"he\",\"hello\",5)", sign(strncmp("he", "hello", 5)), -1);
    test_print_int("strncmp(\"hello\",\"hello\",10)", strncmp("hello", "hello", 10), 0);
}

void test_strncpy(void)
{
    char dest[10];
    strncpy(dest, "hi", 5);
    dest[5] = '\0'; 
    test_print_string("strncpy(\"hi\",5)", dest, "hi");

    char dest2[5];
    strncpy(dest2, "12345", 5);
    
    test_print_int("strncpy no null term [0]", dest2[0] == '1', 1);
    test_print_int("strncpy no null term [4]", dest2[4] == '5', 1);
}

void test_strcspn(void)
{
    test_print_size_t("strcspn(\"hello\",\"aeiou\")", strcspn("hello", "aeiou"), 1);
    test_print_size_t("strcspn(\"xyz\",\"abc\")", strcspn("xyz", "abc"), 3);
    test_print_size_t("strcspn(\"\",\"abc\")", strcspn("", "abc"), 0);
    test_print_size_t("strcspn(\"hello\",\"\")", strcspn("hello", ""), 5);
}

void test_strerror(void)
{
    test_print_error_msg("strerror(0)", strerror(0), "Success");
    test_print_error_msg("strerror(2)", strerror(2), "No such file or directory");
    test_print_error_msg("strerror(-1)", strerror(-1), "Unknown error");
    test_print_error_msg("strerror(999999)", strerror(999999), "Unknown error");
}

void test_strlen(void)
{
    test_print_size_t("strlen(\"\")", strlen(""), 0);
    test_print_size_t("strlen(\"a\")", strlen("a"), 1);
    test_print_size_t("strlen(\"hello\")", strlen("hello"), 5);
}

void test_strpbrk(void)
{
    const char *s = "hello";
    test_print_ptr("strpbrk(\"hello\",\"aeiou\")", strpbrk(s, "aeiou"), (char*)s + 1);
    test_print_ptr("strpbrk(\"xyz\",\"abc\")", strpbrk("xyz", "abc"), NULL);
    test_print_ptr("strpbrk(\"hello\",\"h\")", strpbrk(s, "h"), (char*)s);
}

void test_strrchr(void)
{
    const char *s = "hello";
    test_print_ptr("strrchr(\"hello\",'l')", strrchr(s, 'l'), (char*)s + 3);
    test_print_ptr("strrchr(\"hello\",'x')", strrchr(s, 'x'), NULL);
    test_print_ptr("strrchr(\"hello\",'\\0')", strrchr(s, '\0'), (char*)s + 5);
}

void test_strstr(void)
{
    const char *s = "hello world";
    test_print_ptr("strstr(\"hello world\",\"world\")", strstr(s, "world"), (char*)s + 6);
    test_print_ptr("strstr(\"hello world\",\"lo\")", strstr(s, "lo"), (char*)s + 3);
    test_print_ptr("strstr(\"hello world\",\"xyz\")", strstr(s, "xyz"), NULL);
    test_print_ptr("strstr(\"hello world\",\"\")", strstr(s, ""), (char*)s);
}

void test_strtok(void)
{
    char s1[] = " hello,world ";
    char *token = strtok(s1, " ,");
    test_print_string("strtok first token", token, "hello");

    token = strtok(NULL, " ,");
    test_print_string("strtok second token", token, "world");

    token = strtok(NULL, " ,");
    test_print_ptr("strtok end", token, NULL);

    char s2[] = "a:b:c";
    token = strtok(s2, ":");
    test_print_string("strtok colon 1", token, "a");
    token = strtok(NULL, ":");
    test_print_string("strtok colon 2", token, "b");
    token = strtok(NULL, ":");
    test_print_string("strtok colon 3", token, "c");
    token = strtok(NULL, ":");
    test_print_ptr("strtok colon end", token, NULL);
}



int main(void)
{
    printf("=== Тестирование mystring ===\n\n");

    test_memchr();
    test_memcmp();
    test_memcpy();
    test_memset();
    test_strncat();
    test_strchr();
    test_strncmp();
    test_strncpy();
    test_strcspn();
    test_strerror();
    test_strlen();
    test_strpbrk();
    test_strrchr();
    test_strstr();
    test_strtok();

    printf("\n Тестирование завершено.\n");
    return 0;
}