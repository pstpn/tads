#ifndef ___MY_TYPES___
#define ___MY_TYPES___

#include "my_def.h"


typedef struct tree_node
{
    char *value;

    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

typedef struct balance_tree_node
{    
    char *keyword;
    int height;

    struct balance_tree_node *left;
    struct balance_tree_node *right;
} balance_tree_node_t;


typedef struct 
{
    char keyword[MAX_KEYWORD_LEN + 1];
    char help[MAX_HELP_LEN + 1];
} keyword_info_t;


typedef struct list_keyword
{
    char keyword[MAX_KEYWORD_LEN + 1];
    char help[MAX_HELP_LEN + 1];

    struct list_keyword *next;
} list_keyword_info_t;


typedef struct 
{
    void *data;
    int size;
} hash_table_t;


typedef struct measure
{
    long long unsigned time;
    char type;
    int count;
    int mem;
} measurement_table;

#endif // ___MY_TYPES___