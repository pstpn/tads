#include <stdio.h>

#include "../inc/my_types.h"


void clear_buf(FILE *f)
{
    char buf = '\0';

    
    while (buf != '\n')
        buf = fgetc(f);
}


int compare_prices(const void *p_1, const void *p_2)
{
    const car_info *a = p_1;
    const car_info *b = p_2;


    return a->price - b->price;
}


int key_compare_prices(const void *p_1, const void *p_2)
{
    const help_table *a = p_1;
    const help_table *b = p_2;


    return a->price - b->price;
}


void deep_cpy(void *dst, void *base, int count, int size)
{
    for (int i = 0; i < count; ++i)
    {
        char *d = (char *) dst + i * size;
        char *b = (char *) base + i * size;


        for (int j = 0; j < size; ++j)
            *(d++) = *(b++);
    }
}


void transpose_at_the_end(void *cars, int ind, int size, int *count)
{   
    char buf;

    for (; ind < *count - 1; ++ind)
    {
        char *p1 = ((char *) cars) + size * ind;
        char *p2 = ((char *) cars) + size * (ind + 1);


        for (int j = 0; j < size; ++j)
        {
            buf = *p1;
            *(p1++) = *p2;
            *(p2++) = buf;
        }
    }
}


void restore_key_table(help_table keys[], car_info cars[], int count)
{
    for (int i = 0; i < count; ++i)
    {
        keys[i].index = i;
        keys[i].price = cars[i].price;
    }
}