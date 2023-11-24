#include "libmx.h"

char *mx_del_extra_spaces(const char *str){
    if(!str){
        return NULL;
    }
    
    str = mx_strtrim(str);
    int size = mx_strlen(str);
    int count = 0;
    bool flag = false;

    for(int i = 0; i < size; i++){
        if(flag == true && mx_isspace(str[i]) == true){
	    continue;
	}
	else if(mx_isspace(str[i]) == true){
	    flag = true;
            count++;
	}
	else{
	    flag = false;
	    count++;
	}
    }

    char* newstr = mx_strnew(count);

    for(int i = 0, j = 0;  i < count; i++, j++){
        if(mx_isspace(str[j])){
	    while(mx_isspace(str[j])){
	    j++;
	    }
	    newstr[i] = ' ';
	    i++;
	}
	newstr[i] = str[j];
    }

    char *result = mx_strdup(newstr);
    mx_strdel(&newstr);

    return result;
}

