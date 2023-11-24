#include "libmx.h"

char* mx_strdup(const char *str){
    int size = mx_strlen(str);
    char* arr = mx_strnew(size);
    mx_strcpy(arr, str);
    return arr;
}

