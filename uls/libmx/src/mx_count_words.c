#include "libmx.h"

int mx_count_words(const char *str, char c){
    int count = 0;
    int i = 0;
    bool flag = true;

    if(str == NULL){
        return -1;
    }
    else{
        while(str[i]){
	    if(str[i] == c){
	        flag = true;
	    }
	    else if (flag == true){
	        flag = false;
		count++;
	    }
	    i++;
	}
    }
    return count;
}

