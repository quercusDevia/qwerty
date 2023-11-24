#include "libmx.h"

char *mx_strjoin(const char*s1, const char*s2){
    if(s1 == NULL && s2 == NULL){
        return NULL;
    }
    else if(s1 == NULL){
        return mx_strdup(s2);
    }
    else if(s2 == NULL){
        return mx_strdup(s1);
    }
    else{
        int len1 = mx_strlen(s1);
        int len2 = mx_strlen(s2);
        char *result = mx_strnew(len1 + len2);

        result = mx_strncpy(result, s1, len1);
        result = mx_strcat(result, s2);

        return result;
    }
}

