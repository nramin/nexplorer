#include <ncurses.h>			/* ncurses.h includes stdio.h */  
#include <string.h> 
#include "dir_list.h"
#include <unistd.h>

char choices[100][30];

int n_choices = 0;

void print_menu(WINDOW *menu_win, int highlight, dir_list* list);

void traverse_dir(dir_list* list);

int main()
{
    int HEIGHT, WIDTH;

    dir_list* list = dir_list_construct_obj();
    //dir_list_set_indent(list, 5);
    dir_list_get_files(list, choices);
    //dir_list_set_indent(list, 15);
    //printf("%d\n", dir_list_get_indent(list));
    //printf("%d\n", dir_list_get_file_count(list));
    n_choices = dir_list_get_file_count(list);
    dir_list_delete_obj(list);




    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
        dir_list_set_current_directory(list, cwd);
    }

    //printf("Current working dir: %c\n", dir_list_get_current_directory(list)[4]);




    
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;
    
    initscr();
    getmaxyx(stdscr, HEIGHT, WIDTH);

    //scrollok(stdscr, TRUE);
    clear();
    noecho();
    cbreak();

    menu_win = newwin(HEIGHT, WIDTH, 0, 0);
    keypad(menu_win, TRUE);
    refresh();
    print_menu(menu_win, highlight, list);
    while(1)
    {
        c = wgetch(menu_win);
        switch(c)
        {
            case KEY_UP:
                if (highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                if (choice == 2) {
                    traverse_dir(list);
                }
                break;
            default:
                refresh();
                break;
        }
        print_menu(menu_win, highlight, list);
        if (choice != 0)
            break;
    }

    mvprintw(23, 0, "You chose");
    clrtoeol();
    refresh();
    endwin();

    return 0;
}

void print_menu(WINDOW *menu_win, int highlight, dir_list* list)
{
    int x, y, i;

    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    mvwprintw(menu_win, y, x, "%s", dir_list_get_current_directory(list));
    for (i = 1; i < n_choices; ++i)
    {
        ++y;
        if (highlight == i + 1)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
    }
    wrefresh(menu_win);
}

void traverse_dir(dir_list* list)
{
    //int init_size = strlen(cwd);
    char delim[] = "/";

    char *ptr = strtok(dir_list_get_current_directory(list), delim);

	int i;

    for (i = 0; i < strlen(ptr); i++)
	{
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
}