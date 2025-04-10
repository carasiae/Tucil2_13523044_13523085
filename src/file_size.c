#include "file_size.h"
#include <stdint.h>

#include <stdio.h>

int file_size(char * file_name) {
    FILE *fp = fopen(file_name, "r");
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    fclose(fp);
    return size;
}