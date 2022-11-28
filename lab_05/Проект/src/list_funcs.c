#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/my_types.h"
#include "../inc/my_err.h"


list_queue_t *create_list_queue(void)
{
    list_queue_t *s;
    s = malloc(sizeof(list_queue_t));


    if (s)
    {
        s->top = NULL;
        s->last = NULL;
        s->len = 0;
    }

    return s;
}


void push_list_queue(list_queue_t **s, node_t *new_node)
{
    if (!(*s)->top)
    {
        (*s)->top = new_node;
        (*s)->last = new_node;
    }
    else
    {
        (*s)->last->next = new_node;
        (*s)->last = new_node;
    }

    ++(*s)->len;
}


void pop_list_queue(list_queue_t *s, double *pop_elem)
{
    node_t *node;


    *pop_elem = s->top->item;

    node = s->top;

    s->top = node->next;

    --(s->len);

    free(node);
}


void destroy_list_queue(list_queue_t *s)
{
    double item;


    while (s->len)
        pop_list_queue(s, &item);

    free(s);
}


void del_dublicates(list_queue_t *list_queue, p_node_t *p_nodes)
{
    for (int i = p_nodes->len; i >= 0; --i)
    {
        node_t *cur = list_queue->top;


        for (int j = 0; j < list_queue->len; ++j, cur = cur->next)
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