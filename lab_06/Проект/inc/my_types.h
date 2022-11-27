#ifndef ___MY_TYPES___
#define ___MY_TYPES___

#include "../inc/my_def.h"


typedef struct tree_node
{
    int index;
    
    char value;

    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;


typedef struct file_tree_node
{
    char filename[MAX_FILENAME_LEN + 1];
    struct 
    {
        int num;
        int month;
        int year;
    } date;
    
    struct file_tree_node *left;
    struct file_tree_node *right;
} file_tree_node_t;


// typedef struct measure
// {
//     long long unsigned time;
//     int mem;
//     int queue_len;
// } measurement_table;

#endif // ___MY_TYPES___