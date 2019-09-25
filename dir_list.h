#pragma once

typedef struct dir_list dir_list;

dir_list* dir_list_construct_obj(void);

void dir_list_get_files();

void dir_list_set_indent(dir_list* this, int indent);

int dir_list_get_indent(dir_list* this);

int dir_list_get_file_count(dir_list* this);

void dir_list_delete_obj(dir_list* list);

void dir_list_set_current_directory(dir_list* list, char directory[1024]);

char* dir_list_get_current_directory(dir_list* this);