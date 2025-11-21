#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_TYPE int
#include "include/Vector.h"

int copy_int(int x)
{
    return x;
}

void delete_int(int x)
{
    return;
}

void print_vector(const Vector *v, const char *label) {
    printf("%s: [", label);
    for (size_t i = 0; i < v->size; ++i) {
        printf("%d", v->data[i]);
        if (i < v->size - 1) printf(", ");
    }
    printf("] (size=%zu, cap=%zu)\n", v->size, v->capacity);
}

int main(void) {
    printf("Создание\n");
    Vector v = create_vector(0, copy_int, delete_int);
    print_vector(&v, "Пустой вектор");

    printf("Добавление элементов\n");
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    push_back_vector(&v, 40);
    print_vector(&v, "После добавления 10,20,30,40");

    printf("Получение элемента по индексу\n");
    printf("Элемент [2] = %d\n", get_at_vector(&v, 2));

    printf("Удаление элемента по индексу\n");
    delete_at_vector(&v, 1);
    print_vector(&v, "После удаления индекса 1");

    printf("Создание копии вектора\n");
    Vector v2 = create_vector(0, copy_int, delete_int);
    copy_vector(&v2, &v);
    print_vector(&v2, "Копия v2");

    printf("Сравнение векторов\n");
    printf("v == v2 ? %s\n", is_equal_vector(&v, &v2) ? "true" : "false");

    printf("Изменяем v2 и снова сравниваем\n");
    push_back_vector(&v2, 999);
    print_vector(&v2, "v2 после добавления 999");
    printf("v == v2 ? %s\n", is_equal_vector(&v, &v2) ? "true" : "false");

    printf("Динамическое копирование (copy_vector_new)\n");
    Vector *v3 = copy_vector_new(&v);
    print_vector(v3, "v3");
    printf("v == v3 ? %s\n", is_equal_vector(&v, v3) ? "true" : "false");

    printf("Очистка содержимого вектора\n");
    erase_vector(&v2);
    print_vector(&v2, "v2 после erase");

    printf("Освобождение памяти\n");
    delete_vector(&v);
    delete_vector(&v2);
    delete_vector(v3); 
    free(v3); 

    return 0;
}