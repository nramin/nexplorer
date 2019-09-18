#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "dir_list.h"

struct dir_list
{
    int indent;
    int file_count;
};

dir_list* dir_list_construct_obj(void)
{
    dir_list* instance = malloc(sizeof(dir_list));

    if (instance == NULL) {
        puts("dir_list object could not be created.");
    }

    return instance;
}

void dir_list_get_files(dir_list* this, char files[100][30])
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        int file_count = 0;
        while ((dir = readdir(d)) != NULL)
        {
            strcpy(files[file_count], dir->d_name);
            file_count++;
        }
        this->file_count = file_count;

        while (file_count < 100) {
            strcpy(files[file_count], "UNUSED_FILE_INDEX");
            file_count++;
        }

        for (int i = 0; i < 100; i++) {
            if (strcmp(files[i],"UNUSED_FILE_INDEX") != 0) {
                //printf("%s\n", files[i]);
            }
            
        }
            

        closedir(d);
    }
}

// int dir_list_get_file_count()
// {
//     int count = 0;
// }

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

int dir_list_get_file_count(dir_list* this)
{
    return this->file_count;
}

void dir_list_delete_obj(dir_list* obj) {
    free (obj);
}
