#include <stdlib.h>

#include "../inc/my_types.h"
#include "../inc/my_def.h"
#include "../inc/my_err.h"


arr_queue_t *create_arr_queue(void)
{
    arr_queue_t *s = malloc(sizeof(arr_queue_t));

    if (s)
        s->len = 0;

    return s;
}


void push_arr_queue(arr_queue_t *s, double elem)
{
    s->content[(s->len)++] = elem;
}


int pop_arr_queue(arr_queue_t *s, double *pop_elem)
{
    *pop_elem = s->content[0];

    for (int i = 1; i < s->len; ++i)
        s->content[i - 1] = s->content[i];

    --(s->len);

    return SUCCESS;
}


void destroy_arr_queue(arr_queue_t *s)
{
    free(s);
}