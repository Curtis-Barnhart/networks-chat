#include <stdio.h>

#include "line_buff.h"

int main(int argc, char *argv[]) {
    char b1[6] = "Hello",
         b2[8] = " world!",
         b3[27] = " How are you doing today?\n",
         b4[24] = "I'm doing fine,\nthanks!";
         
    struct line_buff lb = line_buff_new(3, 16);
    printf("%s\n", lb.head->next->str);
    printf("%s\n", lb.head->next->next->str);
    printf("%s\n", lb.head->str);
    printf("------------------\n");

    line_buff_push_back(&lb, b1);
    printf("%s\n", lb.head->next->str);
    printf("%s\n", lb.head->next->next->str);
    printf("%s\n", lb.head->str);
    printf("------------------\n");

    line_buff_push_back(&lb, b2);
    printf("%s\n", lb.head->next->str);
    printf("%s\n", lb.head->next->next->str);
    printf("%s\n", lb.head->str);
    printf("------------------\n");
    
    line_buff_push_back(&lb, b3);
    printf("%s\n", lb.head->next->str);
    printf("%s\n", lb.head->next->next->str);
    printf("%s\n", lb.head->str);
    printf("------------------\n");

    line_buff_push_back(&lb, b4);
    printf("%s\n", lb.head->next->str);
    printf("%s\n", lb.head->next->next->str);
    printf("%s\n", lb.head->str);
    
    line_buff_del(&lb);

    return 0;
}

