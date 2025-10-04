#include <stdbool.h>
#include <stdio.h>

typedef enum {
    OK,
    ARGUMENT_ERROR,
    INVALID_FLAG,
    INVALID_PATH,
    MEMORY_ERROR,
    NULL_PTR
} return_code;


return_code flagValidation (char *str, bool *n_flag, char *flag);

return_code createName (char *str, char **name);