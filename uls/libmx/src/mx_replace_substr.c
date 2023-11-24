#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace){
    if(!str | !sub | !replace){
        return NULL;
    }

    int strsz = mx_strlen(str);
    int subsz = mx_strlen(sub);
    int replacesz = mx_strlen(replace);
    int num = 0;

    num = mx_count_substr(str, sub);

    char *newstr = mx_strnew(strsz - (num * subsz) + (num * replacesz));
    int i = 0;

    while(*str){
        if(mx_strncmp(str, sub, subsz) == 0){
	    mx_strcpy(&newstr[i], replace);
	    i += replacesz;
	    str += subsz;
	}
	else{
	    newstr[i++] = *str++;
	}
    }

    newstr[i] = '\0';
    return newstr;
}

