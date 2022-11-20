#include <stdlib.h>
#include <math.h>

#include "../inc/my_types.h"
#include "../inc/my_err.h"
#include "../inc/arr_funcs.h"
#include "../inc/my_msgs.h"


void init_queue(arr_queue_t *arr_queue)
{
    for (int i = 0; i < QUEUE_SIZE; ++i)
        push_arr_queue(arr_queue, 0.0);
}


double get_random_double(double min, double max)
{
    return (double) (rand()) / RAND_MAX * (max - min) + min;
}


int arr_modeling(void)
{
    int first_machine_act_count = 0;
    int second_machine_act_count = 0;

    int cur_prob;
    
    double cur_elem;
    
    double cur_time;
    double all_time;
    
    double first_machine_timer = 0;
    double second_machine_timer = 0;
    
    double first_all_times = 0;
    double second_all_times = 0;

    unsigned long first_queue_lens = 0;
    unsigned long second_queue_lens = 0;

    unsigned long first_count_per_thous = 0;
    unsigned long second_count_per_thous = 0;


    arr_queue_t *first_arr_queue = create_arr_queue();
    if (!first_arr_queue)
        return ERR_ALLOC;

    list_queue_t *second_arr_queue = create_arr_queue();
    if (!second_arr_queue)
    {
        destroy_arr_queue(first_arr_queue);
        return ERR_ALLOC;
    }

    init_queue(first_arr_queue);


    while (second_machine_act_count < MAX_REQUESTS_COUNT)
    {
        if ((second_machine_timer < first_machine_timer && second_arr_queue->len > 0) ||
            (second_machine_timer > first_machine_timer && !first_arr_queue->len))
        {
            cur_time = get_random_double(SECOND_MACHINE_START_WORK_TIME, SECOND_MACHINE_FINISH_WORK_TIME);

            pop_arr_queue(second_arr_queue, &cur_elem);
            
            second_all_times += all_time - cur_time;
            second_machine_timer += all_time;

            if (second_machine_timer > first_machine_timer && first_arr_queue->len > 0)
                all_time += second_machine_timer - first_machine_act_count;
            else if (second_machine_timer > first_machine_timer)
                all_time += cur_time;
                
            push_arr_queue(first_arr_queue, all_time);

            second_queue_lens += second_arr_queue->len;

            ++first_count_per_thous;
            ++second_machine_act_count;
        }
        else if (first_arr_queue->len > 0)
        {
            cur_time = get_random_double(FIRST_MACHINE_START_WORK_TIME, FIRST_MACHINE_FINISH_WORK_TIME);

            pop_arr_queue(first_arr_queue, &cur_elem);
            
            first_all_times += all_time - cur_time;
            first_machine_timer += all_time;

            cur_prob = get_random_double(MIN_PROB, MAX_PROB);

            if (cur_prob > PROB)
                push_arr_queue(second_arr_queue, all_time);
            else
                push_arr_queue(first_arr_queue, all_time);

            first_queue_lens += first_arr_queue->len;

            ++first_count_per_thous;
            ++first_machine_act_count;
        }
        
        if (!second_machine_act_count &&
            !(second_machine_act_count % SEP_REQUEST_NUM))
        {
            printf(ARR_MODELING_TMP_MSG, first_machine_act_count, second_machine_act_count,
                first_arr_queue->len, second_arr_queue->len, first_queue_lens / first_count_per_thous,
                second_queue_lens / second_count_per_thous);

            first_queue_lens = second_queue_lens = 0;
            
            first_count_per_thous = second_count_per_thous = 0;
        }
    }

    double machine_reference = MAX_REQUESTS_COUNT * ((double)
        (SECOND_MACHINE_START_WORK_TIME + SECOND_MACHINE_FINISH_WORK_TIME) / 2);
    
    double error = fabs((double) (second_machine_timer - machine_reference) / machine_reference);


    printf(ARR_MODELING_MSG, all_time, error, first_machine_act_count,
        first_all_times / first_machine_act_count, 
        second_all_times / second_machine_act_count,
        all_time - second_machine_timer);
}