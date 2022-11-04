#ifndef ___ARR_STACK_FUNCS___
#define ___ARR_STACK_FUNCS___

#include <stdbool.h>

#include "my_types.h"


arr_stack_t *create_arr_stack(void);
void destroy_arr_stack(arr_stack_t *s);
bool is_arr_stack_empty(const arr_stack_t *s);
bool is_arr_stack_full(const arr_stack_t *s);
int push_arr_stack(arr_stack_t *s, char elem);
int pop_arr_stack(arr_stack_t *s, char *pop_elem);

#endif // ___ARR_STACK_FUNCS___