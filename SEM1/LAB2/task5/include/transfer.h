#ifndef TRANSFER_H
#define TRANSFER_H
#include <stdio.h>


typedef enum{
    OK,
    WRONG_PTR,
    MEMORY_ERROR,
    WRITING_ERROR,
    END
} return_code;


return_code transfer (FILE * input_file, FILE * output_file);


#endif