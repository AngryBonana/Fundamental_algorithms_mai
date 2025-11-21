#ifndef STACK_H
#define STACK_H

typedef struct _node {
    char value;
    struct _node * prev;
} node;

typedef struct {
    unsigned int size;
    node * top;
} Stack;

node * node_create (char value);

int node_destroy (node * node);

Stack *  stack_create (void);

int stack_destroy (Stack *stack);

int stack_top (Stack * stack);

int stack_push (Stack * stack, char value);

int stack_pop (Stack * stack);

int stack_empty (Stack * stack);

unsigned int stack_size (Stack * stack);


#endif