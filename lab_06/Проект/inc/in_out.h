#ifndef ___MY_IN_OUT___
#define ___MY_IN_OUT___

#include "my_types.h"


int get_in_elem(FILE *f, char *elem);
void clear_buf(FILE *f);
void draw_line(int len);
void print_tree_node_info(void *tree, void *param);

#endif // ___MY_IN_OUT___