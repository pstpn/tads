#ifndef ___MY_TYPES___
#define ___MY_TYPES___

#include "my_def.h"


typedef struct
{
    double content[QUEUE_SIZE];
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
    node_t *p_nodes[QUEUE_SIZE];
    int len;
} p_node_t;


// typedef struct measure
// {
//     long long unsigned time;
//     int mem;
//     char expr[EXPR_LEN + 1];
// } measurement_table;

#endif // ___MY_TYPES___