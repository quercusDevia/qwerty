#include "libmx.h"

unsigned long mx_hex_to_nbr(const char *hex){
    unsigned long result =0;
    int size = 0;

    for (int i = 0; hex[i] != '\0'; i++){
        size++;
    }
    for (int i = 0; i < size; i++){
        char ch = hex[i];
	if (ch >= '0' && ch <= '9'){
	   result = result * 16 + (ch - '0');
	}
	else if (ch >= 'A' && ch <= 'F'){
	   result = result * 16 + (ch - 'A' + 10);
	}
	else if(ch >= 'a' && ch <= 'f'){
           result = result * 16 + (ch - 'a' + 10);
        }
	else{
	   return 0;
        }
    }
    return result;
}

