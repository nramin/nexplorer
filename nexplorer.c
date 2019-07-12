#include <ncurses.h>			/* ncurses.h includes stdio.h */  
#include <string.h> 
#include <dirent.h>
#include "dir_list.h"
 
int main()
{
    dir_list* list = dir_list_construct_obj();
    dir_list_set_indent(list, 5);
    dir_list_test(list);
    dir_list_set_indent(list, 15);
    printf("%d\n", dir_list_get_indent(list));
    dir_list_delete_obj(list);

    char mesg[]="Enter a string: ";		/* message to be appeared on the screen */
    char str[80];
    int row,col;				/* to store the number of rows and *
            * the number of colums of the screen */
    initscr();				/* start the curses mode */
    getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
    mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);

    /* print the message at the center of the screen */
    getstr(str);
    mvprintw(LINES - 2, 0, "You Entered: %s", str);
    getch();
    endwin();

    return 0;
}