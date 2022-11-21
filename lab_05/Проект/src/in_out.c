#include <stdio.h>

#include "../inc/my_def.h"
#include "../inc/my_err.h"
#include "../inc/my_msgs.h"
#include "../inc/my_types.h"


int get_in_elem(FILE *f, double *elem)
{
    char buf;


    if (fscanf(f, "%lf%c", elem, &buf) != 2)
        return ERR_READING;
    if (buf != '\n')
        return ERR_READING;

    return SUCCESS;
}


void print_del_ptrs(double *arr_elem, node_t *del_node)
{
    printf(SUCCESSFULLY_DEL_MSG, GREEN, *arr_elem,
    (void *) arr_elem, (void *) del_node, RESET);
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


void print_queues(list_queue_t *list_queue, arr_queue_t *arr_queue, p_node_t *p_nodes)
{
    draw_line(QUEUE_TABLE_WIDTH);
    printf(QUEUE_TABLE_MSG, PURPLE, RESET, BLUE, RESET);
    draw_line(QUEUE_TABLE_WIDTH);

    node_t *cur = list_queue->top;


    for (int i = 0, j = p_nodes->len - 1; i < list_queue->len || j >= 0; ++i, --j)
    {
        if (j >= 0 && i < list_queue->len)
        {
            printf("|%s|%*lf|%*p|%s|%s|%*lf|%*p|%*p|%s|\n", PURPLE, FIRST_FIELD_WIDTH,
            arr_queue->content[i], SECOND_FIELD_WIDTH, (void *) &(arr_queue->content[i]),
            RESET, BLUE, FIRST_FIELD_WIDTH, cur->item, SECOND_FIELD_WIDTH,
            (void *) &(cur->item), THIRD_FIELD_WIDTH, (void *) p_nodes->p_nodes[j], RESET);

            cur = cur->next;
        }
        else if (j >= 0 && i >= list_queue->len)
            printf("|%s|%*c|%*c|%s|%s|%*c|%*c|%*p|%s|\n", PURPLE, FIRST_FIELD_WIDTH,
            ' ', SECOND_FIELD_WIDTH, ' ', RESET, BLUE, FIRST_FIELD_WIDTH, ' ',
            SECOND_FIELD_WIDTH, ' ', THIRD_FIELD_WIDTH, (void *) p_nodes->p_nodes[j], RESET);
        else
        {
            printf("|%s|%*lf|%*p|%s|%s|%*lf|%*p|%*c|%s|\n", PURPLE, FIRST_FIELD_WIDTH,
            arr_queue->content[i], SECOND_FIELD_WIDTH, (void *) &(arr_queue->content[i]),
            RESET, BLUE, FIRST_FIELD_WIDTH, cur->item, SECOND_FIELD_WIDTH,
            (void *) &(cur->item), THIRD_FIELD_WIDTH, ' ', RESET);

            cur = cur->next;
        }
    }

    draw_line(QUEUE_TABLE_WIDTH);
}


void print_measures(measurement_table *table, int len)
{
    printf(ARR_QUEUE_MSG, PURPLE, RESET);

    draw_line(MEAS_TABLE_WIDTH);
    printf(MEASURE_TABLE_MSG, BLUE, RESET);
    draw_line(MEAS_TABLE_WIDTH);

    for (int i = 0; i < len / 2; i += 2)
        printf("|%*d|%*llu|%*llu|%*d|\n", FIRST_SECOND_MEAS_FIELD_WIDTH, table[i].queue_len,
        FIRST_SECOND_MEAS_FIELD_WIDTH, table[i].time, THIRD_MEAS_FIELD_WIDTH, table[i + 1].time,
        FOURTH_MEAS_FIELD_WIDTH, table[i].mem);
    
    draw_line(MEAS_TABLE_WIDTH);


    printf(LIST_QUEUE_MSG, PURPLE, RESET);

    draw_line(MEAS_TABLE_WIDTH);
    printf(MEASURE_TABLE_MSG, BLUE, RESET);
    draw_line(MEAS_TABLE_WIDTH);

    for (int i = len / 2; i < len; i += 2)
        printf("|%*d|%*llu|%*llu|%*d|\n", FIRST_SECOND_MEAS_FIELD_WIDTH, table[i].queue_len,
        FIRST_SECOND_MEAS_FIELD_WIDTH, table[i].time, THIRD_MEAS_FIELD_WIDTH, table[i + 1].time,
        FOURTH_MEAS_FIELD_WIDTH, table[i].mem);
    
    draw_line(MEAS_TABLE_WIDTH);
}