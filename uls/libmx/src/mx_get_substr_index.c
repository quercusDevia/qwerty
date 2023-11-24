#include "libmx.h"

int mx_get_substr_index(const char *str, const char*sub){
    if(!str){
        return -2;
    }
    else if(!mx_strstr(str, sub)){
        return -1;
    } 

    return mx_strstr(str, sub) - str;
}

