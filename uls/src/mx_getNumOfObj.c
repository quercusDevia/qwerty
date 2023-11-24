#include "uls.h"

void mx_getNumOfObj(t_manager ***all_files, t_manager ***dirs, t_manager ***files, t_manager ***errors) {
    int numberOfFiless = 0;
    int numberOfDirss = 0;
    int numberOfErrorss = 0;

    int j = 0;
    while((*all_files)[j]) {
        //count files
        if(!((*all_files)[j]->error)) {
            if(!(S_ISDIR((*all_files)[j]->statistic.st_mode))) {
                numberOfFiless++;

            }
            else{
                numberOfDirss++;

            }
        }
        else{
            numberOfErrorss++;

        }

        j++;
    }

    if (numberOfErrorss > 0) {
        *errors = malloc((numberOfErrorss + 1) * sizeof(t_manager));
    }
    ////

    if (numberOfFiless > 0) {
        *files = malloc((numberOfFiless + 1) * sizeof(t_manager));
    }
    /////

    if (numberOfDirss > 0) {
        *dirs = malloc((numberOfDirss + 1) * sizeof(t_manager));
    }   
}
