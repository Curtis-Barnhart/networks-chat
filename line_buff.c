#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "line_buff.h"

struct line_node line_node_new(int capacity) {
    assert(capacity > 0);

    struct line_node n;
    n.next = NULL, n.prev = NULL;
    // n.capacity = capacity;
    n.str = malloc(capacity);
    n.str[0] = '\0';
    n.str[capacity - 1] = '\0';
    return n;
}

void line_node_del(struct line_node *ln) {
    free(ln->str);
}

struct line_buff line_buff_new(int capacity, int line_length) {
    assert(capacity > 0);
    assert(line_length > 0);

    struct line_node *temp = malloc(sizeof(struct line_node)),
                     *last;
    struct line_buff lb;
    lb.head = temp;
    *lb.head = line_node_new(line_length);
    lb.index_into_line = 0;
    lb.width = line_length;
    last = lb.head;
    --capacity;

    while (capacity-- > 0) {
        temp = malloc(sizeof(struct line_node));
        *temp = line_node_new(line_length);
        temp->prev = last;
        last->next = temp;
        last = temp;
    }
    lb.head->prev = last;
    last->next = lb.head;

    return lb;
}

void line_buff_del(struct line_buff *lb) {
    struct line_node *curr,
                     *next = lb->head->next;
    do {
        curr = next;
        next = curr->next;
        line_node_del(curr);
        free(curr);
    } while (curr != lb->head);
}

void line_buff_push_back(struct line_buff *lb, char *str) {
    while (1) { // for each char
        switch (*str) {
            case '\0':
                if (lb->index_into_line == lb->width - 1) {
                    // if this line was already full, perfect!
                    return;
                } else {
                    // stop for now
                    lb->head->str[lb->index_into_line] = '\0';
                    return;
                }
                break;
            case '\n':
                if (lb->index_into_line == lb->width - 1) {
                    // if this line was already full, perfect!
                } else {
                    // cut string short and pretend the line is full
                    lb->head->str[lb->index_into_line] = '\0';
                    lb->index_into_line = lb->width - 1;
                }
                ++str;
                break;
            default:
                if (lb->index_into_line == lb->width - 1) {
                    // if this line was already full, get a new one
                    lb->head = lb->head->next;
                    memset(lb->head->str, 0, lb->width - 1);
                    lb->head->str[0] = *str;
                    lb->index_into_line = 1;
                } else {
                    // just add the char
                    lb->head->str[lb->index_into_line++] = *str;
                }
                ++str;
                break;
        }
    }
}

