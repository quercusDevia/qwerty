#include "libmx.h"

void mx_printint(int n){
    if(n < 0){
       mx_printchar('-');	    
       if (n == -2147483648) {
            mx_printchar('2');
            n = 147483648;
        } else {
            n = -n;
        }
    }
    if(n == 0){
       mx_printchar('0');
    }
    
    int m = 0;
    int b = n;

    while(b != 0){
       m += 1;
       b /= 10;
    }

    b = n;
    int y = m;
    
    int arr[m];
    while(m >= 0){
       arr[m - 1] = b % 10;
       m--;
       b /= 10;
    }

    for(int i = 0; i < y; i++){
       mx_printchar(arr[i] + 48);
    }
}

