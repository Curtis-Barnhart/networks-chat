#include <string.h>

#include "var_str.h"

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

