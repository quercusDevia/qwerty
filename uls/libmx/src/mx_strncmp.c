#include "libmx.h"

int mx_strncmp(const char* s1, const char* s2, int n) {
    if(n == 0){
        return 0;
    }

    

    for (int i = 0; i < n; i++) {
        if (*s1 != *s2) {
            return (*(unsigned char*)s1 - *(unsigned char*)s2);
        }
	s1++;
	s2++;
    }
    return 0;
}

