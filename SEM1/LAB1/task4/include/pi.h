#ifndef PI_H
#define PI_H

#include "return_codes.h"

return_code pi_lim(const double e, double *ans);

double pi_sum(const double e);

double pi_eq(const double x, const double e);

double pi_eq_d(const double x, const double e);

#endif
