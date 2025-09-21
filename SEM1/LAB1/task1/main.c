#include <stdio.h>
#include "include/functions.h"


int main(int argc, char *argv[])
{
    int num = 0; // Введенное пользователем число
    char flag; // Флаг
    
    // Валидация количества аргументов командной строки
    if (argc != 3)
    {
        printf("ERROR: Invalid Input\nUsing: ./program <num> <flag>\n");
        return INVALID_INPUT;
    }

    // Валидация числа
    switch (numValidation(argv[1], &num)) {
        case INVALID_NUMBER:
            printf("ERROR: Invalid Number\nFirst argument must be integer\n");
            return INVALID_NUMBER;
        case INT_OVERFLOW:
            printf("ERROR: Int Overflow\nToo big integer\n");
            return INT_OVERFLOW;
        default:
            break;
    }

    // Валидация флага
    if (flagValidation(argv[2], &flag) != OK)
    {
        printf("ERROR: Invalid Flag\nMust starts with '-' or '/'\nSupported: -h, -p, -s, -e, -a, -f\n");
        return INVALID_FLAG;
    }

    switch (flag) {
        // Флаг -h (Кратные числа в пределах 100)
        case 'h':
            if (num > 100 || num < 1)
            {
                printf("ERROR: Ivalid Number\nInteger must be more than 0 and less than 101\n");
                return INVALID_NUMBER;
            }
            printf("Кратные числа %d: ", num);
            int tmp = num;
            while (tmp <= 100)
            {
                printf("%d ", tmp);
                tmp += num;
            }
            printf("\n");
            break;
        
        // Флаг -p (Проверка на простоту)
        case 'p':
            if (num < 1)
            {
                printf("ERROR: Ivalid Number\nInteger must be more than 0\n");
                return INVALID_NUMBER;
            }

            if (num == 1)
            {
                printf("Число 1 ни простое, ни составное\n");
                break;
            }            

            if (isPrime(num))
            {
                printf("Число %d простое\n", num);
            }
            else 
            {
                printf("Число %d составное\n", num);
            }
            break;
            
        // Флаг -a (Сумма чисел от 1 до num)
        case 'a':
            if (num < 1)
            {
                printf("ERROR: Ivalid Number\nInteger must be more than 0\n");
                return INVALID_NUMBER;
            }

            long long sum = sumOfElemts(num);
            printf("Сумма чисел от 1 до %d равна %lld\n", num, sum);
            break;

        // Флаг -f (Факториал числа)
        case 'f':
            if (num < 0)
            {
                printf("ERROR: Ivalid Number\nInteger must be more than -1\n");
                return INVALID_NUMBER;
            }
            int ans = 1;

            if (factorial(&ans, num) == INT_OVERFLOW)
            {
                printf("ERROR: Int Overflow\nAnswer is too big. Try number lower than that\n");
                return INT_OVERFLOW;
            }
            printf("Факториал числа %d равен %d\n", num, ans);
            break;

        // Перевод в 16 систему счисления и вывод по разрядам
        case 's':
            if (num < 0)
            {
                num *= -1;
                printf("- ");
            }
            char digits[8] = {};
            int position = hexanalization(digits, num);
            for (int i = position; i < 8; i++)
            {
                printf("%c ", digits[i]);
            }
            printf("\n");
            break;

        // Вывод таблицы степеней для чисел от 1 до 10, степени от 1 до num, num <= 10
        case 'e':
            if (num <= 0 || num > 10)
            {
                printf("ERROR: Ivalid Number\nInteger must be more than 0 and less than 11\n");
                return INVALID_NUMBER;
            }
            long long nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            printf("| %-2lld | %-4lld | %-5lld |  %-7lld | %-7lld | ", nums[0], nums[1], nums[2], nums[3], nums[4]);
            printf("%-8lld | %-9lld | %-10lld | %-10lld | %-11lld |\n", nums[5], nums[6], nums[7], nums[8], nums[9]);
            for (int i = 2; i <= num; i++)
            {   
                powNums(nums);
                printf("| %-2lld | %-4lld | %-5lld |  %-7lld | %-7lld | ", nums[0], nums[1], nums[2], nums[3], nums[4]);
                printf("%-8lld | %-9lld | %-10lld | %-10lld | %-11lld |\n", nums[5], nums[6], nums[7], nums[8], nums[9]);
            }
    }

    return 0;
}