/**
 * @file main.c
 * @author Stepan Postnov ICS7-31B
 * @brief 
 * 
 *                     TASK:
 * 
 *                    Вариант 9
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

#include "../inc/arr_stack_funcs.h"
#include "../inc/list_stack_funcs.h"
#include "../inc/operations.h"
#include "../inc/in_out.h"
#include "../inc/my_measure.h"
#include "../inc/my_types.h"
#include "../inc/my_msgs.h"
#include "../inc/my_err.h"


int main(void)
{
    int key = -1;

    arr_stack_t *arr_stack = create_arr_stack();
    if (!arr_stack)
    {
        printf(ERR_ALLOC_MSG, RED, RESET);
        return ERR_ALLOC;
    }

    list_stack_t *list_stack = create_list_stack();
    if (!list_stack)
    {
        printf(ERR_ALLOC_MSG, RED, RESET);
        destroy_arr_stack(arr_stack);
        return ERR_ALLOC;
    }

    p_node_t p_nodes;
    memset(p_nodes.p_nodes, 0, STACK_SIZE * sizeof(node_t *));
    p_nodes.len = 0;


    printf(INFO_MSG);
    
    while (key != 0)
    {
        printf(MENU_MSG);

        if (fscanf(stdin, "%d", &key) != 1 ||
        key < 0 || key > MENU_LEN)
        {
            printf(ERR_CODE_MSG, RED, RESET);
            destroy_list_stack(list_stack);
            destroy_arr_stack(arr_stack);
            return ERR_CODE;
        }

        switch (key)
        {
            case 0:
            {
                destroy_list_stack(list_stack);
                destroy_arr_stack(arr_stack);
                return SUCCESS;
            }
            case 1:
            {
                print_stacks(list_stack, arr_stack, &p_nodes);
                
                break;
            }
            case 2:
            {
                clear_buf(stdin);

                if (is_arr_stack_full(arr_stack) &&
                is_list_stack_full(list_stack))
                {
                    printf(ERR_STACK_IS_FULL_MSG, RED, RESET);
                    clear_buf(stdin);
                    break;
                }

                char elem;


                printf(INPUT_ELEM_MSG);

                if (get_in_elem(stdin, &elem))
                {
                    printf(ERR_READING_STDIN_MSG, RED, RESET);
                    clear_buf(stdin);
                    break;
                }

                if (push_list_stack(list_stack, elem))
                {
                    printf(ERR_ALLOC_MSG, RED, RESET);
                    destroy_list_stack(list_stack);
                    destroy_arr_stack(arr_stack);
                    return ERR_ALLOC;
                }

                push_arr_stack(arr_stack, elem);

                if (p_nodes.len)
                    --p_nodes.len;

                printf(SUCCESSFULLY_ADD_MSG, GREEN, RESET);

                break;
            }
            case 3:
            {
                if (is_list_stack_empty(list_stack) &&
                is_arr_stack_empty(arr_stack))
                {
                    printf(ERR_STACK_IS_EMPTY_MSG, RED, RESET);
                    clear_buf(stdin);
                    break;
                }

                char pop_elem;


                print_del_ptrs(&(arr_stack->content[arr_stack->len - 1]), list_stack->top);

                p_nodes.p_nodes[(p_nodes.len)++] = list_stack->top;
                pop_list_stack(list_stack, &pop_elem);
                pop_arr_stack(arr_stack, &pop_elem);

                break;
            }
            case 4:
            {
                clear_buf(stdin);

                char ans;

                char expr[STACK_SIZE + 1] = { 0 };
                int len = 0;

                char out_expr[STACK_SIZE + 1] = { 0 };


                printf(INPUT_STACK_TYPE);
                fscanf(stdin, "\n%c", &ans);
                if (ans == '1')
                {
                    clear_buf(stdin);

                    arr_stack_t *cur_arr_stack = create_arr_stack();
                    if (!cur_arr_stack)
                    {
                        printf(ERR_ALLOC_MSG, RED, RESET);
                        destroy_list_stack(list_stack);
                        destroy_arr_stack(arr_stack);
                        return ERR_ALLOC;
                    }


                    printf(INPUT_EXPR_MSG, STACK_SIZE);

                    if (get_in_expression(expr, STACK_SIZE, &len))
                    {
                        printf(ERR_READING_OVERFLOW_MSG, RED, RESET);
                        destroy_arr_stack(cur_arr_stack);
                        clear_buf(stdin);
                        break;
                    }

                    if (get_postfix_expression_arr_stack(expr, len, cur_arr_stack, out_expr))
                    {
                        printf(ERR_EXPR_MSG, RED, RESET);
                        destroy_arr_stack(cur_arr_stack);
                        break;
                    }

                    printf(OUT_EXPR_MSG, GREEN, expr, out_expr, RESET);

                    destroy_arr_stack(cur_arr_stack);
                }
                else if (ans == '2')
                {
                    clear_buf(stdin);
                    
                    list_stack_t *cur_list_stack = create_list_stack();
                    if (!cur_list_stack)
                    {
                        printf(ERR_ALLOC_MSG, RED, RESET);
                        destroy_list_stack(list_stack);
                        destroy_arr_stack(arr_stack);
                        return ERR_ALLOC;
                    }


                    printf(INPUT_EXPR_MSG, STACK_SIZE);

                    if (get_in_expression(expr, STACK_SIZE, &len))
                    {
                        printf(ERR_READING_OVERFLOW_MSG, RED, RESET);
                        destroy_list_stack(cur_list_stack);
                        clear_buf(stdin);
                        break;
                    }

                    if (get_postfix_expression_list_stack(expr, len, cur_list_stack, out_expr))
                    {
                        printf(ERR_EXPR_MSG, RED, RESET);
                        destroy_list_stack(cur_list_stack);
                        break;
                    }

                    printf(OUT_EXPR_MSG, GREEN, expr, out_expr, RESET);

                    destroy_list_stack(cur_list_stack);
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
                measurement_table measures[MEAS_LEN * 2] = { 0 };


                if (get_measures(measures))
                {
                    printf(ERR_MEASURES_MSG, RED, RESET);
                    break;
                }

                print_measures(measures, MEAS_LEN * 2);

                break;
            }
        }
    }
    
    return SUCCESS;
}
