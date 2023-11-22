#include "uls.h"

//The new_dir function calculates the number of directories in the input array and allocates memory for the directories array.
static void new_dir(t_manager ***directories, t_manager ***input) {
    int num_dir = 0;

    for (int i = 0; (*input)[i] != '\0'; i++) {
        if ((*input)[i]->error == NULL) {
            if (S_ISDIR((*input)[i]->statistic.st_mode) &&
                mx_strcmp((*input)[i]->name, ".") != 0 &&
                mx_strcmp((*input)[i]->name, "..") != 0) {
                num_dir++;
            }
        }
    }

    if (num_dir > 0) {
        *directories = malloc((num_dir + 1) * sizeof(t_manager *));
    }
}

//The clean_dirs_list function frees the memory occupied by the toDelete array elements,
static void clean_dirs_list(t_manager ***toDelete, t_manager **directories) {
    t_manager **temp = *toDelete;

    for (int i = 0; temp[i] != '\0'; i++) {
        mx_strdel(&temp[i]->name);
        mx_strdel(&temp[i]->path);

        if (temp[i]->error) {
            mx_strdel(&temp[i]->error);
        }

        free(temp[i]);
        temp[i] = NULL;
    }

    free(*toDelete);
    *toDelete = directories;
}

//The clean_dirs function frees the memory occupied by the elements of the input array.
void clean_dirs(t_manager ***input) {
    t_manager **toDelete = *input;

    for (int i = 0; toDelete[i] != '\0'; i++) {
        mx_strdel(&toDelete[i]->path);
        mx_strdel(&toDelete[i]->name);


        if (toDelete[i]->open != NULL) {
            clean_dirs(&toDelete[i]->open);
        }
        if (toDelete[i]->error) {
            mx_strdel(&toDelete[i]->error);
        }

        free(toDelete[i]);

        toDelete[i] = NULL;
    }

    free(*input);
    *input = NULL;
}

//The clean_files function allocates memory for the directories array, which contains pointers to t_manager structures
void clean_files(t_manager ***toDelete, t_flags *flags) {
    t_manager **directories = NULL;

    new_dir(&directories, toDelete);

    int num_dir = 0;

    for (int i = 0; (*toDelete)[i] != NULL; i++) {
        if ((*toDelete)[i]->error == NULL) {
            if (S_ISDIR((*toDelete)[i]->statistic.st_mode) && mx_strcmp((*toDelete)[i]->name, "..") != 0 && mx_strcmp((*toDelete)[i]->name, ".") != 0) {
                num_dir++;
                directories[num_dir] = add_file_node((*toDelete)[i]);
                directories[num_dir] = NULL;
            }
        }
    }

    flags->is_files = 1;

    clean_dirs_list(toDel, directories);
}

