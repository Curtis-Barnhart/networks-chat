#ifndef CCHAT_LIB_H
#define CCHAT_LIB_H

#include "var_str.h"

/**
* var_str_to_3_buf takes a var_str and writes it into a set of three buffers
* such that each buffer contains consecutive lines of text
* and the last buffer contains the last character from vstr.
*
* @param vstr pointer to var_str to write into the three buffers.
* @param b1 the first char buffer.
* @param b2 the second char buffer.
* @param b3 the third char buffer.
* @param width the width of the three buffers (not counting null terminator)
*/
void var_str_to_3_buf(
    struct var_str *vstr,
    char *b1,
    char *b2,
    char *b3,
    int width
);

#endif // !CCHAT_LIB_H

