/**
 * @file my_type.h
 * @author Stepan Postnov ICS7-31B
 * @brief Файл, содержащий тип данных для хранения
 * "длинных" чисел
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ___MY_TYPE___
#define ___MY_TYPE___

#include "my_def.h"


typedef struct number
{
    char sign;
    int whole_part[MAX_COUNT + 1];
    int real_part[MAX_COUNT + 1];
    int order;
} my_number;

#endif // ___MY_TYPE___