#include "uls.h"

//The obj_counter_init function allocates memory and initializes the t_obj_counter structure
static t_obj_counter *mx_initObjCouuunt() {
    t_obj_counter *new_obj = (t_obj_counter *)malloc(sizeof(t_obj_counter));

    new_obj->dirs_count = 0;
    new_obj->files_count = 0;
    new_obj->errors_count = 0;
    new_obj->i = 0;

    return new_obj;
}

// The print_one function prints file names in the files array on separate lines.
static void mx_flInfoOut(t_manager **files) {
    for (int i = 0; files[i]; i++) {
        mx_printstr(files[i]->name);

        mx_printchar('\n');
    }
}

// The flags_init function allocates memory and initializes the t_flags structure,
// representing a set of flags to control the output of the uls program.
static t_flags *mx_intitFlgs() {
    t_flags *new_t_flags = (t_flags *)malloc(sizeof(t_flags));

    new_t_flags->A = 0;
    new_t_flags->c = 0;
    new_t_flags->F = 0;
    new_t_flags->G = 0;
    new_t_flags->R = 0;
    new_t_flags->S = 0;
    new_t_flags->a = 0;
    new_t_flags->l = 0;
    new_t_flags->t = 0;
    new_t_flags->r = 0;
    new_t_flags->u = 0;

    return new_t_flags;
}


// The print_menu function sorts and outputs objects in the files array according to the flags.
void mx_menuOut(t_manager ***files, t_flags* flags, char** argv) {

    mx_sortObjs(&(*files), &flags, argv);

    if (flags->l) {
        mx_LFlagFunc(*files, flags);
    }
    if (isatty(1) && !flags->l) {
        mx_outCleansem(*files, flags);
    }
    if(!isatty(1) && ! flags->l) {
        mx_flInfoOut(*files);
    }
}

// The main function main of the uls program.
int main(int argc, char *argv[]) {
    t_flags *flags = mx_intitFlgs();

    int counter = 1;
    mx_flCheck(&flags, argv, &counter);

    int count_f = 0;
    char **name_of_file = mx_getThatFiles(argc, argv, counter, &count_f);

    t_manager **all_files = mx_setFileMang(name_of_file, count_f);
    mx_del_strarr(&name_of_file);

    t_obj_counter *counter_o = mx_initObjCouuunt();
    t_manager **dirs = NULL;
    t_manager **errors = NULL;
    t_manager **files = NULL;

    mx_getNumOfObj(&all_files, &dirs, &files, &errors);
    mx_placeObj(&all_files, &dirs, &files, &errors, counter_o);

    if (counter_o->errors_count > 0) {
        mx_sortObjs(&errors, &flags, argv);

        mx_errorsOutputu(&errors);
    }

    if (counter_o->files_count > 0) {
        mx_menuOut(&files, flags, argv);

        if (counter_o->dirs_count > 0) {
            mx_printchar('\n');
        }

        mx_cleanseDirs(&files);
    }

    if (counter_o->dirs_count > 0) {
        mx_dirsPrintt(&dirs, flags, counter_o, argv);
    }

    free(flags);
    flags = NULL;

    free(counter_o);
    counter_o = NULL;

    return 0;
}

