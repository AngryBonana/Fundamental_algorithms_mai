#include "../include/solution.h"
#include "../include/stack.h"



int check_type (char c)
{
    switch (c) 
    {
        case '(':
        case ')':
        case '{':
        case '}':
        case '[':
        case ']':
        case '<':
        case '>':
        return 1;
        default:
        return 0;
    }
}

int cmp_brackets (char prev, char now)
{
    if (prev == '(' && now == ')')
    {
        return 1;
    }
    if (prev == '[' && now == ']')
    {
        return 1;
    }
    if (prev == '{' && now == '}')
    {
        return 1;
    }
    if (prev == '<' && now == '>')
    {
        return 1;
    }

    return 0;
}

int check_brackets (const char *str)
{
    // -1 ошибка
    // 0 неправильная строка
    // 1 правильная строка
    Stack * temp = stack_create();
    if (!temp)
    {
        return -1;
    }

    for (unsigned int i = 0; str[i] != '\0'; ++i)
    {
        char sym = str[i];
        int t = check_type(sym);
        if (t == 0)
        {
            continue;
        }
        switch (sym) 
        {
            case '(':
            case '[':
            case '{':
            case '<':
            {
                if (!stack_push(temp, sym))
                {
                    stack_destroy(temp);
                    return -1;
                }
            }
            break;
            default:
            {
                int prev = stack_top(temp);
                if (prev == -1)
                {
                    stack_destroy(temp);
                    return 0;
                }
                if (!cmp_brackets((char)prev, sym))
                {
                    stack_destroy(temp);
                    return 0;
                }
                stack_pop(temp);
            }
            break;
        }
        
    }

    int res = stack_empty(temp);

    stack_destroy(temp);

    return res;
}