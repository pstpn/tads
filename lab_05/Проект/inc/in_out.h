#ifndef ___IN_OUT___
#define ___IN_OUT___

#include <stdio.h>

#include "my_types.h"


int get_in_elem(FILE *f, double *elem);
void print_del_ptrs(char *arr_elem, node_t *del_node);
void clear_buf(FILE *f);
void draw_line(int len);
void print_queues(list_queue_t *list_queue, arr_queue_t *arr_queue, p_node_t *p_nodes);
// void print_measures(measurement_table *table, int len);

#endif // ___IN_OUT___