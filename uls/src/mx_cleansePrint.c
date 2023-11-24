#include "uls.h"

static void mx_outTabss(int len, int max_len, t_flags* flags) {
    int g = max_len - len;
    int count = 0;

    if(flags->G) {

        for (int i = len; i < (max_len / 2) + 1; i++) {
            mx_printchar(' ');
        }

    }
    else {

        if (g % 8 == 0) {
            count = g / 8;
        }
        else {
            count = (g / 8) + 1;
        }

        for (int i = 0; i < count; i++) {
            mx_printchar('\t');
        }
    }
}

static int mx_getMaxLenOfName(t_manager **file) {
    int temp = 0;
    int max_num = 0;

    for (int i = 0; file[i]; i++) {
        temp = mx_strlen(file[i]->name);

        if (max_num < temp) {
            max_num = temp;
        }
    }

    if (max_num % 8 == 0) {
        max_num += 8;

    }
    else if(max_num % 8 != 0){
        max_num = max_num + (max_num % 8) - 8;
    }

    return max_num;
}

static void mx_outColumn(t_manager **files, int row, int num, int max_len, t_flags* flags) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; i + j < num; j += row) {
            mx_printstr(files[j + i]->name);

            if (files[i + j + 1] && (row + i + j < num)) {
                mx_outTabss(mx_strlen(files[i + j]->name), max_len, flags);
            }
        }

        if (i != row - 1) { mx_printchar('\n'); }
    }
}

static void mx_remPrintt(t_manager **files, int max_length, int wCol, t_flags* flags) {
    int row = 0;
    int col = 0;
    int count = 0;

    if ((wCol / max_length) != 0) {
        col = wCol / max_length;
    }
    else {
        col++;
    }

    if (max_length * col > wCol && col != 1) {
        col--;
    }

    while (files[count]) {
        count++;
    }


    if (count * max_length > wCol) {
        row = count / col;

        if (row == 0 || count % col != 0) {
            row++;
        }

        mx_outColumn(files, row, count, max_length, flags);
    }
    else {
        for (int i = 0; files[i]; i++) {
            if (flags->G) {

                struct stat buf = files[i]->statistic;

                if (S_ISDIR(buf.st_mode)) {
                    mx_printstr(CL_BLUE);
                }

                else if (S_ISSOCK(buf.st_mode)) {
                    mx_printstr(CL_GREEN);
                }

                else if (S_ISFIFO(buf.st_mode)) {
                    mx_printstr(CL_BROWN);
                }

                else if (S_ISBLK(buf.st_mode)) {
                    mx_printstr(CL_BLUE);
                    mx_printstr(CL_BOLD_CYAN);
                }
                else if (S_ISLNK(buf.st_mode)) {
                    mx_printstr(CL_MAGENTA);
                }
                else if (S_ISCHR(buf.st_mode)) {
                    mx_printstr(CL_BLUE);
                    mx_printstr(CL_BOLD_BROWN);
                }
                else if (buf.st_mode & S_ISVTX) {
                    mx_printstr(CL_BLACK);
                    mx_printstr(CL_BOLD_GREEN);
                }
                else if (buf.st_mode & S_ISGID) {
                    mx_printstr(CL_BLACK);
                    mx_printstr(CL_BOLD_CYAN);
                }
                else if (buf.st_mode & S_ISUID) {
                    mx_printstr(CL_BLACK);
                    mx_printstr(CL_BOLD_RED);
                }
                else if (buf.st_mode & S_IXUSR) {
                    mx_printstr(CL_RED);
                }
            }

            mx_printstr(files[i]->name);

            if (flags->G) {
                mx_printstr(CL_END);
            }

            if (flags->F) {
                struct stat buf = files[i]->statistic;
                if (buf.st_mode & S_IFDIR) {
                    mx_printstr("/");
                }
                else if (buf.st_mode & S_IFIFO) {
                    mx_printstr("|");
                }
                else if (buf.st_mode & S_IFSOCK) {
                    mx_printstr("=");
                }
                else if (buf.st_mode & S_IXUSR) {
                    mx_printstr("*");
                }
                else if (buf.st_mode & S_IFLNK) {
                    mx_printstr("@");
                }

            }

            if (files[i + 1]) {
                mx_outTabss(mx_strlen(files[i]->name), max_length, flags);
            }
        }
    }

    mx_printchar('\n');
}

void mx_outCleansem(t_manager **files, t_flags* flags) {
    if (files == NULL) {
        return;
    }

    struct winsize window;

    int max_len_of_word = mx_getMaxLenOfName(files);

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

    if (isatty(1)) {
        mx_remPrintt(files, max_len_of_word, window.ws_col, flags);
    }
    else {
        mx_remPrintt(files, max_len_of_word, 80, flags);
    }
}
