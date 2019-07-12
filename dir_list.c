#include <stdlib.h>
#include <stdio.h> 
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
    puts("test");
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