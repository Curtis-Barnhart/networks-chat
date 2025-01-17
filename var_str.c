#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "var_str.h"

struct var_str var_str_new(int capacity) {
    assert(capacity > 0);
    struct var_str vstr;
    vstr.cap = capacity;
    vstr.len = 0;
    vstr.str = malloc(capacity);
    vstr.str[0] = '\0';
    return vstr;
}

void var_str_del(struct var_str *vstr) {
    free(vstr->str);
}

int var_str_push_back(struct var_str *vstr, char *str, int len) {
    if (len < 1) { return 0; }
    if ((vstr->cap - vstr->len - 1) < len) {
        while (((vstr->cap = vstr->cap * 2) - vstr->len - 1) < len);
        if ((vstr->str = realloc(vstr->str, vstr->cap)) == NULL) {
            return 1;
        }
    }
    char *dst = vstr->str + vstr->len;
    while ((*dst++ = *str++) && ++vstr->len && (--len > 0));
    *dst = '\0';
    return 0;
}

int var_str_push_back_ch(struct var_str *vstr, char c) {
    char buf[2];
    buf[0] = c, buf[1] = '\0';
    return var_str_push_back(vstr, buf, 1);
}

char var_str_pop_back_ch(struct var_str *vstr) {
    if (vstr->len > 0) {
        char c = vstr->str[--vstr->len];
        vstr->str[vstr->len] = '\0';
        return c;
    } else {
        return '\0';
    }
}

void var_str_clear(struct var_str *vstr) {
    vstr->len = 0;
    vstr->str[0] = '\0';
}

