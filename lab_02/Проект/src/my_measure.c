#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "../inc/my_types.h"
#include "../inc/tools.h"
#include "../inc/w_w_table.h"


unsigned long long milliseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long) - 1;
    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}


void get_measures(measurement_table table[], car_info cars[], help_table inds[], int count)
{
    car_info cur_table[RECORDS_COUNT] = { 0 };

    help_table cur_keys[RECORDS_COUNT] = { 0 };
    
    long long unsigned beg, end;


    deep_cpy(cur_table, cars, count, sizeof(car_info));

    // Table_slow

    beg = milliseconds_now();
    mysort(&cur_table, count, sizeof(car_info), compare_prices);
    end = milliseconds_now();

    table[0].time = end - beg;
    table[0].mem = sizeof(car_info) * count;

    deep_cpy(cur_table, cars, count, sizeof(car_info));

    // Table_quick

    beg = milliseconds_now();
    qsort(&cur_table, count, sizeof(car_info), compare_prices);
    end = milliseconds_now();

    table[1].time = end - beg;
    table[1].mem = sizeof(car_info) * count;

    deep_cpy(cur_keys, inds, count, sizeof(help_table));

    // Key_slow

    beg = milliseconds_now();
    mysort(&cur_keys, count, sizeof(help_table), key_compare_prices);
    end = milliseconds_now();

    table[2].time = end - beg;
    table[2].mem = (sizeof(car_info) + sizeof(help_table)) * count;

    deep_cpy(cur_keys, inds, count, sizeof(help_table));

    // Key_quick

    beg = milliseconds_now();
    qsort(&cur_keys, count, sizeof(help_table), key_compare_prices);
    end = milliseconds_now();

    table[3].time = end - beg;
    table[3].mem = (sizeof(car_info) + sizeof(help_table)) * count;
}