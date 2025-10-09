#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "return_codes.h"
#include "stdbool.h"

bool validation(int base, char *str);

return_code convert_to_dec(char *str, const int base, long long *ans);

char * convert_to_base(long long num, const int base);

bool stopCheck(char *str);

return_code findMax(long long *nums, const unsigned int size, long long *ans);

#endif