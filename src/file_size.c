#include "file_size.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int file_size(char * file_name) {
    FILE *fp = fopen(file_name, "r");
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    fclose(fp);
    return size;
}

unsigned char has_extension(const char *filename, const char *ext) {
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) return 0;
    return strcmp(dot + 1, ext) == 0;
}

void trim(char *str) {
    char *start = str;
    char *end;

    while (isspace((unsigned char)*start)) {
        start++;
    }

    if (*start == 0) {
        str[0] = '\0';
        return;
    }

    memmove(str, start, strlen(start) + 1);

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    *(end + 1) = '\0';
}