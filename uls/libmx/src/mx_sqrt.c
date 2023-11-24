#include "libmx.h"

int mx_sqrt(int x){
    if (x <= 0){
        return 0;
    }

    if (x == 1){
       return 1;
    }

    for(int i = 2; i <= x / 2 + 1; i++){
	if (x == i * i){
	    return i;
	}
    }
    
    return 0;
     
}

