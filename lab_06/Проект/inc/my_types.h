#ifndef ___MY_TYPES___
#define ___MY_TYPES___


typedef struct tree_node
{
    int index;
    
    char value;

    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

// typedef struct measure
// {
//     long long unsigned time;
//     int mem;
//     int queue_len;
// } measurement_table;

#endif // ___MY_TYPES___