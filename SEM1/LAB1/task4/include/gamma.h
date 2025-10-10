#ifndef GAMMA_H
#define GAMMA_H

#include "return_codes.h"

return_code gamma_lim(const double e, double *ans);

double gamma_sum(const double e, const double pi);

double gamma_eq(const double x, const double e);

double gamma_eq_d(const double x, const double e);

#endif