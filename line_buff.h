#ifndef CCC_LINE_BUFF_H
#define CCC_LINE_BUFF_H

/**
 * capacity includes the null terminator.
 */
struct line_node {
    struct line_node *prev, *next;
    char *str;
    // int capacity;
};

/**
* Create new line_node struct.
*
* @param capacity capacity of line (including null terminator)
* @return a new line_node struct.
*/
struct line_node line_node_new(int capacity);

/**
* Free all memory associated with a line_node struct.
*
* @param ln the line_node object to destroy.
*/
void line_node_del(struct line_node *ln);

/**
 * width includes the null terminator.
 */
struct line_buff {
    int len, width, index_into_line;
    struct line_node *head;
};

/**
* Create a new line_buff struct.
*
* @param capacity the number of lines for the buffer to hold.
* @param line_length the length of each line in the buffer
*     (including null terminator).
* @ return the new line_buff struct.
*/
struct line_buff line_buff_new(int capacity, int line_length);

/**
* Free all memory associated with a line_buff struct.
*
* @param lb the line_buff object to destroy.
*/
void line_buff_del(struct line_buff *lb);

/**
* Add more text to the line buffer.
*
* @param lb the line_buff object to add text to.
* @param str the string to add.
*/
void line_buff_push_back(struct line_buff *lb, char *str);

#endif // !CCC_LINE_BUFF_H

