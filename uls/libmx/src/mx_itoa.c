#include "libmx.h"

char *mx_itoa(int number){
    int sizenum = 0;
    int ncop = number;

    while (ncop != 0){
        if (ncop < 0){
	    sizenum++;
	    ncop *= -1;
	}
	sizenum ++;
	ncop /= 10;
    }
    if (number == 0){
        sizenum = 1;
    }
    char *a = mx_strnew(sizenum);

    if (number == 0){
        a[0] = 48;
    }

    for (int i = sizenum; number != 0; i--){
        if (number < 0){
	    a[0] = 45;
	    number *= -1;
	}
	
	a[i - 1] = (number % 10) + 48;
	number /= 10;
    }

    return a;
}

