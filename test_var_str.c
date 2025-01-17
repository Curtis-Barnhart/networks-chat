#include "var_str.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    char buf1[4] = "Hi!";
    char buf2[13] = " I'm Curtis!";
    char buf3[14] = " How are you?";

    struct var_str test_vstr = var_str_new(1);

    var_str_push_back_ch(&test_vstr, buf1[0]);
    var_str_push_back_ch(&test_vstr, buf1[1]);
    var_str_push_back_ch(&test_vstr, buf1[2]);
    var_str_push_back(&test_vstr, buf2, sizeof(buf2));
    var_str_push_back(&test_vstr, buf3, sizeof(buf3));

    printf("%s\n", test_vstr.str);

    var_str_del(&test_vstr);

    return 0;
}

