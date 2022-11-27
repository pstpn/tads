#ifndef ___MY_TYPES___
#define ___MY_TYPES___

#include "my_def.h"


typedef struct
{
    double content[MAX_QUEUE_SIZE];
    int len;
} arr_queue_t;

typedef struct node node_t;

struct node
{
    double item;
    node_t *next;
};

typedef struct
{
    node_t *top;
    int len;
} list_queue_t;

typedef struct 
{
    node_t *p_nodes[MAX_QUEUE_SIZE];
    int len;
} p_node_t;


typedef struct 
{
    int first_machine_min_work_time;
    int first_machine_max_work_time;

    int second_machine_min_work_time;
    int second_machine_max_work_time;

    double prob;
} process_info_t;


typedef struct measure
{
    long long unsigned time;
    int mem;
    int queue_len;
} measurement_table;

#endif // ___MY_TYPES___