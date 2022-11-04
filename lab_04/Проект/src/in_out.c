#include <stdio.h>

#include "../inc/my_err.h"
#include "../inc/my_msgs.h"
#include "../inc/my_types.h"


int get_in_elem(FILE *f, char *elem)
{
    if (fscanf(f, "%c\n", elem) != 1)
    {
        fflush(f);
        return ERR_READING;
    }

    return SUCCESS;
}


void print_del_ptrs(char *arr_elem, node_t *del_node)
{
    printf(SUCCESSFULLY_DEL_MSG, *arr_elem,
    arr_elem, del_node);
}