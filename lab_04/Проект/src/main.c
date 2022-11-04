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

#include "../inc/arr_stack_funcs.h"
#include "../inc/list_stack_funcs.h"
#include "../inc/in_out.h"
#include "../inc/my_types.h"
#include "../inc/my_msgs.h"
#include "../inc/my_err.h"


int main(void)
{
    int key = -1;

    arr_stack_t *arr_stack = create_arr_stack();
    if (!arr_stack)
    {
        printf(ERR_ALLOC_MSG);
        return ERR_ALLOC;
    }

    list_stack_t *list_stack = create_list_stack();
    if (!list_stack)
    {
        printf(ERR_ALLOC_MSG);
        destroy_arr_stack(arr_stack);
        return ERR_ALLOC;
    }


    printf(INFO_MSG);
    
    while (key != 0)
    {
        printf(MENU_MSG);

        if (fscanf(stdin, "%d", &key) != 1 ||
        key < 0 || key > MENU_LEN)
        {
            printf(ERR_CODE_MSG);
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
                
                
                break;
            }
            case 2:
            {
                if (is_arr_stack_full(arr_stack) &&
                is_list_stack_full(list_stack))
                {
                    printf(ERR_STACK_IS_FULL_MSG);
                    break;
                }

                char elem;


                printf(INPUT_ELEM_MSG);

                if (get_in_elem(stdin, &elem))
                {
                    printf(ERR_READING_STDIN_MSG);
                    break;
                }

                if (push_list_stack(list_stack, elem))
                {
                    printf(ERR_ALLOC_MSG);
                    destroy_list_stack(list_stack);
                    destroy_arr_stack(arr_stack);
                    return ERR_ALLOC;
                }

                push_arr_stack(arr_stack, elem);

                break;
            }
            case 3:
            {
                if (is_list_stack_empty(list_stack) &&
                is_arr_stack_empty(arr_stack))
                {
                    printf(ERR_STACK_IS_EMPTY_MSG);
                    break;
                }

                char pop_elem;


                print_del_ptrs(&(arr_stack->content[arr_stack->len - 1]), list_stack->top);

                pop_list_stack(list_stack, &pop_elem);
                pop_arr_stack(arr_stack, &pop_elem);

                break;
            }
            case 4:
            {
                break;
            }
            case 5:
            {
                // measurement_table measures[MEAS_LEN] = { 0 };


                // if (get_measures(measures))
                // {
                //     printf(ERR_MEASURES_MSG);
                //     break;
                // }

                // print_measures(measures, MEAS_LEN);

                break;
            }
        }
    }
    
    return SUCCESS;
}
