#include <stdio.h>
#include "include/exponent.h"
#include "include/pi.h"
#include "include/log.h"
#include "include/return_codes.h"
#include "include/sqrt.h"
#include "include/gamma.h"
#include "include/methods.h"



int main (void)
{
    const double e = 1e-7;

    printf("Вычисление экспоненты:\n");
    double exp = exp_lim(e);
    printf("Как предел: %.8lf\n", exp);
    exp = exp_sum(e);
    printf("Как ряд: %.8lf\n", exp);
    printf("Как решение уравнения: ");
    switch (dichotomy(exp_eq, 1, 3, e, &exp)) {
        case OK:
        {
            printf("%.8f\n\n", exp);
        }
        break;
        case ACCURACY_ERROR:
        {
            printf("Не получилось достичь заданной точности, последнее значение: %.8f\n\n", exp);
        }
        break;
        case BAD_BOUNDARY:
        {
            printf("Неправильно указаны границы\n\n");
        }
        break;
    }

    printf("Вычисление числа пи:\n");
    double pi = pi_lim(e);
    printf("Как предел: %.8lf\n", pi);
    pi = pi_sum(e);
    printf("Как ряд: %.8lf\n", pi);
    printf("Как решение уравнения: ");
    switch (newtone(pi_eq, pi_eq_d, 3.1, e, &pi)) {
        case OK:
        {
            printf("%.8f\n\n", pi);
        }
        break;
        case ACCURACY_ERROR:
        {
            printf("Не получилось достичь заданной точности, последнее значение: %.8f\n\n", pi);
        }
        break;
        case BAD_BOUNDARY:
        {
            printf("Неправильно указаны границы\n\n");
        }
        break;
    }

    printf("Вычисление ln2:\n");
    double ln2 = log_lim(e);
    printf("Как предел: %.8lf\n", ln2);
    ln2 = log_sum(e);
    printf("Как ряд: %.8lf\n", ln2);
    printf("Как решение уравнения: ");
    switch (dichotomy(log_eq, 0, 2, e, &ln2)) {
        case OK:
        {
            printf("%.8f\n\n", ln2);
        }
        break;
        case ACCURACY_ERROR:
        {
            printf("Не получилось достичь заданной точности, последнее значение: %.8f\n\n", ln2);
        }
        break;
        case BAD_BOUNDARY:
        {
            printf("Неправильно указаны границы\n\n");
        }
        break;
    }

    printf("Вычисление sqrt(2):\n");
    double sqrt2 = sqrt_lim(e);
    printf("Как предел: %.8lf\n", sqrt2);
    sqrt2 = sqrt_mult(e);
    printf("Как произведение: %.8lf\n", sqrt2);
    printf("Как решение уравнения: ");
    switch (dichotomy(sqrt_eq, 1, 3, e, &sqrt2)) {
        case OK:
        {
            printf("%.8f\n\n", sqrt2);
        }
        break;
        case ACCURACY_ERROR:
        {
            printf("Не получилось достичь заданной точности, последнее значение: %.8f\n\n", sqrt2);
        }
        break;
        case BAD_BOUNDARY:
        {
            printf("Неправильно указаны границы\n\n");
        }
        break;
    }

    printf("Вычисление постоянной Эйлера:\n");
    double gamma = gamma_lim(e);
    printf("Как предел: %.8lf\n", gamma);
    gamma = gamma_sum(e, pi_sum(e));
    printf("Как ряд: %.8lf\n", gamma);
    printf("Как решение уравнения: ");
    switch (newtone(gamma_eq, gamma_eq_d, 0.5, e, &gamma)) {
        case OK:
        {
            printf("%.8f\n\n", gamma);
        }
        break;
        case ACCURACY_ERROR:
        {
            printf("Не получилось достичь заданной точности, последнее значение: %.8f\n\n", gamma);
        }
        break;
        case BAD_BOUNDARY:
        {
            printf("Неправильно указаны границы\n\n");
        }
        break;
    }

    return 0;
}