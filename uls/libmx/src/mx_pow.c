#include "libmx.h"

double mx_pow(double n, unsigned int pow){
    double b = 1;

    for(unsigned int i = 0; i < pow; i++ ){
        b *= n;
    }

    return b;
}

