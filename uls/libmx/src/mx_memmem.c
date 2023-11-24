#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len){
    if(big_len < little_len || little_len == 0){
        return NULL;
    }

    const char *bi = (const char*)big;
    const char *li = (const char*)little;

    for(size_t i = 0; i <= big_len - little_len; ++i){
        if(mx_memcmp(bi, li, little_len - 1) == 0){
	    return (void*)(bi);
	}
	bi++;
    }

    return NULL;
}

