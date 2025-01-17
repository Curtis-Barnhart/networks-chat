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

    b1[0] = '\0', b2[0] = '\0', b3[0] = '\0';

    if (lines-- > 0) {
        strncpy(b1, vstr->str + skipped, width + 1);
    }
    if (lines-- > 0) {
        strncpy(b2, vstr->str + skipped + width, width + 1);
    }
    if (lines-- > 0) {
        strncpy(b3, vstr->str + skipped + 2*width, width + 1);
    }
}

