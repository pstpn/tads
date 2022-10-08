#ifndef ___MY_TOOLS___
#define ___MY_TOOLS___

#include <stdio.h>

#include "my_types.h"


void clear_buf(FILE *f);
int compare_prices(const void *p_1, const void *p_2);
int key_compare_prices(const void *p_1, const void *p_2);
void deep_cpy(void *dst, void *base, int count, int size);
void transpose_at_the_end(void *cars, int ind, int size, int *count);
void restore_key_table(help_table keys[], car_info cars[], int count);

#endif // ___MY_TOOLS___