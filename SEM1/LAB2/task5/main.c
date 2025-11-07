#include <stdio.h>
#include <string.h>
#include "include/transfer.h"

int main (void) 
{
    char input_path[1024];
    char output_path[1024];

    printf("Input input_filename: ");
    if (!fgets(input_path, sizeof(input_path), stdin)) {
        printf("Can't read input filename\n");
        return 1;
    }
    input_path[strcspn(input_path, "\n")] = 0; // удаляем \n

    printf("Input output_filename: ");
    if (!fgets(output_path, sizeof(output_path), stdin)) {
        printf("Can't read input filename\n");
        return 1;
    }
    output_path[strcspn(output_path, "\n")] = 0;

    FILE *in = fopen(input_path, "r");
    if (!in) {
        printf("Can't open input file");
        return 1;
    }

    FILE *out = fopen(output_path, "w");
    if (!out) {
        printf("Can't open input file");
        fclose(in);
        return 1;
    }

    return_code code = transfer(in, out);
    switch (code) 
    {
        case OK:
        printf("DONE!\n");
        break;
        case WRONG_PTR:
        printf("ERROR: Wrong ptr!\n");
        break;
        case MEMORY_ERROR:
        printf("ERROR: Memory error!\n");
        break;
        case WRITING_ERROR:
        printf("ERROR: Writing error!\n");
        break;
        default:
        printf("Unexpected error!\n");
        break;
    }
    
    fclose(in);
    fclose(out);
    return code;
}