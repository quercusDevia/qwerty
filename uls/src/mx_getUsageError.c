#include "uls.h"

void mx_getUsageError() {
    //Empty argv
    mx_printerr("usage: uls [-latrcuSGARF] [file ...]\n");
    exit(-1);
}
