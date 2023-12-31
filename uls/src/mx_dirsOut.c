#include "uls.h"

// The is_a_flag function checks if the string str is a filename,
// satisfying the conditions of the '-a' flag (including hidden files starting with a dot).
bool mx_isaFlag(char *str, t_flags *flags) {
    if (str[0] == '.' && flags->a) {
        return 1;
    }

    if (!(mx_strcmp(str, ".")) || !(mx_strcmp(str, ".."))) {
        if (flags->a) {
            return 1;
        }
        else{
            return 0;
        }
    }

    return 0;
}


bool mx_isAFlag(char *str, t_flags *flags) {
    if (!flags->A || !(mx_strcmp(str, "..")) || !(mx_strcmp(str, "."))) {
        return false;
    }

    return true;
}


// The files_count function counts the number of files in the dir directory
static int files_count(t_manager **dir, t_flags *flags) {
    int count = 0;
    DIR *pDir;
    t_manager *copy_dir = *dir;
    struct dirent *reader;

    if (S_ISDIR(copy_dir->statistic.st_mode)
        || S_ISLNK(copy_dir->statistic.st_mode)) {

        pDir = opendir(copy_dir->path);
        if (pDir != NULL) {
            while((reader = readdir(pDir)) != NULL) {

                if (reader->d_name[0] != '.'
                    || mx_isaFlag(reader->d_name, flags)
                    || mx_isAFlag(reader->d_name, flags)) {

                    count++;
                }
            }

            closedir(pDir);
        }
        else {
            (*dir)->error = mx_strdup(strerror(errno));

            return -1;
        }
    }

    return count;
}

// The check_errors_and_print function checks for errors in the directory structure
// and prints them, or calls the print_menu function (print_menu).
static void mx_errCheckAndOut(t_manager** directory, t_flags* flags, t_obj_counter *counter, char** argv) {
    if ((*directory)->open != NULL) {
        mx_menuOut(&(*directory)->open, flags, argv);

        if (flags->R == 1) {
            flags->is_files = 1;
            mx_remFiles(&(*directory)->open, flags);

            if ((*directory)->open) {
                mx_printchar('\n');
                mx_dirsPrintt(&(*directory)->open, flags, counter, argv);
            }
        }

    }
    else if ((*directory)->error != NULL) {
        mx_printerr("uls: ");
        mx_printerr((*directory)->path);
        mx_printerr(": ");
        mx_printerr((*directory)->error);
        mx_printerr("\n");
    }
}

// The output_dirs function outputs the contents of the directory array taking into account flags and errors.
static void mx_dirsOutp(t_manager*** directory, t_flags* flags, t_obj_counter* counter_obj, char** argv) {
    if (*directory) {
        for (int i = 0; (*directory)[i]; i++) {

            if (counter_obj->errors_count > 0
                || counter_obj->files_count > 0
                ||counter_obj->dirs_count > 1) {

                mx_printstr((*directory)[i]->path);
                mx_printstr(":\n");
            }

            if(flags->is_files == 1) {
                if ((*directory)[i]->path[0] == '/' && (*directory)[i]->path[1] == '/') {
                    mx_printstr(&(*directory)[i]->path[1]);
                }
                else {
                    mx_printstr((*directory)[i]->path);
                }

                mx_printchar(':');
                mx_printchar('\n');
            }

            mx_errCheckAndOut(&(*directory)[i], flags, counter_obj, argv);

            if ((*directory)[i + 1]) {
                mx_printchar('\n');
            }
        }

        //clean
        mx_cleanseDirs(directory);
    }

}

// The print_dirs function processes each directory in the directory array,
// counts the number of files in each directory and outputs their contents.
void mx_dirsPrintt(t_manager*** directory, t_flags* flags, t_obj_counter* counter_obj, char** argv) {
    int count = 0;
    DIR* Ndir;
    struct dirent* reader;

    for (int i = 0; (*directory)[i]; i++) {
        count = files_count(&(*directory)[i], flags);

        if (count > 0) {
            (*directory)[i]->open = (t_manager**)malloc((count + 1) * sizeof(t_manager*));

            if ((Ndir = opendir((*directory)[i]->path)) != NULL) {
                for (count = 0; (reader = readdir(Ndir)) != NULL;) {
                    if (reader->d_name[0] != '.'
                        || mx_isAFlag(reader->d_name, flags)
                        || mx_isaFlag(reader->d_name, flags)) {
                        (*directory)[i]->open[count++] = mx_addNodeWithName(reader->d_name, (*directory)[i]->path);
                    }
                }

                (*directory)[i]->open[count] = NULL;
            }

            closedir(Ndir);
        }
    }

    mx_dirsOutp(directory, flags, counter_obj, argv);
}

