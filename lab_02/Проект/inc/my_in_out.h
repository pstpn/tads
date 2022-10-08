#ifndef ___MY_IN_OUT___
#define ___MY_IN_OUT___

#include <stdio.h>

#include "my_types.h"


void write_in_file(FILE *f, car_info car, int count);
int get_str(FILE *f, char *str, int max_len, char sep);
int get_tables(FILE *f, car_info table[], help_table index_table[], int *count);


#endif // ___MY_IN_OUT___