#include <stdbool.h>

#include "../inc/my_types.h"
#include "../inc/my_err.h"


arr_stack_t *create_arr_stack(void)
{
    arr_stack_t *s = malloc(sizeof(arr_stack_t));

    if (s)
        s->len = 0;

    return s;
}


void destroy_arr_stack(arr_stack_t *s)
{
    free(s);
}


bool is_arr_stack_empty(const arr_stack_t *s)
{
    return s->len == 0;
}


bool is_arr_stack_full(const arr_stack_t *s)
{
    return s->len >= STACK_SIZE;
}


int push_arr_stack(arr_stack_t *s, char elem)
{
    if (is_arr_stack_full(s))
        return OVERFLOW;

    s->content[(s->len)++] = elem;

    return SUCCESS;
}


int pop_arr_stack(arr_stack_t *s, char *pop_elem)
{
    if (is_arr_stack_empty(s))
        return EMPTY_STACK;

    *pop_elem = s->content[--(s->len)];

    return SUCCESS;
}