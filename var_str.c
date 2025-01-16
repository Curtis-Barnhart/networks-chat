#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

struct var_str {
    char *str; // internal str buffer
    int len, cap; // cap includes null term, len does not!
};

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

/**
 * Copies at most len chars from str into vstr string buffer,
 * terminating if null character encountered.
 *
 * @param vstr the var_str to push str back to
 * @param str a null terminated string buffer
 * @param len the length of the string in str
 * @return 0 if success else 1
 */
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

int var_str_clear(struct var_str *vstr) {
    vstr->len = 0;
    vstr->str[0] = '\0';
}

