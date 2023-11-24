#include "uls.h"

// The fill_file_manager function creates an array of t_manager structures representing files,
// based on the passed file names in the nameFiles array and their total number count.
// Returns a pointer to the created array of structures.
t_manager **mx_setFileMang(char **nameFiles, int count) {
    int i = 0;
    t_manager **all_files = (t_manager **)malloc(count * sizeof(t_manager *));

    while (nameFiles[i]) {
        all_files[i] = mx_nodeAddFile(nameFiles[i]);
        i++;
    }

    all_files[i] = NULL;

    return all_files;
}
