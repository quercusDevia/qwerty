#include "uls.h"

void arrange_obj(t_manager ***all_files, t_manager ***dirs, t_manager ***files, t_manager ***errors, t_obj_counter *counter) {
    for (; (*all_files)[counter->i] != NULL; counter->i++) {

        if((*all_files)[counter->i]->error != NULL) {
            (*errors)[counter->errors_count++] = add_file_node((*all_files)[counter->i]);
            (*errors)[counter->errors_count] = NULL;
            continue;
        }
        
        if (S_ISDIR((*all_files)[counter->i]->statistic.st_mode) != 0) {
            (*dirs)[counter->dirs_count++] = add_file_node((*all_files)[counter->i]);
            (*dirs)[counter->dirs_count] = NULL;
            continue;
        }

        (*files)[counter->files_count++] = add_file_node((*all_files)[counter->i]);
        (*files)[counter->files_count] = NULL;
    }
}
