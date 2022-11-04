#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

#include "../inc/arr_stack_funcs.h"
#include "../inc/list_stack_funcs.h"
#include "../inc/operations.h"
#include "../inc/my_types.h"
#include "../inc/my_err.h"
#include "../inc/my_def.h"


unsigned long long microseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long) - 1;
    return val.tv_sec * 1000000ULL + val.tv_usec * 1ULL;
}


int get_measures(measurement_table table[MEAS_LEN])
{
    char exprs[MEAS_LEN][EXPR_LEN + 1] = {"A+B", "(A+B)*C-(D-E)*(F+G)",
    "((((A+B)*C)-(D-E))*(F+G))", "(((((A+B)*C)-(D-E))*((F+G)))/H)-L",
    "A+A+A+A+A+A+A+A+A+A+A+A+A+A+A+A+A+A+A+A"};

    int exprs_count[] = { 1, 4, 12, 18, 24, 1 };

    int lens[] = { 3, 19, 25, 33, 39 };
    
    long long unsigned beg, end, arr_res, list_res;


    for (int k = 0, i = 0; i < MEAS_LEN; k += 2, ++i)
    {
        arr_res = 0, list_res = 0;

        arr_stack_t *arr_stack = create_arr_stack();


        beg = microseconds_now();

        for (int j = 0; j < MEAS_COUNT; ++j)
        {
            char arr_out_expr[STACK_SIZE + 1] = { 0 };
            arr_stack->len = 0;


            get_postfix_expression_arr_stack(exprs[i], lens[i], arr_stack, arr_out_expr);
        }

        end = microseconds_now();

        destroy_arr_stack(arr_stack);

        arr_res += (end - beg);

        table[k].time = arr_res;
        table[k].mem = sizeof(arr_stack_t);
        memcpy(table[k].expr, exprs[i], sizeof(char) * lens[i]);

        list_stack_t *list_stack = create_list_stack();


        beg = microseconds_now();

        for (int j = 0; j < MEAS_COUNT; ++j)
        {
            char list_out_expr[STACK_SIZE + 1] = { 0 };
            list_stack->len = 0;


            get_postfix_expression_list_stack(exprs[i], lens[i], list_stack, list_out_expr);
        }
        end = microseconds_now();

        destroy_list_stack(list_stack);

        list_res += (end - beg);

        table[k + 1].time = list_res;
        table[k + 1].mem = sizeof(list_stack_t) + sizeof(node_t) * exprs_count[i];
    }
    
    return SUCCESS;
}