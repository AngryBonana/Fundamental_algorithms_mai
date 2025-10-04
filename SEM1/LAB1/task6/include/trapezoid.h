#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "return_codes.h"


return_code trapezoid(double (*func) (double, const double), const double a, const double b, double *ans, const double e);

#endif