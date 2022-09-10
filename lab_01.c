#include <stdio.h>

#define MAX_COUNT 30
#define MAX_DIGIT_CODE 57
#define MIN_DIGIT_CODE 48
#define FLAG_VALUE -10

#define SUCCESS 0
#define INCORRECT_NUM 1

#define INPUT_MSG "Input your number: "
#define INCORRECT_NUM_MSG "Incorrect number. Please, try again!\n"
#define TYPE_OF_OPERATION "\nType of operation on a number: DIVISION\n\n"
#define INPUT_FORMAT "Input format: [+|-]m[.]n[Е|e][+|-][K],\n(m + n) <= 30;\nK <= 5\n\n"
#define INPUT_RANGE "Input range:\nMIN: -0.99999999999999999999999999999E-99999\nMAX: 999999999999999999999999999999E99999\n\n"
#define OUTPUT_FORMAT "Output format: [+|-]0.m1 Е [+|-]K1,\nm1 <= 30;\nK1 <= 5\n\n"


typedef struct number
{
    char sign;
    int whole_part[MAX_COUNT + 1];
    int real_part[MAX_COUNT + 1];
    char order_sign;
    int order;
} my_digit;


void draw_information(void)
{
    printf(TYPE_OF_OPERATION);

    printf(INPUT_FORMAT);

    printf(INPUT_RANGE);

    printf(OUTPUT_FORMAT);
}


void show_parts(my_digit *num)
{
    printf("\nSIGN: %c\nWHOLE PART: ", num->sign);
    for (int j = 0; j < num->whole_part[MAX_COUNT]; ++j)
        printf("%d", (num->whole_part)[j]);

    printf("\nREAL PART: ");
    for (int j = 0; j < num->real_part[MAX_COUNT]; ++j)
        printf("%d", (num->real_part)[j]);
    printf("\n");
}


int get_number(my_digit *num)
{
    char ch;

    int i = 0;


    if ((ch = getc(stdin)) == '-')
    {
        num->sign = ch;
        ch = getc(stdin);
    }
    else if (ch == '+')
    {
        num->sign = ch;
        ch = getc(stdin);
    }
    else if (ch >= MIN_DIGIT_CODE && ch <= MAX_DIGIT_CODE)
        num->sign = '+';
    else
        return INCORRECT_NUM;

    while (i < MAX_COUNT)
    {
        if (ch >= MIN_DIGIT_CODE && ch <= MAX_DIGIT_CODE)
        {
            (num->whole_part)[i] = ch - MIN_DIGIT_CODE;
            ch = getc(stdin), ++i;
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

        while (i < MAX_COUNT)
        {
            if (ch >= MIN_DIGIT_CODE && ch <= MAX_DIGIT_CODE)
            {
                (num->real_part)[i] = ch - MIN_DIGIT_CODE;
                ch = getc(stdin), ++i;
            }
            else if (ch == '\n')
            {
                (num->real_part)[MAX_COUNT] = i;
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

        while (ch == ' ')
            ch = getc(stdin);

        if (ch == '\n')
        {
            (num->real_part)[0] = (!i) ?  0 : (num->real_part)[0];
            return SUCCESS;
        }

        if (ch != 'E' && ch != 'e')
            return INCORRECT_NUM;
    }


    return SUCCESS;
}


int main(void)
{
    my_digit num;
    num.whole_part[0] = FLAG_VALUE, num.whole_part[MAX_COUNT] = 0,
    num.real_part[0] = FLAG_VALUE, num.real_part[MAX_COUNT] = 0,
    num.order_sign = FLAG_VALUE;


    draw_information();

    printf(INPUT_MSG);
    if (get_number(&num))
    {
        printf(INCORRECT_NUM_MSG);
        return INCORRECT_NUM;
    }

    show_parts(&num);

    return SUCCESS;
}
