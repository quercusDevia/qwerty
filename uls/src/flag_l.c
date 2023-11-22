#include "uls.h"

void find_max(t_manager** text, int* blocks, int* max_size, int* max_links, int* max_usname, int* max_grname) {
    for (int i = 0; text[i] != NULL; i++) {
        struct stat textBuffer = text[i]->statistic;
        int bValue = textBuffer.st_blocks;

        *blocks += bValue;

        // maximum len of string (lValue)
        int lValue = textBuffer.st_nlink;

        if (mx_strlen(mx_itoa(lValue)) > * max_links) {
            *max_links = mx_strlen(mx_itoa(lValue));
        }

        //maximum length of username string (uValue)
        struct passwd* uValue = getpwuid(textBuffer.st_uid);

        if (uValue != NULL) {
            if (mx_strlen(uValue->pw_name) > * max_usname) {
                *max_usname = mx_strlen(uValue->pw_name);
            }
        }
        else {
            char* atStr = mx_itoa(textBuffer.st_uid);

            if (mx_strlen(atStr) > * max_usname) {
                *max_usname = mx_strlen(atStr);
            }
        }

        //group's maximum length of name
        struct group* gValue = getgrgid(textBuffer.st_gid);

        if(gValue != NULL) {

            if (mx_strlen(gValue->gr_name) > *max_grname) {
                *max_grname = mx_strlen(gValue->gr_name);
            }
        }  
        else {
            char* atStr = mx_itoa(textBuffer.st_gid);

            if (mx_strlen(atStr) > *max_grname) {
                *max_grname = mx_strlen(atStr);
            }
        } 
       
        //size maximum length
        int i = textBuffer.st_size;

        if (mx_strlen(mx_itoa(i)) > * max_size) {

            *max_size = mx_strlen(mx_itoa(i));
        }
    }
}

void flag_l(t_manager** text, t_flags* flags) {

    int numOfBlock = 0, mSizem = 0, mOfLink = 0, longUname = 0, longGrName = 0;
    find_max(text, &numOfBlock, &mSizem, &mOfLink, &longUname, &longGrName);

    mx_printstr("total ");
    mx_printint(numOfBlock);
    mx_printstr("\n");
    ///////////////////////////

    for (int i = 0; text[i] != NULL; i++) {
        struct stat textBufferr = text[i]->statistic;

        if ((textBufferr.st_mode & S_IFDIR)) {
            mx_printstr("d");
        }
        else {
            mx_printstr("-");
        }

        // info about uSer
        if ((textBufferr.st_mode & S_IRUSR)) {
            mx_printstr("r");
        }
        else {
            mx_printstr("-");
        }


        if ((textBufferr.st_mode & S_IWUSR)) {
            mx_printstr("w");
        }
        else {
            mx_printstr("-");
        }


        if ((textBufferr.st_mode & S_IXUSR)) {
            mx_printstr("x");
        }
        else {
            mx_printstr("-");
        }

        // info about Group
        if ((textBufferr.st_mode & S_IRGRP)) {
            mx_printstr("r");
        }
        else {
            mx_printstr("-");
        }


        if ((textBufferr.st_mode & S_IWGRP)) {
            mx_printstr("w");
        }
        else {
            mx_printstr("-");
        }


        if ((textBufferr.st_mode & S_IXGRP)) {
            mx_printstr("x");
        }
        else {
            mx_printstr("-");
        }

        // info about anything else

        if ((textBufferr.st_mode & S_IROTH)) {
            mx_printstr("r");
        }
        else {
            mx_printstr("-");
        }


        if ((textBufferr.st_mode & S_IWOTH)) {
            mx_printstr("w");
        }
        else {
            mx_printstr("-");
        }


        if ((textBufferr.st_mode & S_IXOTH)) {
            mx_printstr("x");
        }
        else {
            mx_printstr("-");
        }


        mx_printstr("  ");

        // info about Links

        int tValuee = textBufferr.st_nlink;

        for (int j = mx_strlen(mx_itoa(tValuee)); j < mOfLink; j++) {
            mx_printstr(" ");
        }

        mx_printint(tValuee);
        mx_printstr(" ");

        // userName

        struct passwd* uValuee = getpwuid(textBufferr.st_uid);

        if (uValuee != NULL) {
            for (int j = mx_strlen(uValuee->pw_name); j < longUname; j++) {
                mx_printstr(" ");
            }
            mx_printstr(uValuee->pw_name);
            mx_printstr("  ");
        }
        else {
            char* atStrr = mx_itoa(textBufferr.st_uid);
            for (int j = mx_strlen(atStrr); j < longUname; j++) {
                mx_printstr(" ");
            }
            mx_printint(textBufferr.st_uid);
        }

        

        //groupName
        struct group* gValuee = getgrgid(textBufferr.st_gid);

        if(gValuee != NULL) {

            for (int j = mx_strlen(gValuee->gr_name); j < longGrName; j++) {
                mx_printstr(" ");
            }


            mx_printstr(gValuee->gr_name);
        }
        else {
          
            char* at = mx_itoa(textBufferr.st_gid);

            for (int j = mx_strlen(at); j < longGrName; j++) {
                mx_printstr(" ");
            }


            mx_printint(textBufferr.st_gid);
        }
        

        mx_printstr("  ");

        //info about Size
        int justSize = textBufferr.st_size;

        char* sizeOfThatText = mx_itoa(justSize);

        for (int j = mx_strlen(sizeOfThatText); j < mSizem; j++) {
            mx_printstr(" ");
        }


        mx_printstr(sizeOfThatText);

        mx_printstr(" ");


        // info about Time
        time_t *m_time = &textBufferr.st_mtime;
        time_t *c_time = &textBufferr.st_ctime;
        time_t *a_time = &textBufferr.st_atime;
        
        if (flags->c) {
            m_time = c_time;
        }

        if (flags->u) {
            m_time = a_time;
        }

        char *thatStr = ctime(m_time);
        int o_o = 0;

        if (time(NULL) - textBufferr.st_mtime < 15811200) {
            for (o_o = 4; o_o < 16; o_o++) {
                mx_printchar(thatStr[o_o]);
            }


        }
        else {
            for (o_o = 4; o_o < 11; o_o++) {
                mx_printchar(thatStr[o_o]);
            }

            for (o_o = 19; o_o < 24; o_o++) {
                mx_printchar(thatStr[o_o]);
            }

        }

        ////////////////
        mx_printstr(" ");

        // info about Name
        if (flags->G) {

            if (S_ISDIR(textBufferr.st_mode)) {

                mx_printstr(CL_BLUE);
            }
            else if (textBufferr.st_mode & S_IXUSR) {

                mx_printstr(CL_RED);
            }
            else if (S_ISSOCK(textBufferr.st_mode)) {

                mx_printstr(CL_GREEN);
            }
            else if (S_ISFIFO(textBufferr.st_mode)) {

                mx_printstr(CL_BROWN);
            }
            else if (S_ISLNK(textBufferr.st_mode)) {

                mx_printstr(CL_MAGENTA);
            }
            else if (S_ISBLK(textBufferr.st_mode)) {

                mx_printstr(CL_BLUE);
                mx_printstr(CL_BOLD_CYAN);
            }
            else if (S_ISCHR(textBufferr.st_mode)) {

                mx_printstr(CL_BLUE);
                mx_printstr(CL_BOLD_BROWN);
            }
            else if (textBufferr.st_mode & S_ISUID) {

                mx_printstr(CL_BLACK);
                mx_printstr(CL_BOLD_RED);
            }
            else if (textBufferr.st_mode & S_ISGID) {

                mx_printstr(CL_BLACK);
                mx_printstr(CL_BOLD_CYAN);
            }
            else if (textBufferr.st_mode & S_ISVTX) {

                mx_printstr(CL_BLACK);
                mx_printstr(CL_BOLD_GREEN);
            }

        }

        mx_printstr(text[i]->name);
        ////////////////////////////
        if (flags->G) {
            mx_printstr(CL_END);
        }

        if (flags->F) {
            if (S_ISDIR(textBufferr.st_mode)) {
                mx_printstr("/");

            }
            else if (textBufferr.st_mode & S_IXUSR) {
                mx_printstr("*");

            }
            else if (S_ISLNK(textBufferr.st_mode)) {
                mx_printstr("@");
            }
            else if (S_ISSOCK(textBufferr.st_mode)) {
                mx_printstr("=");

            }
            else if (S_ISFIFO(textBufferr.st_mode)) {
                mx_printstr("|");

            }
            /////////////////////
        }

        mx_printstr("\n");


    }

}
