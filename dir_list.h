#pragma once

typedef struct dir_list dir_list;

dir_list* dir_list_construct_obj(void);

void dir_list_test();

void dir_list_set_indent(dir_list* this, int indent);

int dir_list_get_indent(dir_list* this);

void dir_list_delete_obj(dir_list* list);