#include <stdio.h>
#include "include/exponent.h"
#include "include/pi.h"
#include "include/log.h"
#include "include/sqrt.h"
#include "include/gamma.h"



int main (void)
{
    const double e = 1e-8;

    printf("Вычисление экспоненты:\n");
    double exp = exp_lim(e);
    printf("Как предел: %.8lf\n", exp);
    exp = exp_sum(e);
    printf("Как ряд: %.8lf\n", exp);
    exp = exp_eq(e);
    printf("Как решение уравнения: %.8lf\n\n", exp);

    printf("Вычисление числа пи:\n");
    double pi = pi_lim(e);
    printf("Как предел: %.8lf\n", pi);
    pi = pi_sum(e);
    printf("Как ряд: %.8lf\n", pi);
    pi = pi_eq(e);
    printf("Как решение уравнения: %.8lf\n\n", pi);

    printf("Вычисление ln2:\n");
    double ln2 = log_lim(e);
    printf("Как предел: %.8lf\n", ln2);
    ln2 = log_sum(e);
    printf("Как ряд: %.8lf\n", ln2);
    ln2 = log_eq(e);
    printf("Как решение уравнения: %.8lf\n\n", ln2);

    printf("Вычисление sqrt(2):\n");
    double sqrt2 = sqrt_lim(e);
    printf("Как предел: %.8lf\n", sqrt2);
    sqrt2 = sqrt_mult(e);
    printf("Как произведение: %.8lf\n", sqrt2);
    sqrt2 = sqrt_eq(e);
    printf("Как решение уравнения: %.8lf\n\n", sqrt2);

    printf("Вычисление постоянной Эйлера:\n");
    double gamma = gamma_lim(e);
    printf("Как предел: %.8lf\n", gamma);
    gamma = gamma_sum(e, pi_sum(e));
    printf("Как ряд: %.8lf\n", gamma);
    gamma = gamma_eq(e);
    printf("Как решение уравнения: %.8lf\n\n", gamma);

    return 0;
}