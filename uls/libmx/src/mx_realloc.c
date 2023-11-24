#include "libmx.h"

void *mx_realloc(void *ptr, size_t size){
    if(!ptr){
        return malloc(size);
    }

    if(size == 0){
	free(ptr);
        return NULL;
    }

    size_t ptr_size = malloc_size(ptr);

    void *temp = malloc(size);
    temp = mx_memcpy(temp, ptr, ptr_size);
    free(ptr);
    return temp;
}

