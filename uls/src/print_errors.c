#include "uls.h"

void print_errors(t_manager ***errors) {
    int j = 0;
    while((*errors)[j]) {
        //Error hanler
        mx_printerr("uls: ");
        mx_printerr((*errors)[j]->name);

        mx_printerr(": ");
        mx_printerr((*errors)[j]->error);

        mx_printerr("\n");

        //Describing error:
        mx_strdel(&(*errors)[j]->name);
        mx_strdel(&(*errors)[j]->path);
        mx_strdel(&(*errors)[j]->error);

        //Delete error:
        free((*errors)[j]);
        (*errors)[j] = NULL;

        j++;
    }

    free(*errors);
    *errors = NULL;
}
