/**
 * @file main.c
 * @author Stepan Postnov ICS7-31B
 * @brief 
 * 
 * TASK:
 * 
 * Смоделировать операцию деления действительного числа
 * на действительное число в форме +-m.n Е +-K, где
 * суммарная длина мантиссы (m+n) - до 30 значащих цифр, а
 * величина порядка K - до 5 цифр. Результат выдать в форме
 * +-0.m1 Е +-K1, где m1 - до 30 значащих цифр, а K1 - до 5
 * цифр.
 * 
 * @version 0.1
 * @date 2022-09-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>

#include "my_type.h"
#include "my_msg.h"
#include "my_err.h"
#include "tools.h"
#include "w_w_num.h"
#include "in_out.h"


int main(void)
{
    my_number num_1;
    num_1.whole_part[0] = FLAG_VALUE, num_1.whole_part[MAX_COUNT] = 0,
    num_1.real_part[0] = FLAG_VALUE, num_1.real_part[MAX_COUNT] = 0,
    num_1.order = 0;
    my_number num_2;
    num_2.whole_part[0] = FLAG_VALUE, num_2.whole_part[MAX_COUNT] = 0,
    num_2.real_part[0] = FLAG_VALUE, num_2.real_part[MAX_COUNT] = 0,
    num_2.order = 0;
    my_number result;
    result.real_part[MAX_COUNT] = 0;
    result.whole_part[0] = 0, result.whole_part[MAX_COUNT] = 1;

    int rc;


    draw_information();

    printf(FIRST_INPUT_MSG);
    if (get_number(&num_1))
    {
        printf(INCORRECT_NUM_MSG);
        return INCORRECT_NUM;
    }
    show_parts(&num_1);

    printf(SECOND_INPUT_MSG);
    if (get_number(&num_2))
    {
        printf(INCORRECT_NUM_MSG);
        return INCORRECT_NUM;
    }
    show_parts(&num_2);

    number_normalization(&num_1);
    printf(FIRST_MSG_AFTER_NORM);
    show_number(&num_1);
    
    number_normalization(&num_2);
    printf(SECOND_MSG_AFTER_NORM);
    show_number(&num_2);

    if ((rc = division(&num_1, &num_2, &result)) == DIVISION_BY_ZERO)
    {
        printf(DIVISION_BY_ZERO_MSG);
        return DIVISION_BY_ZERO;
    }
    else if (rc == OVERFLOW)
    {
        printf(OVERFLOW_MSG);
        return OVERFLOW;
    }
    if (is_zero(result.real_part, &((result.real_part)[MAX_COUNT])))
        result.order = 0;

    printf(OUTPUT_MSG);
    show_number(&result);

    return SUCCESS;
}
