#include "libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd){
    if(buf_size < 0 || fd < 0){
        return -2;
    }
	
    int ch = 0;
    int size = 0;
    char *buf = NULL;
    int num = 0;
    static char *sarr = NULL;
    int size_sarr = 0;

    buf = mx_strnew(buf_size);
    ch = read(fd, buf, buf_size);

    while(ch > 0){
	if(sarr){
	    *lineptr = mx_strjoin(*lineptr, sarr);
	    size_sarr = mx_strlen(sarr);
	    size += size_sarr;
	    mx_strdel(&sarr);
	}
        for(int i = 0; i < (int)buf_size; i++){	
	    if(buf[i] == delim){
		char *str = mx_strndup(buf, (size - (buf_size * num) - size_sarr));
		*lineptr = mx_strjoin(*lineptr, str);
		int y = size - ((int)buf_size * num) - size_sarr;
		buf += y + 1;
		sarr = mx_strdup(buf);
		return size;
	    }
	    size++;
	}
	char *str = mx_strdup(buf);
        *lineptr = mx_strjoin(*lineptr, str);
	ch = read(fd, buf, buf_size);
	num++;
    }

    return -1;
}

