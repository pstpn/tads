#ifndef ___MY_TYPES___
#define ___MY_TYPES___


typedef struct balance_tree_node
{    
    char *keyword;
    int height;

    struct balance_tree_node *left;
    struct balance_tree_node *right;
} balance_tree_node_t;


// typedef struct measure
// {
//     long long unsigned time;
//     int branching;
//     int mem;
// } measurement_table;

#endif // ___MY_TYPES___