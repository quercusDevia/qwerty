#include "libmx.h"

char *mx_strndup(const char *s1, size_t n){
    size_t length = mx_strlen(s1);

    if(length > n){
        length = n;
    }

    char* arr = mx_strnew(length);
    mx_strncpy(arr, s1, n);
    return arr;
}
