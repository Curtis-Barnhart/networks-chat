#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>

#include <ncurses.h>
#include <pthread.h>
#include <sys/socket.h>

#include "var_str.h"
#include "line_buff.h"
#include "lib.h"

struct w_manager_data {
    WINDOW *window;
    int socket_fd;
};

void *w_input_manager(void *data) {
    // get the window * and socket descriptor out of passed data
    // remember, it's ours now so we have to free it
    WINDOW *w_input = ((struct w_manager_data *) data)->window;
    int socket_fd = ((struct w_manager_data *) data)->socket_fd;
    free(data);

    int c;
    int width, height;
    getmaxyx(w_input, height, width);
    // TODO: put the height... at least into some macro somewhere
    width -= 2, height = 3;

    // get a variable length string to store whatever the user has typed
    // each bn buffer is for one line in the text input box on screen
    struct var_str vstr = var_str_new(1);
    // no need to free because thread gets in loop
    char *b1 = malloc(width - 1),
         *b2 = malloc(width - 1),
         *b3 = malloc(width - 1);

    // continuously get characters forever
    while (1) {
        c = wgetch(w_input);
        switch (c) {
            // different terminals might use different chars apparently?
            case KEY_BACKSPACE:
            case KEY_DC:
            case 127:
                var_str_pop_back_ch(&vstr);
                break;
            case '\n':
                var_str_push_back_ch(&vstr, c);
                send(socket_fd, vstr.str, vstr.len, 0);
                var_str_clear(&vstr);
                break;
            default:
                var_str_push_back_ch(&vstr, c);
                break;
        }
        var_str_to_3_buf(&vstr, b1, b2, b3, width-2);
        wclear(w_input);
        box(w_input, 0, 0);
        mvwprintw(w_input, 1, 1, "%s", b1);
        mvwprintw(w_input, 2, 1, "%s", b2);
        mvwprintw(w_input, 3, 1, "%s", b3);
        wrefresh(w_input);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: cchat <address> <port> <username>\n");
        exit(5);
    }
    initscr();                  /* Start curses mode must be first */
    noecho();                   /* So that users input does not show up */
    curs_set(0);                /* make cursor invisible */
    // TODO: Is this necessary?
    refresh();                  /* Print it on to the real screen */

    // This pause is necessary when debugging so that we can hook in
    // with gdb while the program waits
    // getch();

    int x_sz, y_sz;
    getmaxyx(stdscr, y_sz, x_sz);
    // we just nab 5 lines for the text entry box,
    // so make sure that it fits lol
    assert(y_sz > 10);
    // w1 will be upper window, w2 will be lower window
    WINDOW *w_disp = newwin(y_sz - 5, x_sz, 0, 0),
           *w_input = newwin(5, x_sz, y_sz - 5, 0);
    box(w_disp, 0, 0);
    box(w_input, 0, 0);
    wrefresh(w_disp);
    wrefresh(w_input);

    // We are going to give this data to w_input_manager
    // so they will free it and we will not touch it again
    struct w_manager_data *wimd = malloc(sizeof(struct w_manager_data));
    wimd->window = w_input;
    int sockfd = open_socket(argv[1], argv[2]);
    wimd->socket_fd = sockfd;

    // first send name
    struct var_str username = var_str_new(1);
    var_str_push_back(&username, argv[3], strlen(argv[3]));
    var_str_push_back_ch(&username, '\n');
    send(sockfd, username.str, username.len, 0);

    pthread_t w_input_th;
    int w_input_th_id = pthread_create(&w_input_th, NULL, w_input_manager, (void *) wimd);

    char msg[32];
    int msg_size = sizeof(msg);
    struct line_buff lb = line_buff_new(y_sz - 7, x_sz - 2);
    while (1) {
        memset(msg, 0, msg_size);
        if (recv(sockfd, msg, msg_size - 1, 0) < 1) {
            printf("Oopsie we got an error reading from the socket :/\n");
            exit(4);
        }
        printf("Hey we got something!\n");
        line_buff_push_back(&lb, msg);

        wclear(w_disp);
        box(w_disp, 0, 0);
        struct line_node *line_string = lb.head->next;
        for (int l_num = 1; l_num < y_sz - 6; l_num++) {
            mvwprintw(w_disp, l_num, 1, "%s", line_string->str);
            line_string = line_string->next;
        }
        wrefresh(w_disp);
    }

    /*
     * This is what I would do if the program had a way to exit nicely.
     * It does not.
    pthread_join(w_input_th, NULL);

    delwin(w_disp);
    delwin(w_input);
    endwin();
    */

	return 0;
}

