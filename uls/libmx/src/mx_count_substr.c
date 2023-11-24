#include "libmx.h"

int mx_count_substr(const char *str, const char *sub){
    if(!str || !sub){
        return -1;
    }

    int count = 0;
    for(int i = 0; *str; i++){
        if(str == mx_strstr(str, sub)){
	    count++;
	}
	str++;
    }

    return count;
}

