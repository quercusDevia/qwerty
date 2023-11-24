#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n){
    unsigned char *result = (unsigned char *)s + mx_strlen(s);
    size_t count = n;

    while(count >= 0){
        if(*result == (unsigned char)c){
            return result;
        }
        count--;
        result--;
    }

    return NULL;

}

