#include "uls.h"

//The obj_counter_init function allocates memory and initializes the t_obj_counter structure
static t_obj_counter *obj_counter_init() {
    t_obj_counter *new_obj = (t_obj_counter *)malloc(sizeof(t_obj_counter));

    new_obj->dirs_count = 0;
    new_obj->files_count = 0;
    new_obj->errors_count = 0;
    new_obj->i = 0;

    return new_obj;
}

// The print_one function prints file names in the files array on separate lines.
static void print_one(t_manager **files) {
    for (int i = 0; files[i] != '\0'; i++) {
        mx_printstr(files[i]->name);

        mx_printchar('\n');
    }
}

// The flags_init function allocates memory and initializes the t_flags structure,
// representing a set of flags to control the output of the uls program.
static t_flags *flags_init() {
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
void print_menu(t_manager ***files, t_flags* flags, char** argv) {

    sort_obj(&(*files), &flags, argv);

    if (flags->l) {
        flag_l(*files, flags);
    }
    if (isatty(1) && !flags->l) {
        print_clean(*files, flags);
    }
    if(!isatty(1) && ! flags->l) {
        print_one(*files);
    }
}

// The main function main of the uls program.
int main(int argc, char *argv[]) {
    t_flags *flags = flags_init();

    int counter = 1;
    check_flags(&flags, argv, &counter);

    int count_f = 0;
    char **name_of_file = get_files(argc, argv, counter, &count_f);

    t_manager **all_files = fill_file_manager(name_of_file, count_f);
    mx_del_strarr(&name_of_file);

    t_obj_counter *counter_o = obj_counter_init();
    t_manager **dirs = NULL;
    t_manager **errors = NULL;
    t_manager **files = NULL;

    count_obj(&all_files, &dirs, &files, &errors);
    arrange_obj(&all_files, &dirs, &files, &errors, counter_o);

    if (counter_o->errors_count > 0) {
        sort_obj(&errors, &flags, argv);

        print_errors(&errors);
    }

    if (counter_o->count_f > 0) {
        print_menu(&files, flags, argv);

        if (counter_o->dirs_count > 0) {
            mx_printchar('\n');
        }

        clean_dirs(&files);
    }

    if (counter_o->dirs_count > 0) {
        print_dirs(&dirs, flags, counter_o, argv);
    }

    free(flags);
    flags = NULL;

    free(counter_o);
    counter_o = NULL;

    return 0;
}

