#include "libmx.h"

int mx_strlen(const char *s){
  
    int a = 0;

    for(int i = 0; s[i] != '\0'; i++){
       a++;
    }

    return a;
}

