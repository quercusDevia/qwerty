#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr){
    char *arr = mx_strnew(20);
   
    if(nbr == 0){
        arr[0] = '0';
	return arr;
    }

    int length = 0;
    int i = 0;

    while (nbr != 0){
        int n = nbr % 16;
	
	if (n < 10){
            arr[i] = n + 48;
	    i++;
	}
	else {
	    arr[i] = n + 87;
	    i++;
	}
	length++;
	nbr /= 16;
    }
	    
    
    if (length < 1){
        return NULL;
    }

    char *result = mx_strnew(length);

    for(int i = 0; i < length; i++){
        result[i] = arr[length - i - 1];
    }

    return result;
}

