#include "uls.h"

char **get_files(int argc, char **argv, int counter, int *counterOfFiles) {
    char **arrOfFiles = NULL;

    if(argc == counter) {
        arrOfFiles = (char **)malloc(2 * sizeof(char *));
        
        arrOfFiles[1] = NULL;
        arrOfFiles[0] = mx_strdup(".");

        *counterOfFiles = 2;
    }
    else {
        int i = counter;
        for(;argv[i];) {
            i++;
        }


        arrOfFiles = (char **)malloc((i - counter + 1) * sizeof(char *));

        //record files
        i = 0;
        while(argv[counter]) {
            arrOfFiles[i] = mx_strdup(argv[counter]);

            i++;
            counter++;
        }

        arrOfFiles[i] = NULL;
        *counterOfFiles = i + 1;
    }

    return arrOfFiles;
}
