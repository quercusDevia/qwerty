#include "libmx.h"

void mx_print_strarr(char **arr, const char *delim){
    if (arr == NULL || delim == NULL){
       exit(0);
    }
    else{  
    	for (int i = 0; arr[i] != NULL; i++){
            if(i != 0){
	        mx_printstr(delim);
	    }
	    mx_printstr(arr[i]);    
	}
    }
    mx_printchar('\n');
}

