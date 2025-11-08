#include "../include/stack.h"
#include <stdlib.h>


node * node_create (char value)
{
    node * n = (node *)malloc(sizeof(node));
    if (!n)
    {
        return NULL;
    }
    n->prev = NULL;
    n->value = value;
    return n;
}

int node_destroy (node * node)
{
    if (!node)
    {
        return 0;
    }
    node->prev = NULL;
    free(node);
    return 1;
}

Stack * stack_create (void)
{
    Stack * stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
    {
        return NULL;
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

int stack_destroy (Stack *stack)
{
    if (!stack)
    {
        return 0;
    }
    while (!stack_empty(stack))
    {
        stack_pop(stack);
    }
    free(stack);
    return 1;
}

int stack_top (Stack * stack)
{
    if (!stack || stack_empty(stack))
    {
        return -1;
    }

    return stack->top->value;
}

int stack_push (Stack * stack, char value)
{
    if (!stack)
    {
        return 0;
    }
    node * new = node_create(value);
    if (!new)
    {
        return 0;
    }
    new->prev = stack->top;
    stack->top = new;
    stack->size++;
    return 1;
}

int stack_pop (Stack * stack)
{
    if (!stack || stack_empty(stack))
    {
        return 0;
    }
    node * del = stack->top;
    stack->top = del->prev;
    stack->size--;
    node_destroy(del);
    return 1;
}

int stack_empty (Stack * stack)
{
    if (!stack || stack->size == 0)
    {
        return 1;
    }
    return 0;
}

unsigned int stack_size (Stack * stack)
{
    if (!stack)
    {
        return 0;
    }
    return stack->size;
}