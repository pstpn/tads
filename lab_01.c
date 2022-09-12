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

#define MAX_COUNT 31
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

#define FIRST_INPUT_MSG "Input your first number: "
#define SECOND_INPUT_MSG "Input your second number: "
#define FIRST_MSG_AFTER_NORM "First number after normalization: "
#define SECOND_MSG_AFTER_NORM "Second number after normalization: "
#define INCORRECT_NUM_MSG "Incorrect number. Please, try again!\n"
#define DIVISION_BY_ZERO_MSG "Error! Division by zero. Please, try again!\n"
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
    int real_part[MAX_COUNT + 2];
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
        printf("\nORDER: %d",num->order);
    printf("\n\n");
}


void show_number(my_number *num)
{
    char order_sign;


    printf("%c", num->sign);
    for (int i = 0; i < (num->whole_part)[MAX_COUNT]; ++i)
        printf("%d", (num->whole_part)[i]);
    
    if ((num->real_part)[MAX_COUNT] > 0)
    {
        printf(".");
        for (int i = 0; i < (num->real_part)[MAX_COUNT]; ++i)
            printf("%d", (num->real_part)[i]);
    }

    order_sign = (num->order > 0) ? '+' : EMPTY;
    printf(" E %c%d\n\n", order_sign, num->order);
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

    while (i < MAX_COUNT)
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
    (num->whole_part)[MAX_COUNT] = (i == MAX_COUNT) ? MAX_COUNT : (num->whole_part)[MAX_COUNT];

    while (ch == ' ')
        ch = getc(stdin);

    if (ch == '\n')
        return (!i) ? INCORRECT_NUM : SUCCESS;

    if (ch != 'E' && ch != 'e' && ch != '.')
        return INCORRECT_NUM;

    if (ch == '.')
    {
        ch = getc(stdin);
        i = 0;

        while (i < MAX_COUNT - (num->whole_part)[MAX_COUNT])
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
        (num->real_part)[MAX_COUNT] = (i == MAX_COUNT - (num->whole_part)[MAX_COUNT]) 
        ? MAX_COUNT - (num->whole_part)[MAX_COUNT] : (num->real_part)[MAX_COUNT];

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
}


int is_zero(int *num)
{
    for (int i = 0; i < num[MAX_COUNT]; ++i)
        if (num[i])
            return FALSE;

    return TRUE;
}


int is_bigger(int *num_1, int *num_2)
{
    if (num_1[MAX_COUNT] > num_2[MAX_COUNT])
        return BIGGER;
    if (num_1[MAX_COUNT] < num_2[MAX_COUNT])
        return LOWER;

    for (int i = 0; i < num_2[MAX_COUNT]; ++i)
    {
        if (num_1[i] > num_2[i])
            return BIGGER;
        if (num_1[i] < num_2[i])
            return LOWER;
    }

    return EQUIL;
}


void shift_numbers_and_add_zeros(int *numbers, int *ord)
{
    while (!numbers[0])
    {
        for (int i = 1; i < numbers[MAX_COUNT]; ++i)
            numbers[i] = numbers[i - 1];
            
        numbers[numbers[MAX_COUNT]] = 0, --(*ord);
    }
}


int division(my_number *num_1, my_number *num_2, my_number *result)
{
    int ind = (num_2->real_part)[MAX_COUNT] - 1;


    if (is_zero(num_2->real_part))
        return INCORRECT_NUM;

    result->sign = (((num_1->sign) == '+' && (num_2->sign) == '-') ||
    ((num_2->sign) == '+' && (num_1->sign) == '-')) ? '-' : '+';

    for (int i = 0; !is_zero(num_1->real_part) && i < MAX_COUNT; ++i)
    {
        shift_numbers_and_add_zeros(num_1->real_part, &(num_1->order));
        shift_numbers_and_add_zeros(num_2->real_part, &(num_2->order));

        (result->whole_part)[i] = 0, ++((result->whole_part)[MAX_COUNT]);

        if (is_bigger((num_1->real_part), (num_2->real_part)) == -1)
        {
            (num_1->real_part)[((num_1->real_part)[MAX_COUNT])++] = 0;
            --(num_1->order);
            continue;
        }

        while (is_bigger((num_1->real_part), (num_2->real_part)) >= 1)
        {
            for (int i = ind; i >= 0; --i)
            {
                if ((num_1->real_part)[i] < (num_2->real_part)[i])
                {
                    --((num_1->real_part)[i - 1]);
                    (num_1->real_part)[i] += (10 - (num_2->real_part)[i]);
                }
                else
                    (num_1->real_part)[i] -= (num_2->real_part)[i];
            }

            ++((result->whole_part)[i]);
        }
    }

    result->order = num_1->order - num_2->order;

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
    result.whole_part[MAX_COUNT] = 0;


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

    if (division(&num_1, &num_2, &result))
    {
        printf(DIVISION_BY_ZERO_MSG);
        return DIVISION_BY_ZERO;
    }
    printf(OUTPUT_MSG);
    number_normalization(&result);
    show_number(&result);

    return SUCCESS;
}
