/**
 * @file w_w_num.c
 * @author Stepan Postnov ICS7-31B
 * @brief Файл, содержащий основные функции проекта
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "my_type.h"
#include "my_def.h"
#include "my_err.h"
#include "tools.h"


void number_normalization(my_number *num)
{
    if ((num->whole_part)[MAX_COUNT] != 1 || (num->whole_part)[0] != 0)
    {
        for (int i = (num->whole_part)[MAX_COUNT] - 1; i >= 0; --i)
        {
            for (int j = (num->real_part)[MAX_COUNT]; j > 0; --j)
                (num->real_part)[j] = (num->real_part)[j - 1];
                
            (num->real_part)[0] = (num->whole_part)[i];
            ++(num->order), ++(num->real_part)[MAX_COUNT];
        }
        (num->whole_part)[MAX_COUNT] = 1, (num->whole_part)[0] = 0;
    }

    shift_numbers(num->real_part, &(num->order));
}


int division(my_number *num_1, my_number *num_2, my_number *result)
{
    int ind = (num_2->real_part)[MAX_COUNT] - 1;


    if (is_zero(num_2->real_part, &((num_2->real_part)[MAX_COUNT])))
        return DIVISION_BY_ZERO;

    result->sign = (((num_1->sign) == '+' && (num_2->sign) == '-') ||
    ((num_2->sign) == '+' && (num_1->sign) == '-')) ? '-' : '+';

    result->order = num_1->order - num_2->order;
    result->order += (is_bigger(num_1->real_part, num_2->real_part, FALSE) == LOWER) ? 0 : 1;
    if (result->order < MIN_ORDER_VALUE || result->order > MAX_ORDER_VALUE)
        return OVERFLOW;

    while ((num_1->real_part)[MAX_COUNT] - 1 < ind)
    {
        (num_1->real_part)[(num_1->real_part)[MAX_COUNT]++] = 0;
        --(num_1->order);
    }
    if (is_bigger(num_1->real_part, num_2->real_part, TRUE) == LOWER)
    {
        (num_1->real_part)[(num_1->real_part)[MAX_COUNT]++] = 0;
        --(num_1->order), ++ind;
        shift(num_2->real_part, FALSE);
    }
    if ((num_1->real_part)[MAX_COUNT] > (num_2->real_part)[MAX_COUNT] &&
    is_bigger(num_1->real_part, num_2->real_part, FALSE) == LOWER)
    {
        ++ind;
        shift(num_2->real_part, FALSE);
    }
    
    int index = 0;


    for (int i = 0; !is_zero(num_1->real_part, &((num_1->real_part)[MAX_COUNT])) &&
    i + index < MAX_COUNT - 1; ++i)
    {
        index += i;

        while ((num_1->real_part)[MAX_COUNT] - 1 < ind)
            (num_1->real_part)[(num_1->real_part)[MAX_COUNT]++] = 0;

        (result->real_part)[index] = 0, ++(result->real_part)[MAX_COUNT];

        while (is_bigger(num_1->real_part, num_2->real_part, FALSE) >= EQUIL)
        {
            for (int j = ind; j >= 0; --j)
            {
                if ((num_1->real_part)[j] < (num_2->real_part)[j])
                {
                    --((num_1->real_part)[j - 1]);
                    (num_1->real_part)[j] += (10 - (num_2->real_part)[j]);
                }
                else
                    (num_1->real_part)[j] -= (num_2->real_part)[j];
            }

            ++(result->real_part)[index];
        }


        for (int j = 0; (is_bigger(num_1->real_part, num_2->real_part, FALSE) < EQUIL &&
        !is_zero(num_1->real_part, &((num_1->real_part)[MAX_COUNT]))); ++j)
        {
            if (!(num_1->real_part)[0])
                shift(num_1->real_part, TRUE);
            else
                shift(num_2->real_part, FALSE), ++ind;

            if ((num_1->real_part)[MAX_COUNT] == ind + 1)
                (num_1->real_part)[(num_1->real_part)[MAX_COUNT]++] = 0;

            if (j)
            {
                ++index;

                (result->real_part)[index] = 0;
                ++(result->real_part)[MAX_COUNT];
            }

            if (index == MAX_COUNT - 2)
                break;
        }

        index -= i;
    }

    if ((result->real_part)[MAX_COUNT] == MAX_COUNT - 1)
    {
        if ((result->real_part)[MAX_COUNT - 2] > 4)
        {
            ++(result->real_part)[MAX_COUNT - 3];

            for (int i = MAX_COUNT - 4; i >= 0; --i)
            {
                if ((result->real_part)[i + 1] > MAX_DIGIT)
                {
                    ++(result->real_part)[i];
                    (result->real_part)[i + 1] = 0;
                }
                else
                    break;
            }

            if ((result->real_part)[0] > MAX_DIGIT)
            {
                if ((result->real_part)[MAX_COUNT - 3] > 4)
                {
                    ++(result->real_part)[MAX_COUNT - 4];

                    for (int i = MAX_COUNT - 5; i >= 0; --i)
                    {
                        if ((result->real_part)[i + 1] > MAX_DIGIT)
                        {
                            ++(result->real_part)[i];
                            (result->real_part)[i + 1] = 0;
                        }
                        else
                            break;
                    }
                }
                
                --((result->real_part)[MAX_COUNT]);
            }
        }

        --((result->real_part)[MAX_COUNT]);
    }

    return SUCCESS;
}