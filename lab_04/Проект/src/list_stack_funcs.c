#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../inc/my_types.h"
#include "../inc/my_def.h"
#include "../inc/my_err.h"


list_stack_t *create_list_stack(void)
{
    list_stack_t *s;
    s = malloc(sizeof(list_stack_t));


    if (s)
        s->len = 0;

    return s;
}


bool is_list_stack_empty(const list_stack_t *s)
{
    return s->len == 0;
}


bool is_list_stack_full(const list_stack_t *s)
{
    return s->len >= STACK_SIZE;
}


int push_list_stack(list_stack_t *s, char elem)
{
    node_t *node = malloc(sizeof(node_t));

    if (!node)
        return ERR_ALLOC;

    if (is_list_stack_full(s))
        return ERR_OVERFLOW;

    node->next = s->top;
    node->item = elem;

    s->top = node;

    ++(s->len);

    return SUCCESS;
}


int pop_list_stack(list_stack_t *s, char *pop_elem)
{
    if (is_list_stack_empty(s))
        return EMPTY_STACK;

    node_t *node;


    *pop_elem = s->top->item;

    node = s->top;

    s->top = node->next;

    --(s->len);

    free(node);

    return SUCCESS;
}


void destroy_list_stack(list_stack_t *s)
{
    char item;


    while (!is_list_stack_empty(s))
        pop_list_stack(s, &item);

    free(s);
}


void del_dublicates(list_stack_t *list_stack, p_node_t *p_nodes)
{
    for (int i = p_nodes->len; i >= 0; --i)
    {
        node_t *cur = list_stack->top;


        for (int j = 0; j < list_stack->len; ++j, cur = cur->next)
        {
            if (cur == p_nodes->p_nodes[i])
            {
                for (int k = i; k < p_nodes->len - 1; ++k)
                    p_nodes->p_nodes[k] = p_nodes->p_nodes[k + 1];
                
                --p_nodes->len;
            }

            break;
        }
    }
}