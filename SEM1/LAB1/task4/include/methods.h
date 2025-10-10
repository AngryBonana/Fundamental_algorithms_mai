#ifndef METHODS_H
#define METHODS_H

#include "return_codes.h"

return_code dichotomy(double (*function) (const double, const double), const double a, const double b, const double e, double *ans);


return_code newtone(double (*func) (const double, const double), double (*func_d) (const double, const double), const double x0, const double e, double *ans);

#endif