#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>


typedef VECTOR_TYPE (*CopyFuncType)(VECTOR_TYPE);
typedef void (*DeleteFuncType)(VECTOR_TYPE);

typedef struct {
    VECTOR_TYPE *data;
    size_t size;
    size_t capacity;
    CopyFuncType CopyVoidPtr;
    DeleteFuncType DeleteVoidPtr;
} Vector;



static void resize_if_needed(Vector *v)
{
    if (v->size >= v->capacity)
    {
        size_t new_capacity = (v->capacity == 0) ? 1 : v->capacity * 2;
        VECTOR_TYPE *new_data = realloc(v->data, new_capacity * sizeof(VECTOR_TYPE));
        if (!new_data)
        {
            exit(EXIT_FAILURE);
        }
        v->data = new_data;
        v->capacity = new_capacity;
    }
}

Vector create_vector(size_t initial_capacity, CopyFuncType CopyFunc, DeleteFuncType DeleteFunc) 
{
    Vector v;
    v.data = NULL;
    v.size = 0;
    v.capacity = 0;
    v.CopyVoidPtr = CopyFunc;
    v.DeleteVoidPtr = DeleteFunc;

    if (initial_capacity > 0)
    {
        v.data = malloc(initial_capacity * sizeof(VECTOR_TYPE));
        if (!v.data) 
        {
            exit(EXIT_FAILURE);
        }
        v.capacity = initial_capacity;
    }

    return v;
}

void erase_vector(Vector *v)
{
    if (!v || !v->data) 
    {
        return;
    }
    for (size_t i = 0; i < v->size; ++i) 
    {
        v->DeleteVoidPtr(v->data[i]);
    }
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

int is_equal_vector(const Vector *v1, const Vector *v2)
{
    if (!v1 || !v2)
    {
        return -1;
    }
    if (v1->size != v2->size) 
    {
        return 0;
    }
    if (!v1->data || !v2->data)
    {
        return -1;
    }

    for (size_t i = 0; i < v1->size; ++i)
    {
        if (v1->data[i] != v2->data[i]) return 0;
    }
    return 1;
}

void copy_vector(Vector *dest, const Vector *src)
{
    if (!dest || !src) 
    {
        return;
    }
    erase_vector(dest);

    dest->CopyVoidPtr = src->CopyVoidPtr;
    dest->DeleteVoidPtr = src->DeleteVoidPtr;

    if (src->size == 0) 
    {
        return;
    }

    dest->capacity = src->capacity;
    dest->data = malloc(dest->capacity * sizeof(VECTOR_TYPE));

    if (!dest->data) 
    {
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < src->size; ++i) 
    {
        dest->data[i] = dest->CopyVoidPtr(src->data[i]);
    }
    dest->size = src->size;
}

Vector *copy_vector_new(const Vector *src)
{
    Vector *new_vec = malloc(sizeof(Vector));
    if (!new_vec) 
    {
        exit(EXIT_FAILURE);
    }
    *new_vec = create_vector(0, src->CopyVoidPtr, src->DeleteVoidPtr);
    copy_vector(new_vec, src);
    return new_vec;
}

void push_back_vector(Vector *v, VECTOR_TYPE value)
{
    resize_if_needed(v);
    v->data[v->size] = v->CopyVoidPtr(value);
    v->size++;
}

void delete_at_vector(Vector *v, size_t index)
{
    if (!v || index >= v->size) 
    {
        return;
    }

    v->DeleteVoidPtr(v->data[index]);

    for (size_t i = index; i < v->size - 1; ++i)
    {
        v->data[i] = v->data[i + 1];
    }

    v->size--;

}

VECTOR_TYPE get_at_vector(const Vector *v, size_t index)
{
    if (!v || index > v->size)
    {
        printf("ERROR: Index out of range!\n");
        exit(EXIT_FAILURE);
    }
    return v->data[index];
}

void delete_vector(Vector *v)
{
    if (!v) 
    {
        return;
    }
    erase_vector(v);
}
void delete_vector(Vector *v);

#endif