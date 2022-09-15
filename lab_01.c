/**
 * @file tasd.c
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

#define MAX_COUNT 32
#define MAX_ORDER 6
#define MAX_DIGIT_CODE 57
#define MIN_DIGIT_CODE 48
#define MIN_ORDER_VALUE -99999
#define MAX_ORDER_VALUE 99999
#define FLAG_VALUE -10
#define EMPTY '\0'
#define TRUE 1
#define FALSE 0
#define EQUIL 0
#define BIGGER 1
#define LOWER -1

#define SUCCESS 0
#define INCORRECT_NUM 1
#define DIVISION_BY_ZERO 2
#define OVERFLOW 3

#define FIRST_INPUT_MSG "Input your first number: "
#define SECOND_INPUT_MSG "Input your second number: "
#define FIRST_MSG_AFTER_NORM "First number after normalization: "
#define SECOND_MSG_AFTER_NORM "Second number after normalization: "
#define INCORRECT_NUM_MSG "Incorrect number. Please, try again!\n"
#define DIVISION_BY_ZERO_MSG "Error! Division by zero. Please, try again!\n"
#define OVERFLOW_MSG "Error! An overflow occurred during the calculation. Please, try again!\n"
#define TYPE_OF_OPERATION "\nType of operation on a number: DIVISION\n\n"
#define INPUT_FORMAT "Input format: [+|-]m[.]n[Е|e][+|-][K],\n(m + n) <= 30;\nK <= 5\n\n"
#define INPUT_RANGE "Input range:\nMIN: -0.00000000000000000000000000001 E -99999 \
\nMAX: +999999999999999999999999999999 E 99999\n\n"
#define OUTPUT_FORMAT "Output format: [+|-]0.m1 Е [+|-]K1,\nm1 <= 30;\nK1 <= 5\n\n"
#define OUTPUT_MSG "Result after division: "


typedef struct number
{
    char sign;
    int whole_part[MAX_COUNT + 1];
    int real_part[MAX_COUNT + 1];
    int order;
} my_number;


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
                if ((result->real_part)[i + 1] > MAX_DIGIT_CODE)
                {
                    ++(result->real_part)[i];
                    (result->real_part)[i + 1] = 0;
                }
                else
                    break;
            }

            if ((result->real_part)[0] > MAX_DIGIT_CODE)
            {
                if ((result->real_part)[MAX_COUNT - 3] > 4)
                {
                    ++(result->real_part)[MAX_COUNT - 4];

                    for (int i = MAX_COUNT - 5; i >= 0; --i)
                    {
                        if ((result->real_part)[i + 1] > MAX_DIGIT_CODE)
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
