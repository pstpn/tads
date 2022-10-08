#ifndef ___MY_TYPES___
#define ___MY_TYPES___

#include "my_def.h"


typedef struct info
{
    char model[MODEL_LEN + 2];
    char country[COUNTRY_LEN + 2];
    int price;
    char color[COLOR_LEN + 2];
    int condition;
    union
    {
        int guarantee;
        struct old_info
        {
            int year;
            int mileage;
            int number_of_repairs;
            int number_of_owners;
        } old_car;

    } add_info;
    
} car_info;


typedef struct indexes
{
    int index;
    int price;
} help_table;


typedef struct measure
{
    long long unsigned time;
    int mem;
} measurement_table;

#endif // ___MY_TYPES___