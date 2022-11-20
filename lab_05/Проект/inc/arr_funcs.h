#ifndef ___MY_ARR_FUNCS___
#define ___MY_ARR_FUNCS___

#include "my_types.h"


arr_queue_t *create_arr_queue(void);
void push_arr_queue(arr_queue_t *s, double elem);
int pop_arr_queue(arr_queue_t *s, double *pop_elem);
void destroy_arr_queue(arr_queue_t *s);

#endif // ___MY_ARR_FUNCS___