#include "libmx.h"

void mx_print_unicode(wchar_t c){
   write(1, &c, 1);
}

