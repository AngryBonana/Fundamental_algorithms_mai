#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/findPrime.h"



int main (void)
{
    int repeats = 0;
    int numToFind = 0;
    const int max = 100000000;
    



    printf("Введите количество чисел: ");
    scanf("%d", &repeats);

    

    if (repeats <= 0 || repeats > 1000) {
        printf("ERROR: Ivalid Input\nNumber must be more than 0 and less than 1001\n");
        return INVALID_INPUT;
    }

    int *numbers = (int *)malloc(sizeof(int) * repeats); // Под номера

    if (numbers == NULL)
    {
        printf("ERROR: Memory Error\nProgram can not use memory\n");
        return MEMORY_ERROR;
    }

    int *result = (int *)malloc(sizeof(int) * repeats); // Под ответы

    if (result == NULL)
    {
        printf("ERROR: Memory Error\nProgram can not use memory\n");
        return MEMORY_ERROR;
    }

    printf("Введите %d номера(ов):\n", repeats);
    for (int i = 0; i < repeats; i++)
    {
        scanf("%d", &numToFind);
        if (numToFind <= 0)
        {
            printf("ERROR: Invalid Input\nInteger must be more than 0\n");
            return INVALID_INPUT;
        }
        numbers[i] = numToFind;
    }

    printf("Обработка запроса...\n");
    if (findPrime(numbers, result, repeats, max) == MEMORY_ERROR)
    {
        printf("ERROR: Memory Error\nProgram can not use memory\n");
        return MEMORY_ERROR;
    }

    for (int i = 0; i < repeats; i++)
    {   
        if (result[i] == 0)
        {
            printf("Простое число номер %d слишком большое\n", numbers[i]);
            continue;
        }
        printf("Простое число номер %d равно %d\n", numbers[i], result[i]);
    }

    free(numbers);
    free(result);

    return 0;
}