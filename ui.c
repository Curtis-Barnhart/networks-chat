#include <assert.h>
#include <memory.h>
#include <ncurses.h>

#include <pthread.h>

#include "var_str.h"
#include "lib.h"

void *w_input_manager(void *window) {
    WINDOW *w_input = (WINDOW *) window;
    int c;
    int width, height, pos_x, pos_y;
    getmaxyx(w_input, height, width);
    // TODO: put the height... at least into some macro somewhere
    width -= 2, height = 3;

    mvwprintw(w_input, 1, 1, "Hello!");
    wrefresh(w_input);
    getch();

    struct var_str vstr = var_str_new(1),
    char *b1 = malloc(width - 1),
         *b2 = malloc(width - 1),
         *b3 = malloc(width - 1);
    while (1) {
        c = wgetch(w_input);
        // TODO: may have to check what character is before using
        var_str_push_back_ch(&vstr, c);
        var_str_to_3_buf(&vstr, b1, b2, b3, width-2);
        mvwprintw(w_input, 1, 1, "%s", vstr.str);
        wrefresh(w_input);
    }
}

int main(int argc, char *argv[]) {
    initscr();			        /* Start curses mode must be first */
    noecho();                   /* we will let the users input show up for now */
    // TODO: Is this necessary?
	refresh();		            /* Print it on to the real screen */

    int x_sz, y_sz;
    int w_input_width, w_input_height, w_input_x, w_input_y;
    getmaxyx(stdscr, y_sz, x_sz);

    // we just nab 5 lines for the text entry box,
    // so make sure that it fits lol
    assert(y_sz > 10);

    // w1 will be upper window, w2 will be lower window
    WINDOW *w_disp = newwin(y_sz - 5, x_sz, 0, 0),
           *w_input = newwin(5, x_sz, y_sz - 5, 0);
    w_input_height = 3, w_input_x = x_sz - 2, w_input_x = 1, w_input_y = y_sz - 4;
    box(w_disp, 0, 0);
    box(w_input, 0, 0);
    wrefresh(w_disp);
    wrefresh(w_input);
    
    pthread_t w_input_th;
    int w_input_th_id = pthread_create(&w_input_th, NULL, w_input_manager, (void *) w_input);
    // this will never occur
    pthread_join(w_input_th, NULL);

	getch();		            /* Wait for user input */

    delwin(w_disp);                 /* delete our windows when done */
    delwin(w_input);
	endwin();		            /* End curses mode		  */

	return 0;
}

