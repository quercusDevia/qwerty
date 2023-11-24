#include "libmx.h"

int mx_atoi(char* str){
  int i = -1;
    long result = 0;

    while (str[++i]) {
        if (mx_isdigit(str[i]))
            result = result * 10 + str[i] - '0';
        if (!mx_isdigit(str[i]))
            return result;
    }
    return result;
}
