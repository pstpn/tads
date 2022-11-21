#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

#include "../inc/my_types.h"
#include "../inc/arr_funcs.h"
#include "../inc/list_funcs.h"
#include "../inc/modeling.h"
#include "../inc/my_err.h"


unsigned long long microseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long) - 1;
    return val.tv_sec * 1000000ULL + val.tv_usec * 1ULL;
}


int get_measures(measurement_table table[MEAS_COUNT])
{
    int lens[] = { 100, 250, 500, 1000 };
    
    long long unsigned beg, end;


    for (int i = 0, k = 0; i < MEAS_COUNT / 4; ++i, k += 2)
    {
        arr_queue_t *arr_queue = create_arr_queue();


        beg = microseconds_now();

        for (int j = 0; j < lens[i]; ++j)
            push_arr_queue(arr_queue, 0.0);

        end = microseconds_now();

        table[k].time = (end - beg);
        table[k].mem = sizeof(arr_queue_t);
        table[k].queue_len = lens[i];

        double pop_elem;


        beg = microseconds_now();

        for (int j = 0; j < lens[i]; ++j)
            pop_arr_queue(arr_queue, &pop_elem);

        end = microseconds_now();

        table[k + 1].time = (end - beg);
        table[k + 1].mem = sizeof(arr_queue_t);
        table[k + 1].queue_len = lens[i];

        destroy_arr_queue(arr_queue);


        list_queue_t *list_queue = create_list_queue();


        beg = microseconds_now();

        for (int j = 0; j < lens[i]; ++j)
        {
            node_t *cur = malloc(sizeof(node_t));
            if (!cur)
                return ERR_ALLOC;

            cur->item = 0.0;
            cur->next = NULL;

            push_list_queue(&list_queue, cur);
        }

        end = microseconds_now();

        table[MEAS_COUNT / 2 + k].time = (end - beg);
        table[MEAS_COUNT / 2 + k].mem = list_queue->len * sizeof(node_t);
        table[MEAS_COUNT / 2 + k].queue_len = lens[i];

        beg = microseconds_now();

        for (int j = 0; j < lens[i]; ++j)
            pop_list_queue(list_queue, &pop_elem);

        end = microseconds_now();

        table[MEAS_COUNT / 2 + k + 1].time = (end - beg);
        table[MEAS_COUNT / 2 + k + 1].mem = list_queue->len * sizeof(node_t);
        table[MEAS_COUNT / 2 + k + 1].queue_len = lens[i];

        destroy_list_queue(list_queue);
    }
    
    return SUCCESS;
}