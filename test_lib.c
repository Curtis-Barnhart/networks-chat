#include <stdio.h>

#include "lib.h"

int main(int argc, char *argv[]) {
    char buf[97] = 
        "0123456789"
        "1123456789"
        "2123456789"
        "3123456789"
        "4123456789"
        "5123456789"
        "6123456789"
        "7123456789"
        "8123456789"
        "912345";
    struct var_str vstr = var_str_new(100);
    var_str_push_back(&vstr, buf, 96);
    char b1[11], b2[11], b3[11];

    var_str_to_3_buf(&vstr, b1, b2, b3, 10);
    printf("%s\n", b1);
    printf("%s\n", b2);
    printf("%s\n", b3);
    printf("---------------\n");

    var_str_clear(&vstr);
    var_str_push_back(&vstr, &buf[70], 26);
    var_str_to_3_buf(&vstr, b1, b2, b3, 10);
    printf("%s\n", b1);
    printf("%s\n", b2);
    printf("%s\n", b3);
    printf("---------------\n");

    var_str_clear(&vstr);
    var_str_push_back(&vstr, &buf[80], 16);
    var_str_to_3_buf(&vstr, b1, b2, b3, 10);
    printf("%s\n", b1);
    printf("%s\n", b2);
    printf("%s\n", b3);
    printf("---------------\n");

    var_str_clear(&vstr);
    var_str_push_back(&vstr, &buf[90], 66);
    var_str_to_3_buf(&vstr, b1, b2, b3, 10);
    printf("%s\n", b1);
    printf("%s\n", b2);
    printf("%s\n", b3);

    return 0;
}
