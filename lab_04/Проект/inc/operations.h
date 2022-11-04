#ifndef ___MY_OPERATIONS___
#define ___MY_OPERATIONS___

#include "my_types.h"


int get_postfix_expression_arr_stack(char *in_expr, int len, arr_stack_t *stack, char *out_expr);
int get_postfix_expression_list_stack(char *in_expr, int len, list_stack_t *stack, char *out_expr);

#endif // ___MY_OPERATIONS___