#include "../include/findPrime.h"
#include <stdio.h>
#include <stdlib.h>


return_code findPrime (int *numbers, int *result, const int size, const int max)
{
    if (numbers == NULL || result == NULL)
    {
        return MEMORY_ERROR;
    }


    int *temp = (int *)malloc(sizeof(int) * (max + 1));

    if (temp == NULL)
    {
        return MEMORY_ERROR;
    }

    for (int i = 0; i <= max; i++) // Заполняем числами
    {
        temp[i] = i;
    }

    for (int i = 2; i <= max; i++) // Решето Эратосфена
    {
        if (temp[i] == 0) // Если уже 0,то пропускаем
        {
            continue;
        }

        for(int j = i + i; j <= max; j += i) // Проходимся по числам от i до max с шагом i, чтобы исключить кратные
        {
            if (temp[j] == 0) // Пропускаем уже обнуленные
            {
                continue;
            }

            if (j % i == 0) // Обнуляем, если кратное
            {
                temp[j] = 0;
            }
        }
    }

    int tmpSize = 100;
    int counter = 0;

    int * primeNums = (int *)malloc(sizeof(int) * tmpSize);

    if (primeNums == NULL)
    {
        return MEMORY_ERROR;
    }

    for (int i = 2; i<= max; i++) // Перекидываем ненулевые элементы
    {
        if (counter == tmpSize) {
            tmpSize *= 2;
            primeNums = (int *)realloc(primeNums, sizeof(int) * tmpSize);
        }

        if (temp[i] != 0)
        {
            primeNums[counter] = temp[i];
            counter++;
        }
    }
     // counter указывает на ячейку за последним добавленным элементом

    for (int i = 0; i < size; i++)
    {
        if (numbers[i] > counter)
        {
            result[i] = 0;
            continue;
        }

        result[i] = primeNums[numbers[i] - 1];
    }


    free(temp);
    free(primeNums);
    return OK;
}