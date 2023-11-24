#include "libmx.h"

int size_of_file(const char *file){
    int ofile = open(file, O_RDONLY);
    int ch = 0;
    int size = 0;
    char buf;

    ch = read(ofile, &buf, 1);

    while(ch > 0){
        ch = read(ofile, &buf, 1);
        size++;
    }

    close(ofile);
    return size;
}

char *mx_file_to_str(const char *file){
    int ofile = open(file, O_RDONLY);

    if(ofile == -1){
      close(ofile);
      return NULL;
    }

    int size = 0;
    size = size_of_file(file);

    if(size <= 0){
        return NULL;
    }

    int n = 0;
    char *newstr = mx_strnew(size);
    n  = read(ofile, newstr, size);
    close(ofile);
    return newstr;
}
