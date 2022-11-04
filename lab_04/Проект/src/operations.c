#include "../inc/list_stack_funcs.h"
#include "../inc/my_types.h"
#include "../inc/my_err.h"


int get_postfix_expression_arr_stack(char *in_expr, int len, arr_stack_t *stack, char *out_expr)
{
    int ind_str = 0;


    for (int i = 0; i < len; ++i)
    {
        if (in_expr[i] == '(')
            stack->content[stack->len++] = in_expr[i];
        else if (in_expr[i] == ')')
        {
            while (stack->len && stack->content[stack->len - 1] != '(')
                out_expr[ind_str++] = stack->content[--stack->len];

            if (!stack->len)
                return ERR_EXPRESSION;

            --stack->len;
        }
        else if (in_expr[i] == '+' || in_expr[i] == '-')
        {
            while (stack->len &&
            stack->content[stack->len - 1] != '(')
                out_expr[ind_str++] = stack->content[--stack->len];
            
            stack->content[stack->len++] = in_expr[i];
        }
        else if (in_expr[i] == '*' || in_expr[i] == '/')
        {
            while (stack->len &&
            stack->content[stack->len - 1] != '(' &&
            stack->content[stack->len - 1] != '+' &&
            stack->content[stack->len - 1] != '-')
                out_expr[ind_str++] = stack->content[--stack->len];
            
            stack->content[stack->len++] = in_expr[i];
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

    while (stack->len)
        out_expr[ind_str++] = stack->content[--stack->len];

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
            while (stack->len && stack->top->item != '(')
            {
                pop_list_stack(stack, &pop_elem);
                out_expr[ind_str++] = pop_elem;
            }

            if (!stack->len)
                return ERR_EXPRESSION;

            --stack->len;
        }
        else if (in_expr[i] == '+' || in_expr[i] == '-')
        {
            while (stack->len && stack->top->item != '(')
            {
                pop_list_stack(stack, &pop_elem);
                out_expr[ind_str++] = pop_elem;
            }
            
            push_list_stack(stack, in_expr[i]);
        }
        else if (in_expr[i] == '*' || in_expr[i] == '/')
        {
            while (stack->len && stack->top->item != '(' &&
            stack->top->item != '+' && stack->top->item != '-')
            {
                pop_list_stack(stack, &pop_elem);
                out_expr[ind_str++] = pop_elem;
            }
            
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

    while (stack->len)
    {
        pop_list_stack(stack, &pop_elem);
        out_expr[ind_str++] = pop_elem;
    }

    return SUCCESS;
}