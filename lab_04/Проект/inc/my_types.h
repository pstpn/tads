#ifndef ___MY_TYPES___
#define ___MY_TYPES___

#include "my_def.h"


typedef struct
{
    char content[STACK_SIZE];
    int len;
} arr_stack_t;

typedef struct node node_t;

struct node
{
    char item;
    node_t *next;
};

typedef struct
{
    node_t *top;
    int len;
} list_stack_t;

#endif // ___MY_TYPES___