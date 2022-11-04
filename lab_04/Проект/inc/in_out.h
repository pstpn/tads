#ifndef ___IN_OUT___
#define ___IN_OUT___

#include <stdio.h>


int get_in_elem(FILE *f, char *elem);
void print_del_ptrs(char *arr_elem, node_t *del_node);
int get_in_expression(char *in_str, size_t n, int *len);
void clear_buf(FILE *f);
void draw_line(int len);
void print_stacks(list_stack_t *list_stack, arr_stack_t *arr_stack);

#endif // ___IN_OUT___