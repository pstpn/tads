#include <stdio.h>

#define MAX_COUNT 30

#define SUCCESS 0
#define INCORRECT_NUM 1

#define INCORRECT_NUM_MSG "Incorrect number. Please, try again!\n"
#define TYPE_OF_OPERATION "\nType of operation on a number: DIVISION\n\n"
#define INPUT_FORMAT "Input format: [+|-]m[.]n[Е|e][+|-][K],\n(m + n) <= 30;\nK <= 5\n\n"
#define INPUT_RANGE "Input range:\nMIN: -0.99999999999999999999999999999E-99999\nMAX: 999999999999999999999999999999E99999\n\n"
#define OUTPUT_FORMAT "Output format: [+|-]0.m1 Е [+|-]K1,\nm1 <= 30;\nK1 <= 5\n\n"


typedef struct number
{
    char sign;
    int whole_part[MAX_COUNT];
    int real_part[MAX_COUNT];
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


// int get_digit(my_digit *num)
// {


//     return SUCCESS;
// }


int main(void)
{
    // my_digit num;


    draw_information();

    // if (get_digit(&num))
    // {
    //     printf(INCORRECT_NUM_MSG);
    //     return INCORRECT_NUM;
    // }
        
    
    return SUCCESS;
}
