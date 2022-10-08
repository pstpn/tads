#ifndef ___MY_PRINT___
#define ___MY_PRINT___

#include "my_types.h"


void draw_line(int len);
void draw_name(char *table_name, int table_width);
void print_car(car_info car);
void print_cars(car_info cars[], int count);
void print_keys(help_table index_table[],int count);
void print_cars_using_keys(car_info cars[], help_table inds[], int count);
void print_measures(measurement_table measures[]);

#endif // ___MY_PRINT___