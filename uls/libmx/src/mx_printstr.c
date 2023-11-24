#include "libmx.h"

void mx_printstr(const char* s){
   int n = mx_strlen(s);
       write(1, s, n);
}

