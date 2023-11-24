#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2){
    int length1 = mx_strlen(s1);
    int length2 = mx_strlen(s2);
    int size = length1 + length2;

    for(int i = length1, j = 0; i < size; i++, j++){
        s1[i] = s2[j];
    }

    return s1;
}

