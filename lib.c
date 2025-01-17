#include <string.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "var_str.h"
#include "lib.h"

void var_str_to_3_buf(
    struct var_str *vstr,
    char *b1,
    char *b2,
    char *b3,
    int width
) {
    int total = vstr->len,
        lines = total / width,
        remain = total % width,
        skipped;
    if (remain) {
        ++lines;
    }
    skipped = lines > 3 ? (lines - 3)*width : 0;

    // TODO: fix this yeah I know it just made sense at the time I was thinking
    // logically not machinally
    if (remain) {
        --lines;
    }
    if (lines-- > 0) {
        memcpy(b1, vstr->str + skipped, width);
    } else {
        if (remain) {
            memcpy(b1, vstr->str + skipped, remain);
            memset(b1 + remain, ' ', width - remain);
            remain = 0;
        } else {
            memset(b1, ' ', width);
        }
    }
    if (lines-- > 0) {
        memcpy(b2, vstr->str + skipped + width, width);
    } else {
        if (remain) {
            memcpy(b2, vstr->str + skipped + width, remain);
            memset(b2 + remain, ' ', width - remain);
            remain = 0;
        } else {
            memset(b2, ' ', width);
        }
    }
    if (lines-- > 0) {
        memcpy(b3, vstr->str + skipped + 2*width, width);
    } else {
        if (remain) {
            memcpy(b3, vstr->str + skipped + 2*width, remain);
            memset(b3 + remain, ' ', width - remain);
            remain = 0; // technically this isn't necessary?
        } else {
            memset(b3, ' ', width);
        }
    }
}

int open_socket(char *address, char *port) {
    struct addrinfo hints, *res;
    int sockfd;

    // first, load up address structs with getaddrinfo():
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(address, port, &hints, &res)) {
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
    freeaddrinfo(res);
    return sockfd;
}

