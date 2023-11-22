#include "uls.h"

//The illegal_opt function outputs an error message for an invalid option and calls the usage function.
void illegal_opt(char ch) {
    mx_printerr("uls: illegal option -- ");

    write(2, &ch, 1);
    write(2, "\n", 1);

    usage();
}

