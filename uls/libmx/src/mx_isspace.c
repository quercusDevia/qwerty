#include "libmx.h"

bool mx_isspace(char c){
     if(c == ' ' 
	|| c == '\t' 
	|| c == '\n' 
	|| c == '\v'
	|| c == '\f'
	|| c == '\r'
	|| c == '\a'){
        return true;
     }
     else{
        return false;
     }
}

