#ifndef ___MY_MODELING___
#define ___MY_MODELING___

#include "my_types.h"


void init_arr_queue(arr_queue_t *arr_queue, int size);
int init_list_queue(list_queue_t *list_queue, int size);
double get_random_double(double min, double max);
int arr_modeling(process_info_t process_info);
int list_modeling(process_info_t process_info);

#endif // ___MY_MODELING___