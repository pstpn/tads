#ifndef ___MY_IN_OUT___
#define ___MY_IN_OUT___

#include <stdio.h>

#include "my_types.h"


// int get_in_elem(FILE *f, char *elem);
void clear_buf(FILE *f);
void draw_line(int len);
void print_hash_table(hash_table_t *hash_table);
void print_list_hash_table(hash_table_t *hash_table);
// void print_measures(measurement_table *table, int len);

#endif // ___MY_IN_OUT___