#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n){
    unsigned char *result = (unsigned char *)s;
    size_t count = 0;

    while(count != n){
        if(*result == (unsigned char)c){
	    return result;
	}
	count++;
	result++;
    }

    return NULL;
}

