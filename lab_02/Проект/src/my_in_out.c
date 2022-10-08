#include <stdio.h>

#include "../inc/my_def.h"
#include "../inc/my_types.h"
#include "../inc/my_err.h"
#include "../inc/tools.h"


void write_in_file(FILE *f, car_info car, int count)
{
    if (count)
        fprintf(f, "\n");

    if (car.condition)
        fprintf(f, "%s;%s;%d;%s;%d;%d;%d;%d;%d;",
        car.model, car.country, car.price, car.color, 
        car.condition, car.add_info.old_car.year,
        car.add_info.old_car.mileage,
        car.add_info.old_car.number_of_repairs,
        car.add_info.old_car.number_of_owners);
    else
        fprintf(f, "%s;%s;%d;%s;%d;%d;", car.model, 
        car.country, car.price, car.color,
        car.condition, car.add_info.guarantee);
}


int get_str(FILE *f, char *str, int max_len, char sep)
{
    int len = 0;

    char ch = getc(f);
    if (sep == NEW_SEP)
        ch = fgetc(f);


    while (ch != sep)
    {
        str[len++] = ch;

        if (len > max_len - 1)
        {
            if (sep == NEW_SEP)
                clear_buf(stdin);
                
            return OVERFLOW;
        }

        ch = getc(f);
    }

    return (len) ? SUCCESS : EMPTY_STR;
}


int get_tables(FILE *f, car_info table[], help_table index_table[], int *count)
{
    char buf;


    fgetc(f);
    if (feof(f) != 0)
        return SUCCESS;
    rewind(f);

    for (int i = 0; i < RECORDS_COUNT + 1 && feof(f) == 0; ++i)
    {
        if (i == RECORDS_COUNT)
            return OVERFLOW;

        if (get_str(f, table[i].model, MODEL_LEN + 1, SEP))
            return INCORRECT_DATA;

        if (get_str(f, table[i].country, COUNTRY_LEN + 1, SEP))
            return INCORRECT_DATA;

        if (fscanf(f, "%d", &(table[i].price)) != 1 ||
        (buf = getc(f)) != ';')
            return INCORRECT_DATA;
        if (table[i].price < 1 || table[i].price > MAX_PRICE)
            return INCORRECT_DATA;

        if (get_str(f, table[i].color, COLOR_LEN + 1, SEP))
            return INCORRECT_DATA;

        if (fscanf(f, "%d", &(table[i].condition)) != 1 ||
        (buf = getc(f)) != ';')
            return INCORRECT_DATA;
        if (table[i].condition != 1 &&
        table[i].condition != 0)
            return INCORRECT_DATA;

        if (table[i].condition == 0)
        {
            if (fscanf(f, "%d", &(table[i].add_info.guarantee)) != 1 ||
            (buf = getc(f)) != ';')
                return INCORRECT_DATA;
            if (table[i].add_info.guarantee < 0 ||
            table[i].add_info.guarantee > MAX_GUAR)
                return INCORRECT_DATA;
        }
        else if (table[i].condition == 1)
        {
            if (fscanf(f, "%d", &(table[i].add_info.old_car.year)) != 1 ||
            (buf = getc(f)) != ';')
                return INCORRECT_DATA;
            if (table[i].add_info.old_car.year < 1 ||
            table[i].add_info.old_car.year > MAX_YEAR)
                return INCORRECT_DATA;

            if (fscanf(f, "%d", &(table[i].add_info.old_car.mileage)) != 1 ||
            (buf = getc(f)) != ';')
                return INCORRECT_DATA;
            if (table[i].add_info.old_car.mileage < 1 ||
            table[i].add_info.old_car.mileage > MAX_MIL)
                return INCORRECT_DATA;

            if (fscanf(f, "%d", &(table[i].add_info.old_car.number_of_repairs)) != 1 ||
            (buf = getc(f)) != ';')
                return INCORRECT_DATA;
            if (table[i].add_info.old_car.number_of_repairs < 0 ||
            table[i].add_info.old_car.number_of_repairs > MAX_REP)
                return INCORRECT_DATA;

            if (fscanf(f, "%d", &(table[i].add_info.old_car.number_of_owners)) != 1 ||
            (buf = getc(f)) != ';')
                return INCORRECT_DATA;
            if (table[i].add_info.old_car.number_of_owners < 1 ||
            table[i].add_info.old_car.number_of_owners > MAX_OWN)
                return INCORRECT_DATA;
        }
        else
            return INCORRECT_DATA;

        fgetc(f);

        index_table[i].index = i;
        index_table[i].price = table[i].price;
        ++(*count);
    }

    return SUCCESS;
}