#include <stdio.h>

#include "../inc/my_def.h"
#include "../inc/my_types.h"
#include "../inc/my_msgs.h"


void draw_line(int len)
{
    for (int i = 0; i < len; ++i)
        printf("-");
    printf("\n");
}


void draw_name(char *table_name, int table_width)
{
    draw_line(table_width);
    printf("%s", table_name);
    draw_line(table_width);
}


void print_car(car_info car)
{
    printf("|%*s|%*s|%*d|%*s|%*d|%*d|%*c|%*c|%*c|%*c|\n",
    MODEL_LEN, car.model, COUNTRY_LEN, car.country,
    PRICE_LEN, car.price, COLOR_LEN, car.color,
    CONDITION_LEN, car.condition, GUAR_LEN,
    car.add_info.guarantee, YEAR_LEN, EMPTY,
    MIL_LEN, EMPTY, REP_LEN, EMPTY, OWN_LEN, EMPTY);
}


void print_cars(car_info cars[], int count)
{
    draw_name(TABLE_NAME, TABLE_WIDTH);

    for (int i = 0; i < count; ++i)
    {
        if (cars[i].condition)
            printf("|%*s|%*s|%*d|%*s|%*d|%*c|%*d|%*d|%*d|%*d|\n",
            MODEL_LEN, cars[i].model, COUNTRY_LEN, cars[i].country,
            PRICE_LEN, cars[i].price, COLOR_LEN, cars[i].color,
            CONDITION_LEN, cars[i].condition, GUAR_LEN, EMPTY, 
            YEAR_LEN, cars[i].add_info.old_car.year, 
            MIL_LEN, cars[i].add_info.old_car.mileage, REP_LEN,
            cars[i].add_info.old_car.number_of_repairs,
            OWN_LEN, cars[i].add_info.old_car.number_of_owners);
        else
            print_car(cars[i]);
        draw_line(TABLE_WIDTH);
    }
}


void print_keys(help_table index_table[],int count)
{
    draw_name(KEY_TABLE_NAME, KEY_TABLE_WIDTH);

    for (int i = 0; i < count; ++i)
    {
        printf("|%*d|%*d|%*d|\n",NUM_LEN, i + 1, INDEX_LEN, 
        index_table[i].index, PRICE_LEN, index_table[i].price);

        draw_line(KEY_TABLE_WIDTH);
    }
}


void print_cars_using_keys(car_info cars[], help_table inds[], int count)
{
    draw_name(TABLE_NAME, TABLE_WIDTH);

    for (int i = 0; i < count; ++i)
    {
        int ind = inds[i].index;


        if (cars[ind].condition)
            printf("|%*s|%*s|%*d|%*s|%*d|%*c|%*d|%*d|%*d|%*d|\n",
            MODEL_LEN, cars[ind].model, COUNTRY_LEN, cars[ind].country,
            PRICE_LEN, cars[ind].price, COLOR_LEN, cars[ind].color,
            CONDITION_LEN, cars[ind].condition, GUAR_LEN, EMPTY, 
            YEAR_LEN, cars[ind].add_info.old_car.year, 
            MIL_LEN, cars[ind].add_info.old_car.mileage, REP_LEN,
            cars[ind].add_info.old_car.number_of_repairs,
            OWN_LEN, cars[ind].add_info.old_car.number_of_owners);
        else
            print_car(cars[ind]);

        draw_line(TABLE_WIDTH);
    }
}


void print_measures(measurement_table measures[])
{
    draw_name(MEASURE_TABLE_NAME, MEASURE_TABLE_WIDTH);

    printf("%*s|%*llu|%*llu|%*llu|%*llu|\n", TIME_MEM_LEN, "TIME, mcs",
    SLOW_LEN, measures[0].time, QUICK_LEN, measures[1].time,
    SLOW_LEN, measures[2].time, QUICK_LEN, measures[3].time);
    draw_line(MEASURE_TABLE_WIDTH);
    printf("%*s|%*d|%*d|%*d|%*d|\n", TIME_MEM_LEN, "MEMORY, b", SLOW_LEN,
    measures[0].mem, QUICK_LEN, measures[1].mem, SLOW_LEN,
    measures[2].mem, QUICK_LEN, measures[3].mem);
    draw_line(MEASURE_TABLE_WIDTH);
}