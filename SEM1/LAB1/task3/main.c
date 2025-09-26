#include <stdio.h>
#include "include/functions.h"


int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("ERROR: Invalid Argument\nAt least flag is required\n");
        return INVALID_ARGUMENT;
    }

    char flag;
    if (flagValidation(argv[1], &flag) == INVALID_FLAG)
    {
        printf("ERROR: Invalid Flag\nFlag must start with '-' or '/'\nSupported: -m, -t, -q\n");
        return  INVALID_FLAG;
    }

    switch (flag) {
        case 'm':
            {
                if (argc != 4)
                {
                    printf("ERROR: Invalid Argument\nFlag -m required two integers\n");
                    return INVALID_ARGUMENT;
                }
                int n, m;
                return_code codeN = intValidation(argv[2], &n);
                return_code codeM = intValidation(argv[3], &m);
                if (codeN == INVALID_INTEGER || codeM == INVALID_INTEGER)
                {
                    printf("ERROR: Invalid Integer\nArguments must be integers\n");
                    return  INVALID_INTEGER;
                }

                if (m == 0)
                {
                    printf("ERROR: Invalid Integer\nSecond argument must be not 0\n");
                    return  INVALID_INTEGER;
                }

                if (codeN == INTEGER_OVERFLOW || codeM == INTEGER_OVERFLOW)
                {
                    printf("ERROR: Integer Overflow\nArgument is too big for integer\n");
                    return  INTEGER_OVERFLOW;
                }

                
                bool ans = multiplicity(n, m);
                if (ans)
                {
                    printf("Число %d кратно числу %d\n", n, m);
                }
                else
                {
                    printf("Число %d не кратно числу %d\n", n, m);
                }

            }
            break;


        case 't':
            {
                if (argc != 6)
                {
                    printf("ERROR: Invalid Argument\nFlag -t required four float arguments\n");
                    return INVALID_ARGUMENT;
                }

                float e, a, b, c; // Эпсилон и стороны

                return_code code_e = floatValidation(argv[2], &e);
                if (code_e == INVALID_FLOAT)
                {
                    printf("ERROR: Invalid Float\ne must be float more than 0 and less than 1\n");
                    return INVALID_FLOAT;
                }
                if (code_e == FLOAT_OVERFLOW)
                {
                    printf("ERROR: Float Overflow\nArgument must be float\n");
                    return FLOAT_OVERFLOW;
                }
                if (e <= 0 || e >= 1)
                {
                    printf("ERROR: Invalid Float\ne must be float more than 0 and less than 1\n");
                    return INVALID_FLOAT;
                }
                
                return_code code_a = floatValidation(argv[3], &a);
                return_code code_b = floatValidation(argv[4], &b);
                return_code code_c = floatValidation(argv[5], &c);
                if (code_a == INVALID_FLOAT || code_b == INVALID_FLOAT || code_c == INVALID_FLOAT)
                {
                    printf("ERROR: Invalid Float\nArguments must be float more than 0\n");
                    return INVALID_FLOAT;
                }
                if (code_a == FLOAT_OVERFLOW || code_b == FLOAT_OVERFLOW || code_c == FLOAT_OVERFLOW)
                {
                    printf("ERROR: Float Overflow\nArguments must be float\n");
                    return FLOAT_OVERFLOW;
                }
                if (a < 0 || b < 0 || c < 0)
                {
                    printf("ERROR: Invalid Argument\nArguments must be float more than 0\n");
                    return INVALID_FLOAT;
                }


                if (triangle(a, b, c, e))
                {
                    printf("Прямоугольный треугольник со сторонами %f, %f и %f существует\n", a, b, c);
                }
                else
                {
                    printf("Прямоугольный треугольник со сторонами %f, %f и %f не может существовать\n", a, b, c);

                }

            }
            break;
        case 'q':
            {
                if (argc != 6)
                {
                    printf("ERROR: Invalid Argument\nFlag -t required four float arguments\n");
                    return INVALID_ARGUMENT;
                }
                float e, a, b, c;

                return_code code_e = floatValidation(argv[2], &e);
                if (code_e == INVALID_FLOAT)
                {
                    printf("ERROR: Invalid Float\ne must be float more than 0 and less than 1\n");
                    return INVALID_FLOAT;
                }
                if (code_e == FLOAT_OVERFLOW)
                {
                    printf("ERROR: Float Overflow\nArgument must be float\n");
                    return FLOAT_OVERFLOW;
                }
                if (e <= 0 || e >= 1)
                {
                    printf("ERROR: Invalid Float\ne must be float more than 0 and less than 1\n");
                    return INVALID_FLOAT;
                }

                return_code code_a = floatValidation(argv[3], &a);
                return_code code_b = floatValidation(argv[4], &b);
                return_code code_c = floatValidation(argv[5], &c);
                if (code_a == INVALID_FLOAT || code_b == INVALID_FLOAT || code_c == INVALID_FLOAT)
                {
                    printf("ERROR: Invalid Float\nArguments must be float\n");
                    return INVALID_FLOAT;
                }
                if (code_a == FLOAT_OVERFLOW || code_b == FLOAT_OVERFLOW || code_c == FLOAT_OVERFLOW)
                {
                    printf("ERROR: Float Overflow\nArguments must be float\n");
                    return FLOAT_OVERFLOW;
                }
                double ans1, ans2;
                solution_code code_ans;

                code_ans = quadro(a, b, c, e, &ans1, &ans2);
                printAnswer(code_ans, a, b, c, ans1, ans2);

                code_ans = quadro(a, c, b, e, &ans1, &ans2);
                printAnswer(code_ans, a, c, b, ans1, ans2);

                code_ans = quadro(b, a, c, e, &ans1, &ans2);
                printAnswer(code_ans, b, a, c, ans1, ans2);

                code_ans = quadro(b, c, a, e, &ans1, &ans2);
                printAnswer(code_ans, b, c, a, ans1, ans2);

                code_ans = quadro(c, b, a, e, &ans1, &ans2);
                printAnswer(code_ans, c, b, a, ans1, ans2);

                code_ans = quadro(c, a, b, e, &ans1, &ans2);
                printAnswer(code_ans, c, a, b, ans1, ans2);
            }
            break;


        default:
           printf("ERROR: Invalid Flag\nSupported flags: -m, -t, -q\n");
            return  INVALID_FLAG; 
    }

    return 0;
}