#include "../include/functions.h"
#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>


return_code flagValidation(char * forValidation, char * flag)
{
    if ((forValidation[0] != '-' && forValidation[0] != '/') || forValidation[1] == '\0' || forValidation[2] != '\0')
    {
        return INVALID_FLAG;
    }
    *flag = forValidation[1];
    return OK;
}


return_code intValidation(char *str, int *num)
{
    bool minusFlag = false;
    long long tmp = 0;
    if (*str == '-')
    {
        minusFlag = true;
    }
    else 
    {
        tmp = *str - '0';
        if (tmp < 0 || tmp > 9)
        {
            return INVALID_INTEGER;
        }
        if (tmp == 0 && *(str + 1) != '\0')
        {
            return INVALID_INTEGER;

        }
    }

    for (int i = 1; *(str + i) != '\0'; i++)
    {
        switch (*(str + i)) {
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
                break;
            default:
                return INVALID_INTEGER;
                break;
        }
        
        tmp = tmp * 10 + (*(str + i) - '0');
        if (-1 * tmp < INT_MIN)
        {
            return INTEGER_OVERFLOW;
        }
        if (tmp == 0)
        {
            return INVALID_INTEGER;
        }
    }

    if (minusFlag)
    {
        tmp *= -1;
    }

    if (INT_MIN > tmp || tmp > INT_MAX)
    {
        return INTEGER_OVERFLOW;
    }
    else 
    {
        *num = tmp;
    }

    return OK;
}


return_code floatValidation(char *str, float *num)
{
    bool minusFlag = false;
    bool dot = false;
    int dotCounter = 0;
    double tmp = 0;
    char ch = *str;
    switch (ch) { // Обрабатываем первый символ
        case '-':
            minusFlag = true;
            if (*(str + 1) == '\0')
            {
                return INVALID_FLOAT;
            }
            break;
        case '.':
            dot = true;
            dotCounter = 1;
            break;
        case '0':
            if (*(str + 1) != '.' && *(str + 1) != '\0')
            {
                return INVALID_FLOAT;
            }
            tmp = 0;
            break;
        default:
            tmp = ch - '0';
            if (tmp < 0 || tmp > 9)
            {
                return INVALID_FLOAT;
            }
            break;
    }


    for (int i = 1; *(str + i) != '\0'; i++)
    {
        ch = *(str + i);
        switch (ch) {
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
                break;
            case '.':
                if (dot)
                {
                    return INVALID_FLOAT;
                }
                dot = true;
                dotCounter = 1;
                continue;

            default:
                return INVALID_FLOAT;
                break;
        }

        if (dot)
        {
            tmp = tmp + (ch - '0') * pow(0.1, dotCounter);
            dotCounter++;
        }
        else 
        {
            tmp = tmp * 10 + ch - '0';
        }

        if (tmp > FLT_MAX)
        {
            return FLOAT_OVERFLOW;
        }
    }

    if (minusFlag)
    {
        tmp *= -1;
    }

    *num = tmp;

    return OK;
}


bool multiplicity(const int num1, const int num2)
{
    return (num1 % num2 == 0);
}

bool triangle(const float a, const float b, const float c, const float e)
{

    double da = a, db = b, dc = c;
    double maximum = fmax(da, db);
    maximum = fmax(maximum, dc);
    if (fabs(2 * maximum * maximum - da * da - db * db - dc * dc) < e)
    {
        return true;
    }
    return false;
}


solution_code quadro(const float a, const float b, const float c, const float e, double *ans1, double *ans2)
{
    double da = a, db = b, dc = c;
    if(fabs(da) < e && fabs(db) < e && fabs(dc) < e)
    {
        return INFINITY_SOLUTION;
    }
    if(fabs(da) < e && fabs(db) < e)
    {
        return NO_SOLUTION;
    }
    if(fabs(da) < e)
    {
        *ans1 = -1 * dc / db;
        return ONE_SOLUTION;
    }

    double discriminant = db * db - 4 * da * dc;
    if(fabs(discriminant) < e) // Дискриминант равен 0
    {
        *ans1 = (-1 * db) / (2 * da);
        return ONE_SOLUTION;
    }
    if(discriminant < 0)
    {
        return NO_SOLUTION;
    }

    *ans1 = (-1 * db - sqrt(discriminant)) / (2 * da);
    *ans2 = (-1 * db + sqrt(discriminant)) / (2 * da);
    return TWO_SOLUTION;
}


void printAnswer(solution_code code_ans, const float a, const float b, const float c, const double ans1, const double ans2)
{
    printf("Уравнение с коэффициентами %f, %f, %f ", a, b, c);

                switch (code_ans) {
                    case NO_SOLUTION:
                        printf("не имеет решения ");
                        break;
                    case INFINITY_SOLUTION:
                        printf("имеет бесконечно много решений ");
                        break;
                    case ONE_SOLUTION:
                        printf("имеет корень %lf ", ans1);
                        break;
                    case TWO_SOLUTION:
                        printf("имеет два корня %lf и %lf ", ans1, ans2);
                        break;
                }
    printf("при заданном e\n\n");
}


int permutations(float *ans, const double a, const double b, const double c, const double e)
{
    int combinations = 1;
    ans[0] = a;
    ans[1] = b;
    ans[2] = c;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
            {
                continue;
            }
            for (int k = 0; k < 3; k++)
            {
                if (k == i || k == j)
                {
                    continue;
                }
                for (int p = 0; p < combinations; p++)
                {
                    if (fabs(ans[0 + p * 3] - ans[i]) < e && fabs(ans[1 + p * 3] - ans[j]) < e && fabs(ans[2 + p * 3] - ans[k]) < e)
                    {
                        break;
                    }
                    if (p == combinations - 1)
                    {
                        ans[0 + 3 * combinations] = ans[i];
                        ans[1 + 3 * combinations] = ans[j];
                        ans[2 + 3 * combinations] = ans[k];
                        combinations++;
                        break;
                    }
                }
                
            }
        }
    }

    return combinations;
}