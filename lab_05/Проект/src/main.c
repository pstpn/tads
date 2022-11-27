/**
 * @file main.c
 * @author Stepan Postnov ICS7-31B
 * @brief 
 * 
 *                     TASK:
 * 
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
#include "../inc/arr_funcs.h"
#include "../inc/modeling.h"
#include "../inc/in_out.h"
#include "../inc/my_measure.h"


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

    process_info_t process_info;


    process_info.first_machine_min_work_time = FIRST_MACHINE_MIN_WORK_TIME;
    process_info.first_machine_max_work_time = FIRST_MACHINE_MAX_WORK_TIME;

    process_info.second_machine_min_work_time = SECOND_MACHINE_MIN_WORK_TIME;
    process_info.second_machine_max_work_time = SECOND_MACHINE_MAX_WORK_TIME;

    process_info.prob = PROB;


    printf(INFO_MSG);
    
    while (key != 0)
    {
        printf(MENU_MSG,
        process_info.first_machine_min_work_time,
        process_info.first_machine_max_work_time,
        process_info.second_machine_min_work_time,
        process_info.second_machine_max_work_time,
        process_info.prob * 10);

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


                print_del_ptrs(&(arr_queue->content[0]), list_queue->top);

                p_nodes.p_nodes[(p_nodes.len)++] = list_queue->top;
                
                pop_list_queue(list_queue, &pop_elem);
                pop_arr_queue(arr_queue, &pop_elem);

                break;
            }
            case 4:
            {
                clear_buf(stdin);

                char ans;


                printf(INPUT_QUEUE_TYPE_MSG);
                fscanf(stdin, "\n%c", &ans);
                if (ans == '1')
                {
                    clear_buf(stdin);

                    if (arr_modeling(process_info))
                    {
                        printf(ERR_ALLOC_MSG, RED, RESET);
                        return ERR_ALLOC;
                    }
                }
                else if (ans == '2')
                {
                    clear_buf(stdin);

                    if (list_modeling(process_info))
                    {
                        printf(ERR_ALLOC_MSG, RED, RESET);
                        return ERR_ALLOC;
                    }
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
                measurement_table measures[MEAS_COUNT] = { 0 };


                if (get_measures(measures))
                {
                    printf(ERR_MEASURES_MSG, RED, RESET);
                    return ERR_ALLOC;
                }

                print_measures(measures, MEAS_COUNT);

                break;
            }
            case 6:
            {
                int buf_1, buf_2;


                printf(INPUT_MIN_MACHINE_TIME_MSG);
                if (fscanf(stdin, "%d", &(buf_1)) != 1)
                {
                    printf(ERR_READING_STDIN_MSG, RED, RESET);
                    clear_buf(stdin);
                    break;
                }

                printf(INPUT_MAX_MACHINE_TIME_MSG);
                if (fscanf(stdin, "%d", &(buf_2)) != 1 ||
                    buf_1 > buf_2)
                {
                    printf(ERR_READING_STDIN_MSG, RED, RESET);
                    clear_buf(stdin);
                    break;
                }

                process_info.first_machine_min_work_time = buf_1;
                process_info.first_machine_max_work_time = buf_2;

                break;
            }
            case 7:
            {
                int buf_1, buf_2;


                printf(INPUT_MIN_MACHINE_TIME_MSG);
                if (fscanf(stdin, "%d", &(buf_1)) != 1)
                {
                    printf(ERR_READING_STDIN_MSG, RED, RESET);
                    clear_buf(stdin);
                    break;
                }

                printf(INPUT_MAX_MACHINE_TIME_MSG);
                if (fscanf(stdin, "%d", &(buf_2)) != 1 ||
                    buf_1 > buf_2)
                {
                    printf(ERR_READING_STDIN_MSG, RED, RESET);
                    clear_buf(stdin);
                    break;
                }

                process_info.second_machine_min_work_time = buf_1;
                process_info.second_machine_max_work_time = buf_2;

                break;
            }
            case 8:
            {
                double buf;


                printf(INPUT_PROB_MSG);
                if (fscanf(stdin, "%lf", &(buf)) != 1 ||
                    buf < 0 || buf > 100)
                {
                    printf(ERR_READING_STDIN_MSG, RED, RESET);
                    clear_buf(stdin);
                    break;
                }

                process_info.prob = buf / 10;

                break;
            }
        }
    }
    
    return SUCCESS;
}
