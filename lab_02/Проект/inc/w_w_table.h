#ifndef ___MY_W_W_TABLE___
#define ___MY_W_W_TABLE___

#include <stdio.h>

#include "my_types.h"


int finding_info(car_info cars[], int count);
int adding_car_in_table(FILE *f, car_info *car, int *count);
int delete_cars(car_info cars[], help_table inds[], int *count);
void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

#endif // ___MY_W_W_TABLE___