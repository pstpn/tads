/**
 * @file main.c
 * @author Stepan Postnov ICS7-31B
 * @brief 
 * 
 *                     TASK:
 * 
 *                    Вариант 3
 * 
 * Перевести выражение в постфиксную форму
 * 
 * @version 0.1
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/my_types.h"
#include "../inc/my_msgs.h"
#include "../inc/my_err.h"
#include "../inc/list_funcs.h"
#include "./inc/arr_funcs.h"


int main(void)
{
    int key = -1;

    arr_queue_t *arr_queue = create_arr_queue();
    if (!arr_queue)
    {
        printf(ERR_ALLOC_MSG, RED, RESET);
        return ERR_ALLOC;
    }

    list_queue_t *list_queue = create_list_queue();
    if (!list_queue)
    {
        printf(ERR_ALLOC_MSG, RED, RESET);
        destroy_arr_queue(arr_queue);
        return ERR_ALLOC;
    }

    p_node_t p_nodes;
    memset(p_nodes.p_nodes, 0, QUEUE_SIZE * sizeof(node_t *));
    p_nodes.len = 0;


    printf(INFO_MSG);
    
    while (key != 0)
    {
        printf(MENU_MSG);

        if (fscanf(stdin, "%d", &key) != 1 ||
        key < 0 || key > MENU_LEN)
        {
            printf(ERR_CODE_MSG, RED, RESET);
            destroy_list_queue(list_queue);
            destroy_arr_queue(arr_queue);
            return ERR_CODE;
        }

        switch (key)
        {
            case 0:
            {
                destroy_list_queue(list_queue);
                destroy_arr_queue(arr_queue);
                return SUCCESS;
            }
            case 1:
            {
                print_queues(list_queue, arr_queue, &p_nodes);
                
                break;
            }
            case 2:
            {
                clear_buf(stdin);

                if (list_queue->len >= QUEUE_SIZE ||
                    arr_queue->len >= QUEUE_SIZE)
                {
                    printf(ERR_QUEUE_IS_FULL_MSG, RED, RESET);
                    clear_buf(stdin);
                    break;
                }

                double elem;


                printf(INPUT_ELEM_MSG);

                if (get_in_elem(stdin, &elem))
                {
                    printf(ERR_READING_STDIN_MSG, RED, RESET);
                    clear_buf(stdin);
                    break;
                }
                
                node_t *new_node = calloc(1, sizeof(node_t));
                if (!new_node)
                {
                    printf(ERR_ALLOC_MSG, RED, RESET);
                    destroy_list_queue(list_queue);
                    destroy_arr_queue(arr_queue);
                    return ERR_ALLOC;
                }

                
                new_node->item = elem;
                new_node->next = NULL;

                push_list_queue(&list_queue, new_node);
                push_arr_queue(arr_queue, elem);

                if (p_nodes.len)
                    del_dublicates(list_queue, &p_nodes);

                printf(SUCCESSFULLY_ADD_MSG, GREEN, RESET);

                break;
            }
            case 3:
            {
                if (!list_queue->len || !arr_queue->len)
                {
                    printf(ERR_QUEUE_IS_EMPTY_MSG, RED, RESET);
                    clear_buf(stdin);
                    break;
                }

                double pop_elem;


                print_del_ptrs(&(arr_queue->content[arr_queue->len - 1]), list_queue->top);

                p_nodes.p_nodes[(p_nodes.len)++] = list_queue->top;
                
                pop_list_queue(list_queue, &pop_elem);
                pop_arr_queue(arr_queue, &pop_elem);

                break;
            }
            case 4:
            {
                clear_buf(stdin);

                char ans;


                printf(INPUT_STACK_TYPE);
                fscanf(stdin, "\n%c", &ans);
                if (ans == '1')
                {
                    clear_buf(stdin);

                    // TO DO
                }
                else if (ans == '2')
                {
                    clear_buf(stdin);

                    // TO DO
                }
                else
                {
                    printf(ERR_CODE_MSG, RED, RESET);
                    clear_buf(stdin);
                }

                break;
            }
            case 5:
            {
                // TO DO

                // measurement_table measures[MEAS_LEN * 2] = { 0 };


                // if (get_measures(measures))
                // {
                //     printf(ERR_MEASURES_MSG, RED, RESET);
                //     break;
                // }

                // print_measures(measures, MEAS_LEN * 2);

                // break;
            }
        }
    }
    
    return SUCCESS;
}
