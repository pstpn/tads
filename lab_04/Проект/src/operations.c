#include "../inc/arr_stack_funcs.h"
#include "../inc/list_stack_funcs.h"
#include "../inc/my_types.h"
#include "../inc/my_err.h"


int get_postfix_expression_arr_stack(char *in_expr, int len, arr_stack_t *stack, char *out_expr)
{
    int ind_str = 0;

    char cur_elem;


    for (int i = 0; i < len; ++i)
    {
        if (in_expr[i] == '(')
            push_arr_stack(stack, in_expr[i]);
        else if (in_expr[i] == ')')
        {
            pop_arr_stack(stack, &cur_elem);

            while (stack->len && cur_elem != '(')
            {
                out_expr[ind_str++] = cur_elem;
                pop_arr_stack(stack, &cur_elem);
            }

            if (!stack->len && cur_elem != '(')
                return ERR_EXPRESSION;
        }
        else if (in_expr[i] == '+' || in_expr[i] == '-')
        {
            pop_arr_stack(stack, &cur_elem);

            while (stack->len && cur_elem != '(')
            {
                out_expr[ind_str++] = cur_elem;
                pop_arr_stack(stack, &cur_elem);
            }
            
            push_arr_stack(stack, cur_elem);
            push_arr_stack(stack, in_expr[i]);
        }
        else if (in_expr[i] == '*' || in_expr[i] == '/')
        {
            pop_arr_stack(stack, &cur_elem);

            while (stack->len && cur_elem != '(' &&
            cur_elem != '+' && cur_elem != '-')
            {
                out_expr[ind_str++] = cur_elem;
                pop_arr_stack(stack, &cur_elem);
            }
            
            push_arr_stack(stack, cur_elem);
            push_arr_stack(stack, in_expr[i]);
        }
        else
        {
            if ((in_expr[i] >= MIN_ASCII_BIG && in_expr[i] <= MAX_ASCII_BIG) ||
            (in_expr[i] >= MIN_ASCII_SMALL && in_expr[i] <= MAX_ASCII_SMALL))
                out_expr[ind_str++] = in_expr[i];
            else
                return ERR_EXPRESSION;
        }
    }

    do
    {
        pop_arr_stack(stack, &cur_elem);
        if (cur_elem != '(' && cur_elem != ')')
            out_expr[ind_str++] = cur_elem;
    } while (stack->len);

    return SUCCESS;
}


int get_postfix_expression_list_stack(char *in_expr, int len, list_stack_t *stack, char *out_expr)
{
    int ind_str = 0;

    char pop_elem;


    for (int i = 0; i < len; ++i)
    {
        if (in_expr[i] == '(')
            push_list_stack(stack, in_expr[i]);
        else if (in_expr[i] == ')')
        {
            pop_list_stack(stack, &pop_elem);

            while (stack->len && pop_elem != '(')
            {
                out_expr[ind_str++] = pop_elem;
                pop_list_stack(stack, &pop_elem);
            }

            if (!stack->len && pop_elem != '(')
                return ERR_EXPRESSION;
        }
        else if (in_expr[i] == '+' || in_expr[i] == '-')
        {
            pop_list_stack(stack, &pop_elem);

            while (stack->len && pop_elem != '(')
            {
                out_expr[ind_str++] = pop_elem;
                pop_list_stack(stack, &pop_elem);
            }
            
            push_list_stack(stack, pop_elem);
            push_list_stack(stack, in_expr[i]);
        }
        else if (in_expr[i] == '*' || in_expr[i] == '/')
        {
            pop_list_stack(stack, &pop_elem);

            while (stack->len && pop_elem != '(' &&
            pop_elem != '+' && pop_elem != '-')
            {
                out_expr[ind_str++] = pop_elem;
                pop_list_stack(stack, &pop_elem);
            }
            
            push_list_stack(stack, pop_elem);
            push_list_stack(stack, in_expr[i]);
        }
        else
        {
            if ((in_expr[i] >= MIN_ASCII_BIG && in_expr[i] <= MAX_ASCII_BIG) ||
            (in_expr[i] >= MIN_ASCII_SMALL && in_expr[i] <= MAX_ASCII_SMALL))
                out_expr[ind_str++] = in_expr[i];
            else
                return ERR_EXPRESSION;
        }
    }

    do
    {
        pop_list_stack(stack, &pop_elem);
        if (pop_elem != '(' && pop_elem != ')')
            out_expr[ind_str++] = pop_elem;
    } while (stack->len);

    return SUCCESS;
}