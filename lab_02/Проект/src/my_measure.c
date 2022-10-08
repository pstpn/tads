#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "../inc/my_types.h"
#include "../inc/tools.h"
#include "../inc/w_w_table.h"


unsigned long long microseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long) - 1;
    return val.tv_sec * 1000000ULL + val.tv_usec * 1ULL;
}


void get_measures(measurement_table table[], car_info cars[], help_table inds[], int count)
{
    car_info cur_table[RECORDS_COUNT] = { 0 };

    help_table cur_keys[RECORDS_COUNT] = { 0 };
    
    long long unsigned beg, end, res = 0;


    // Table_slow

    for (int i = 0; i < COUNT; ++i)
    {
        deep_cpy(cur_table, cars, count, sizeof(car_info));
        
        beg = microseconds_now();
        mysort(&cur_table, count, sizeof(car_info), compare_prices);
        end = microseconds_now();

        res += (end - beg);
    }

    table[0].time = res / COUNT;
    table[0].mem = sizeof(car_info) * count;
    res = 0;

    // Table_quick

    for (int i = 0; i < COUNT; ++i)
    {
        deep_cpy(cur_table, cars, count, sizeof(car_info));
        
        beg = microseconds_now();
        qsort(&cur_table, count, sizeof(car_info), compare_prices);
        end = microseconds_now();

        res += (end - beg);
    }

    table[1].time = res / COUNT;
    table[1].mem = sizeof(car_info) * count;
    res = 0;

    // Key_slow

    for (int i = 0; i < COUNT; ++i)
    {
        deep_cpy(cur_keys, inds, count, sizeof(help_table));
        
        beg = microseconds_now();
        mysort(&cur_keys, count, sizeof(help_table), key_compare_prices);
        end = microseconds_now();

        res += (end - beg);
    }

    table[2].time = res / COUNT;
    table[2].mem = (sizeof(car_info) + sizeof(help_table)) * count;
    res = 0;

    // Key_quick

    for (int i = 0; i < COUNT; ++i)
    {
        deep_cpy(cur_keys, inds, count, sizeof(help_table));
        
        beg = microseconds_now();
        qsort(&cur_keys, count, sizeof(help_table), key_compare_prices);
        end = microseconds_now();

        res += (end - beg);
    }

    table[3].time = res / COUNT;
    table[3].mem = (sizeof(car_info) + sizeof(help_table)) * count;
}