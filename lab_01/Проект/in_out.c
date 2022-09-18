/**
 * @file in_out.c
 * @author Stepan Postnov ICS7-31B
 * @brief Файл, содержащий функции ввода/вывода информации
 * и чисел
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>

#include "my_type.h"
#include "my_msg.h"
#include "my_err.h"
#include "tools.h"


void draw_information(void)
{
    printf(TYPE_OF_OPERATION);

    printf(INPUT_FORMAT);

    printf(INPUT_RANGE);

    printf(OUTPUT_FORMAT);
}


void show_parts(my_number *num)
{
    printf("\nSIGN: %c\nWHOLE PART: ", num->sign);
    for (int j = 0; j < num->whole_part[MAX_COUNT]; ++j)
        printf("%d", (num->whole_part)[j]);

    printf("\nREAL PART: ");
    for (int j = 0; j < num->real_part[MAX_COUNT]; ++j)
        printf("%d", (num->real_part)[j]);

    if ((num->order))
        printf("\nORDER: %d", num->order);
    printf("\n\n");
}


void show_number(my_number *num)
{
    printf("%c", num->sign);
    for (int i = 0; i < (num->whole_part)[MAX_COUNT]; ++i)
        printf("%d", (num->whole_part)[i]);
    
    if ((num->real_part)[MAX_COUNT] > 0)
    {
        printf(".");
        for (int i = 0; i < (num->real_part)[MAX_COUNT]; ++i)
            printf("%d", (num->real_part)[i]);
    }

    printf(" E %c%d\n\n", (num->order > 0) ? '+' : EMPTY, num->order);
}


int get_number(my_number *num)
{
    char ch = getc(stdin);

    int i = 0;


    while (ch == ' ')
        ch = getc(stdin);

    if (check_sign(&ch, &(num->sign)))
        return INCORRECT_NUM;

    while (i < MAX_COUNT - 2)
    {
        if (ch >= MIN_DIGIT_CODE && ch <= MAX_DIGIT_CODE)
        {
            if (ch == MIN_DIGIT_CODE && !i && (num->whole_part)[0] == 0)
                continue;
            else
            {
                (num->whole_part)[i] = ch - MIN_DIGIT_CODE;
                ch = getc(stdin), ++i;
            }
        }
        else if (ch == 'e' || ch == 'E')
        {
            (num->whole_part)[MAX_COUNT] = (!i) ? 1 : i;
            (num->whole_part)[0] = (!i) ?  1 : (num->whole_part)[0];
            break;
        }
        else if(ch == '.')
        {
            (num->whole_part)[MAX_COUNT] = (!i) ? 1 : i;
            (num->whole_part)[0] = (!i) ?  0 : (num->whole_part)[0];
            break;
        }
        else if (ch == ' ')
        {
            (num->whole_part)[MAX_COUNT] = i;
            break;
        }
        else if (ch == '\n')
        {
            (num->whole_part)[MAX_COUNT] = i;
            return (!i) ? INCORRECT_NUM : SUCCESS;
        }
        else
            return INCORRECT_NUM;
    }
    (num->whole_part)[MAX_COUNT] = (i == MAX_COUNT - 2) ? MAX_COUNT - 2 : (num->whole_part)[MAX_COUNT];

    while (ch == ' ')
        ch = getc(stdin);

    if (ch == '\n')
        return (!i) ? INCORRECT_NUM : SUCCESS;

    if (ch != 'E' && ch != 'e' && ch != '.')
        return INCORRECT_NUM;

    if (ch == '.')
    {
        ch = getc(stdin);
        if ((ch < MIN_DIGIT_CODE || ch > MAX_DIGIT_CODE) && (num->whole_part)[0] == FLAG_VALUE)
            return INCORRECT_NUM;

        i = 0;

        while (i < MAX_COUNT - 2 - (num->whole_part)[MAX_COUNT])
        {
            if (ch >= MIN_DIGIT_CODE && ch <= MAX_DIGIT_CODE)
            {
                (num->real_part)[i] = ch - MIN_DIGIT_CODE;
                ch = getc(stdin), ++i;
            }
            else if (ch == '\n')
            {
                (num->real_part)[MAX_COUNT] = (!i) ? 1 : i;
                (num->real_part)[0] = (!i) ? 0 : (num->real_part)[0];
                return SUCCESS;
            }
            else if (ch == 'e' || ch == 'E' || ch == ' ')
            {
                (num->real_part)[MAX_COUNT] = i;
                break;
            }
            else
                return INCORRECT_NUM;
        }
        (num->real_part)[MAX_COUNT] = (i == MAX_COUNT - 2 - (num->whole_part)[MAX_COUNT]) 
        ? MAX_COUNT - 2 - (num->whole_part)[MAX_COUNT] : (num->real_part)[MAX_COUNT];

        while (ch == ' ')
            ch = getc(stdin);

        if (ch == '\n')
        {
            (num->real_part)[MAX_COUNT] = (!i) ? 1 : (num->real_part)[MAX_COUNT];
            (num->real_part)[0] = (!i) ?  0 : (num->real_part)[0];
            return SUCCESS;
        }

        if (ch != 'E' && ch != 'e')
            return INCORRECT_NUM;
    }

    if (scanf("%d", &(num->order)) != 1 || 
    num->order < MIN_ORDER_VALUE || num->order > MAX_ORDER_VALUE)
        return INCORRECT_NUM;

    do
    {
        ch = getc(stdin);
    } while (ch == ' ');

    if (ch != '\n')
        return INCORRECT_NUM;

    return SUCCESS;
}