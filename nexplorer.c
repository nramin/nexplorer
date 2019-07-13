#include <ncurses.h>			/* ncurses.h includes stdio.h */  
#include <string.h> 
#include "dir_list.h"

#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;

char *choices[] = {
        "Choice 1",
        "Choice 2",
};

int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int main()
{
    dir_list* list = dir_list_construct_obj();
    dir_list_set_indent(list, 5);
    dir_list_test(list);
    dir_list_set_indent(list, 15);
    printf("%d\n", dir_list_get_indent(list));
    dir_list_delete_obj(list);
    
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;
    
    initscr();
    clear();
    noecho();
    cbreak();
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;

    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Use arrow keys");
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