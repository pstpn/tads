/**
 * @file my_msg.h
 * @author Stepan Postnov ICS7-31B
 * @brief Файл, содержащий сообщения для пользователя
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ___MY_MSG___
#define ___MY_MSG___

#define FIRST_INPUT_MSG "Input your first number: "
#define SECOND_INPUT_MSG "Input your second number: "
#define FIRST_MSG_AFTER_NORM "First number after normalization: "
#define SECOND_MSG_AFTER_NORM "Second number after normalization: "
#define INCORRECT_NUM_MSG "Error! Incorrect number. Please, try again!\n"
#define DIVISION_BY_ZERO_MSG "Error! Division by zero. Please, try again!\n"
#define OVERFLOW_MSG "Error! An overflow occurred during the calculation. Please, try again!\n"
#define TYPE_OF_OPERATION "\nType of operation on a number: DIVISION\n\n"
#define INPUT_FORMAT "Input format: [+|-]m[.]n[Е|e][+|-][K],\n(m + n) <= 30;\nK <= 5\n\n"
#define INPUT_RANGE "Input range:\nMIN: -0.00000000000000000000000000001 E -99999 \
\nMAX: +999999999999999999999999999999 E 99999\n\n"
#define OUTPUT_FORMAT "Output format: [+|-]0.m1 Е [+|-]K1,\nm1 <= 30;\nK1 <= 5\n\n"
#define OUTPUT_MSG "Result after division: "

#endif // ___MY_MSG___