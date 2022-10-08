#include <string.h>
#include <stdio.h>

#include "../inc/my_msgs.h"
#include "../inc/my_err.h"
#include "../inc/my_def.h"
#include "../inc/my_types.h"
#include "../inc/my_in_out.h"
#include "../inc/my_print.h"
#include "../inc/tools.h"


int finding_info(car_info cars[], int count)
{
    char model[MODEL_LEN + 1] = { '\0' };

    int min_price, max_price;


    printf(IN_FIND_MODEL_MSG);
    if (get_str(stdin, model, MODEL_LEN + 1, NEW_SEP))
    {
        clear_buf(stdin);
        return INCORRECT_MODEL;
    }

    printf(IN_FIND_MIN_PRICE_MSG);
    if (fscanf(stdin, "%d", &min_price) != 1 ||
    min_price < 1 || min_price > MAX_PRICE)
    {
        clear_buf(stdin);
        return INCORRECT_PRICE;
    }

    printf(IN_FIND_MAX_PRICE_MSG);
    if (fscanf(stdin, "%d", &max_price) != 1 ||
    max_price < 1 || max_price > MAX_PRICE ||
    max_price < min_price)
    {
        clear_buf(stdin);
        return INCORRECT_PRICE;
    }

    draw_name(TABLE_NAME, TABLE_WIDTH);

    for (int i = 0; i < count; ++i)
        if (cars[i].condition && strcmp(model, cars[i].model) == 0 &&
        cars[i].add_info.old_car.number_of_owners == 1 &&
        cars[i].add_info.old_car.number_of_repairs == 0 &&
        cars[i].price >= min_price && cars[i].price <= max_price)
        {
            print_car(cars[i]);
            draw_line(TABLE_WIDTH);
        }

    return SUCCESS;
}


int adding_car_in_table(FILE *f, car_info *car, int *count)
{
    if (*count + 1 > RECORDS_COUNT)
        return OVERFLOW;

    clear_buf(stdin);
    printf(IN_MODEL_MSG);        
    if (get_str(stdin, car->model, MODEL_LEN + 1, NEW_SEP))
        return INCORRECT_DATA;

    printf(IN_COUNTRY_MSG);
    if (get_str(stdin, car->country, COUNTRY_LEN + 1, NEW_SEP))
        return INCORRECT_DATA;

    printf(IN_PRICE_MSG);
    if (fscanf(stdin, "%d", &(car->price)) != 1)
    {
        clear_buf(stdin);
        return INCORRECT_DATA;
    }
    if (car->price < 1 || car->price > MAX_PRICE)
        return INCORRECT_DATA;

    clear_buf(stdin);
    printf(IN_COLOR_MSG);
    if (get_str(stdin, car->color, COLOR_LEN + 1, NEW_SEP))
        return INCORRECT_DATA;

    printf(IN_COND_MSG);
    if (fscanf(stdin, "%d", &(car->condition)) != 1)
    {
        clear_buf(stdin);
        return INCORRECT_DATA;
    }
    if (car->condition != 1 &&
    car->condition != 0)
        return INCORRECT_DATA;

    if (car->condition == 0)
    {
        printf(IN_GUAR_MSG);
        if (fscanf(stdin, "%d", &(car->add_info.guarantee)) != 1)
        {
            clear_buf(stdin);
            return INCORRECT_DATA;
        }
        if (car->add_info.guarantee < 0 ||
        car->add_info.guarantee > MAX_GUAR)
            return INCORRECT_DATA;
    }
    else if (car->condition == 1)
    {
        printf(IN_YEAR_MSG);
        if (fscanf(stdin, "%d", &(car->add_info.old_car.year)) != 1)
        {
            clear_buf(stdin);
            return INCORRECT_DATA;
        }
        if (car->add_info.old_car.year < 1 ||
        car->add_info.old_car.year > MAX_YEAR)
            return INCORRECT_DATA;

        printf(IN_MIL_MSG);
        if (fscanf(stdin, "%d", &(car->add_info.old_car.mileage)) != 1)
        {
            clear_buf(stdin);
            return INCORRECT_DATA;
        }
        if (car->add_info.old_car.mileage < 1 ||
        car->add_info.old_car.mileage > MAX_MIL)
            return INCORRECT_DATA;

        printf(IN_REP_MSG);
        if (fscanf(stdin, "%d", &(car->add_info.old_car.number_of_repairs)) != 1)
        {
            clear_buf(stdin);
            return INCORRECT_DATA;
        }
        if (car->add_info.old_car.number_of_repairs < 0 ||
        car->add_info.old_car.number_of_repairs > MAX_REP)
            return INCORRECT_DATA;

        printf(IN_OWN);
        if (fscanf(stdin, "%d", &(car->add_info.old_car.number_of_owners)) != 1)
        {
            clear_buf(stdin);
            return INCORRECT_DATA;
        }
        if (car->add_info.old_car.number_of_owners < 1 ||
        car->add_info.old_car.number_of_owners > MAX_OWN)
            return INCORRECT_DATA;
    }
    else
        return INCORRECT_DATA;

    char ans;


    printf(ADD_IN_FILE_MSG);
    fscanf(stdin, "\n%c", &ans);
    if (ans == 'y')
        write_in_file(f, *car, *count);

    ++(*count);

    return SUCCESS;
}


int delete_cars(car_info cars[], help_table inds[], int *count)
{
    int price;


    printf(IN_DEL_MSG);
    if (fscanf(stdin, "%d", &price) != 1 || price < 0 || price > MAX_PRICE)
    {
        clear_buf(stdin);
        return INCORRECT_PRICE;
    }

    for (int i = 0; i < *count; ++i)
        if (cars[i].price == price)
        {
            for (int j = 0; j < *count; ++j)
            {
                if (inds[j].index == i)
                {
                    transpose_at_the_end(inds, j, sizeof(help_table), count);
                    break;
                }
            }

            transpose_at_the_end(cars, i, sizeof(car_info), count);
            --(*count);
        }

    return SUCCESS;
}


void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*))
{
    char *p_end = (char *) base + nmemb * size;
    char temp;

    size_t i = 0;


    for (char *pi_cur = (char *) base; pi_cur != p_end; pi_cur += 2 * size, ++i)
    {
        size_t count = 0;


        if (nmemb <= i)
            break;

        for (size_t j = i; j < nmemb - (1 + i); ++j)
        {
            char *p1 = (char *) base + size * j;
            char *p2 = (char *) base + size * (j + 1);


            if (compar((void *) p1, (void *) p2) > 0)
            {
                ++count;
                for (size_t elem = 0; elem < size; ++elem)
                {
                    temp = *p1;
                    *(p1++) = *p2;
                    *(p2++) = temp;
                }
            }
        }
        if (!count)
            break;
        count = 0;

        for (size_t j = nmemb - i - 1; j > i; --j)
        {
            char *p1 = (char *) base + size * j;
            char *p2 = (char *) base + size * (j - 1);


            if (compar((void *) p1, (void *) p2) < 0)
            {
                ++count;
                for (size_t elem = 0; elem < size; ++elem)
                {
                    temp = *p1;
                    *(p1++) = *p2;
                    *(p2++) = temp;
                }
            }
        }
        if (!count)
            break;
    }
}