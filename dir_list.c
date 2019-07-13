#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "dir_list.h"

struct dir_list
{
    int indent;
};

dir_list* dir_list_construct_obj(void)
{
    dir_list* instance = malloc(sizeof(dir_list));

    if (instance == NULL) {
        puts("dir_list object could not be created.");
    }

    return instance;
}

void dir_list_test(dir_list obj)
{
    char files[100]; //allows 100 files with 30 letter names
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        int file_count = 0;
        char file_name[30];
        while ((dir = readdir(d)) != NULL)
        {
            strcpy(file_name, dir->d_name);
            //printf("%s \n", file_name);
            strcpy(&files[file_count], file_name);
            file_count++;
        }
            

        closedir(d);
    }
}

void dir_list_set_indent(dir_list* list, int indent)
{
    if (&indent == NULL)
    {
        return;
    }
    list->indent = indent;
}

int dir_list_get_indent(dir_list* this)
{
    return this->indent;
}

void dir_list_delete_obj(dir_list* obj) {
    free (obj);
}