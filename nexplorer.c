#include <ncurses.h>			/* ncurses.h includes stdio.h */  
#include <string.h> 
#include "dir_list.h"

char choices[100][30];

int n_choices = 0;

void print_menu(WINDOW *menu_win, int highlight);

int main()
{
    int HEIGHT, WIDTH;

    printf("%d\n", n_choices);
    dir_list* list = dir_list_construct_obj();
    //dir_list_set_indent(list, 5);
    dir_list_get_files(list, choices);
    //dir_list_set_indent(list, 15);
    //printf("%d\n", dir_list_get_indent(list));
    printf("%d\n", dir_list_get_file_count(list));
    n_choices = dir_list_get_file_count(list);
    dir_list_delete_obj(list);
    
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
    print_menu(menu_win, highlight);
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
                break;
            default:
                refresh();
                break;
        }
        print_menu(menu_win, highlight);
        if (choice != 0)
            break;
    }

    mvprintw(23, 0, "You chose");
    clrtoeol();
    refresh();
    endwin();

    return 0;
}

void print_menu(WINDOW *menu_win, int highlight)
{
    int x, y, i;

    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for (i = 0; i < n_choices; ++i)
    {
        if (highlight == i + 1)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}