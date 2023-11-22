#include "uls.h"

static bool add_flag(t_flags** flags, char flag) {
    bool isAdd = false;

    if(flag == 'l') {
        (*flags)->l = 1;
        isAdd = 1;
    }
    else if(flag == 'a') {
        (*flags)->a = 1;
        isAdd = 1;
    }
    else if(flag == 't') {
        (*flags)->t = 1;
        isAdd = 1;
    }
    else if(flag == 'r') {
        (*flags)->r = 1;
        isAdd = 1;
    }
    else if(flag == 'A') {
        (*flags)->A = 1;
        isAdd = 1;
    }
    else if(flag == 'R') {
        (*flags)->R = 1;
        isAdd = 1;
    }
    else if(flag == 'G') {
        (*flags)->G = 1;
        isAdd = 1;
    }
    else if(flag == 'F') {
        (*flags)->F = 1;
        isAdd = 1;
    }
    else if(flag == 'u' || flag == 'c' || flag == 'S') {
        isAdd = 1;
    }

    return isAdd;
}

void check_flags(t_flags **flags, char **argv, int *c) {
    while(argv[(*c)]) {
        if(argv[(*c)][0] == '-') {

            if(argv[(*c)][1] == '\0')
                break;
            
            if(argv[(*c)][1] == '-') {
                (*c)++;
                break;
            }

            //add some flags
            for(int j = 1; argv[(*c)][j]; j++) {
                if(add_flag(flags, argv[(*c)][j]) == false)
                    illegal_opt(argv[(*c)][j]);
            }
        }
        else {
            //exit
            break;
        }

        (*c)++;
    }
}
