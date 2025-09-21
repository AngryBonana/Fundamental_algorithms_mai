#include <stdbool.h>
#include <limits.h>
#include "../include/functions.h"




// Валидация числа
return_code numValidation(char *str, int *num)
{   
    char tmp = *str;
    long long input = 0;
    bool minus = false;

    if (tmp == '-')
    {
        minus = true;
        str++;
        tmp = *str;
    }

    if (tmp == '0' && *(str + 1) != '\0')
    {
        return INVALID_NUMBER;
    }

    while (tmp != '\0')
    {
        switch (tmp) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                // Сдвигаем разряды влево и прибавляем код цифры минус код нуля
                input = input * 10 + tmp - '0';
                if (input > INT_MAX)
                {
                    return INT_OVERFLOW;
                }
                break;
            default:
                return INVALID_NUMBER;
        }
        
        str++;
        tmp = *str;
    }
    if (minus)
    {
        input *= -1;
    }
    *num = input;
    return OK;
}


//Валидация флага
return_code flagValidation(char *str, char *c)
{
    char tmp = *str;
    if ((!(tmp == '-') && !(tmp == '/')) || *(str + 2) != '\0') // Если первый символ не - или / или если третий символ не конец строки
    {
        return INVALID_FLAG;
    }

    tmp = *(str + 1);
    switch (tmp) {
        case 'h':
        case 'p':
        case 's':
        case 'e':
        case 'a':
        case 'f':
            *c = tmp;
            return OK;
        default:
            return INVALID_FLAG;
    }
}


// Факториал числа
return_code factorial(int *ans, int num)
{
    long long fact = 1;
    if (num == 0 || num == 1)
    {
        *ans = fact;
        return OK;
    }

    for (int i = 2; i <= num; i++)
    {
        fact *= i;
        if  (fact > INT_MAX)
        {
            return INT_OVERFLOW;
        }
    }

    *ans = fact;

    return OK;
}


// Сумма элементов от 1 до num
long long sumOfElemts(int num)
{
    long long ans = (1 + num) * num / 2;
    return  ans;
}



// Проверка на простоту
bool isPrime(int num)
{
    for (int i = 2; i * i < num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }

    return true;
}


// Перевод числа в 16 систему счисления с разбиением по разрядам
int hexanalization(char digits[], int num)
{
    int i = 0;
    int tmp = 0;
    if (num == 0)
    {
        digits[7] = '0';
    }
    while (num != 0)
    {   
        tmp = num % 16;
        num = num / 16;

        if (tmp < 10)
        {
            digits[7 - i] = tmp + '0';
        }
        else
        {
            digits[7 - i] = tmp % 10 + 'A';
        }

        i++;
        
    }
    return 7 - (i - 1);
}


// Возведение в степень чисел от 1 до 10
// Домножает каждое число на 1, 2, ... 10 в зависимости от положения
void powNums(long long nums[])
{
    for (int i = 1; i <= 10; i++)
    {
        nums[i - 1] *= i;
    }
}