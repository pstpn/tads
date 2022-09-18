/**
 * @file tools.c
 * @author Stepan Postnov ICS7-31B
 * @brief Файл, содержащий вспомогательные функции
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>

#include "my_err.h"
#include "my_def.h"


int check_sign(char *ch, char *sign)
{
    if (*ch == '.')
        *sign = '+';
    else if (*ch == '-')
    {
        *sign = *ch;
        *ch = getc(stdin);
    }
    else if (*ch == '+')
    {
        *sign = *ch;
        *ch = getc(stdin);
    }
    else if (*ch >= MIN_DIGIT_CODE && *ch <= MAX_DIGIT_CODE)
        *sign = '+';
    else
        return INCORRECT_NUM;

    return SUCCESS;
}


void shift_numbers(int numbers[], int *ord)
{
    while (!numbers[0] && numbers[MAX_COUNT] > 1)
    {
        for (int i = 0; i < numbers[MAX_COUNT] - 1; ++i)
            numbers[i] = numbers[i + 1];
        --(numbers[MAX_COUNT]);
        --(*ord);
    }
}


int is_zero(int num[], int *ind)
{
    for (int i = 0; i < *ind; ++i)
        if (num[i])
            return FALSE;

    return TRUE;
}


int is_bigger(int num_1[], int num_2[], int add_check)
{
    if (add_check)
    {
        if (num_1[MAX_COUNT] > num_2[MAX_COUNT])
            return BIGGER;
        if (num_1[MAX_COUNT] < num_2[MAX_COUNT])
            return LOWER;
    }

    for (int i = 0; i < num_2[MAX_COUNT]; ++i)
    {
        if (num_1[i] > num_2[i])
            return BIGGER;
        if (num_1[i] < num_2[i])
            return LOWER;
    }

    return EQUIL;
}


void shift(int numbers[], int left)
{
    if (left)
    {
        for (int i = 0; i < numbers[MAX_COUNT] - 1; ++i)
            numbers[i] = numbers[i + 1];

        --numbers[MAX_COUNT];
    }
    else
    {
        for (int i = numbers[MAX_COUNT]; i > 0; --i)
            numbers[i] = numbers[i - 1];

        numbers[0] = 0, ++numbers[MAX_COUNT];
    }
}