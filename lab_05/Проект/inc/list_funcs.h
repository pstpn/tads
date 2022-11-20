#ifndef ___LIST_FUNCS___
#define ___LIST_FUNCS___

#include "my_types.h"


list_queue_t *create_list_queue(void);
void push_list_queue(list_queue_t **s, node_t *new_node);
void pop_list_queue(list_queue_t *s, double *pop_elem);
void destroy_list_queue(list_queue_t *s);
void del_dublicates(list_queue_t *list_queue, p_node_t *p_nodes);

#endif // ___LIST_FUNCS___