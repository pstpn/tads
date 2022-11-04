#ifndef ___IN_OUT___
#define ___IN_OUT___

#include <stdio.h>


int get_in_elem(FILE *f, char *elem);
void print_del_ptrs(char *arr_elem, node_t *del_node);
int get_in_expression(char *in_str, size_t n, int *len);
void clear_buf(FILE *f);

#endif // ___IN_OUT___