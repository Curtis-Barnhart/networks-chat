#ifndef CCHAT_VAR_STR_H
#define CCHAT_VAR_STR_H

#include <assert.h>
#include <stdlib.h>
#include <memory.h>

/**
 * struct to hold a variable length string.
 * len is the length of the string (not counting the null terminator).
 * I'd strongly suggest you read only and not write to this fella.
 */
struct var_str {
    char *str; // internal str buffer
    int len, cap; // cap includes null term, len does not!
};

/**
 * Creates a new var_str struct with capacity capacity.
 *
 * @param capacity initial capacity of var_str.
 * @return new var_str struct with capacity capacity.
 */
struct var_str var_str_new(int capacity);

/**
 * Frees all memory associated with a var_str struct.
 * The struct cannot be used after var_str_del has been called.
 *
 * @param vstr var_str to delete.
 */
void var_str_del(struct var_str *vstr);

/**
 * Copies at most len chars from str into vstr string buffer,
 * terminating if null character encountered.
 *
 * @param vstr the var_str to push str back to.
 * @param str a null terminated string buffer.
 * @param len the length of the string in str (not counting null terminator).
 * @return 0 if success else 1.
 */
int var_str_push_back(struct var_str *vstr, char *str, int len);

/**
 * Pushes back a single character to the string.
 *
 * @param vstr the var_str to push str back to.
 * @param c the char to push back.
 * @return 0 if success else 1.
 */
int var_str_push_back_ch(struct var_str *vstr, char c);

/**
 * Resets the string being help by vstr to be empty.
 *
 * @param vstr the var_str struct to clear.
 */
void var_str_clear(struct var_str *vstr);

#endif // !CCHAT_VAR_STR_H

