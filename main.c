#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "var_str.c"

int open_socket() {
    struct addrinfo hints, *res;
    int sockfd;

    // first, load up address structs with getaddrinfo():
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    // if (getaddrinfo("10.90.132.102", "31337", &hints, &res)) {
    if (getaddrinfo("vmwardrobe.westmont.edu", "49153", &hints, &res)) {
        fprintf(stderr, "Oopsie we got an error getting address information :/\n");
        exit(1);
    }
    fprintf(stderr, "Address information acquired.\n");

    // make a socket:
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    // connect!
    if (connect(sockfd, res->ai_addr, res->ai_addrlen)) {
        fprintf(stderr, "Oopsie we got an error connecting to the socket :/\n");
        exit(2);
    }
    fprintf(stderr, "Connection successfully made!\n");
    freeaddrinfo(res);
    return sockfd;
}

void *write_loop(void *data) {
    int sockfd = *(int *) data;
    struct var_str vstr = var_str_new(1);
    char msg[10];
    int msg_size = sizeof(msg);

    while (1) {
        var_str_clear(&vstr);
        msg[msg_size - 1] = '!'; // reset last char to detect if buffer is full
        msg[msg_size - 2] = '!'; // reset last char to detect if buffer is full
        while (1) {
            fgets(msg, msg_size, stdin);
            int read_ct = strlen(msg);
            var_str_push_back(&vstr, msg, read_ct);
            if (read_ct < msg_size - 1 || msg[msg_size - 2] == '\n') {
                break;
            }
        }
        if (send(sockfd, vstr.str, vstr.len, 0) == -1) {
            fprintf(stderr, "Oopsie we got an error sending to the socket :/\n");
            var_str_del(&vstr);
            exit(3);
        }
    }
}

int main(int argc, char *argv[]) {
    int sockfd = open_socket();
    char msg[10];
    int msg_size = sizeof(msg);
    int sock_buf_size = 0;

    pthread_t writer;
    int thread_id = pthread_create(&writer, NULL, write_loop, (void *) &sockfd);

    while (1) {
        memset(msg, 0, msg_size);
        if (recv(sockfd, msg, msg_size - 1, 0) < 1) {
            printf("Oopsie we got an error reading from the socket :/\n");
            exit(4);
        }
        printf("%s", msg);
    }
 
    return 0;
}

