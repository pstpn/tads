#include <stdio.h>

#include "../inc/my_def.h"
#include "../inc/my_err.h"
#include "../inc/my_msgs.h"
#include "../inc/my_types.h"


int get_in_elem(FILE *f, char *elem)
{
    char buf;


    if (fscanf(f, "%c%c", elem, &buf) != 2)
        return ERR_READING;
    if (buf != '\n')
        return ERR_READING;

    return SUCCESS;
}


void print_del_ptrs(char *arr_elem, node_t *del_node)
{
    printf(SUCCESSFULLY_DEL_MSG, GREEN, *arr_elem,
    (void *) arr_elem, (void *) del_node, RESET);
}


int get_in_expression(char *in_str, int n, int *len)
{
    int ch;


    while ((ch = getchar()) != '\n')
        if (*len < n - 1)
            in_str[(*len)++] = ch;
        else
            return ERR_OVERFLOW;

    in_str[*len] = '\0';

    return SUCCESS;
}


void clear_buf(FILE *f)
{
    char buf = '\0';

    
    while (buf != '\n')
        buf = fgetc(f);
}


void draw_line(int len)
{
    for (int i = 0; i < len; ++i)
        printf("-");
    printf("\n");
}


void print_stacks(list_stack_t *list_stack, arr_stack_t *arr_stack)
{
    draw_line(STACKS_TABLE_LEN);
    printf(STACKS_TABLE_MSG, PURPLE, RESET, BLUE, RESET);
    draw_line(STACKS_TABLE_LEN);

    node_t *cur = list_stack->top;


    for (int i = list_stack->len - 1; i >= 0; --i)
    {
        printf("|%s|%*c|%*p|%s|%s|%*c|%*p|%s|\n", PURPLE, FIRST_FIELD_LEN,
        arr_stack->content[i], SECOND_FIELD_LEN, &(arr_stack->content[i]),
        RESET, BLUE, THIRD_FIELD_LEN, cur->item, SECOND_FIELD_LEN,
        &(cur->item), RESET);

        cur = cur->next;
    }

    draw_line(STACKS_TABLE_LEN);
}