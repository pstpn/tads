#ifndef ___LIST_STACK_FUNCS___
#define ___LIST_STACK_FUNCS___

#include <stdbool.h>

#include "my_types.h"


list_stack_t *create_list_stack(void);
bool is_list_stack_empty(const list_stack_t *s);
bool is_list_stack_full(const list_stack_t *s);
int push_list_stack(list_stack_t *s, char elem);
int pop_list_stack(list_stack_t *s, char *pop_elem);
void destroy_list_stack(list_stack_t *s);

#endif // ___LIST_STACK_FUNCS___