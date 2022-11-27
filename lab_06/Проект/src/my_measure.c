#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "../inc/my_types.h"
#include "../inc/my_err.h"
#include "../inc/tree_funcs.h"
#include "../inc/graph.h"


unsigned long long microseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long) - 1;
    return val.tv_sec * 1000000ULL + val.tv_usec * 1ULL;
}


tree_node_t *generate_tree(int count, int depth)
{
    int index = 0;

    tree_node_t *root_node = calloc(1, sizeof(tree_node_t));
    tree_node_t *cur_head_node = root_node;


    root_node->index = index++;
    root_node->value = 'r';

    root_node->left = NULL;
    root_node->right = NULL;


    depth = (int) (count-- * ((double) depth / 100));

    for (; depth; --depth, --count, cur_head_node = cur_head_node->left)
    {
        tree_node_t *cur_node_1 = calloc(1, sizeof(tree_node_t));
        

        cur_node_1->index = index++;
        cur_node_1->value = 'a';

        cur_node_1->left = NULL;
        cur_node_1->right = NULL;

        tree_node_t *cur_node_2 = calloc(1, sizeof(tree_node_t));
        

        cur_node_2->index = index++;
        cur_node_2->value = 'a';

        cur_node_2->left = NULL;
        cur_node_2->right = NULL;


        cur_head_node->left = cur_node_1;
        cur_head_node->right = cur_node_2;
    }

    cur_head_node = (cur_head_node->left) ? cur_head_node->left : cur_head_node;

    for (; count; --count, cur_head_node = cur_head_node->left)
    {
        tree_node_t *cur_node = calloc(1, sizeof(tree_node_t));
        

        cur_node->index = index++;
        cur_node->value = 'a';

        cur_node->left = NULL;
        cur_node->right = NULL;

        cur_head_node->left = cur_node;
    }

    return root_node;
}


int get_measures(measurement_table table[MEAS_COUNT])
{
    int counts[] = { 12, 24, 48, 64, 100 };
    int branching[] = { 0, 25, 50, 75, 100 };

    table[0].time = 1;
    
    // long long unsigned beg, end;


    for (int i = 0; i < 1; ++i)
    {
        for (int j = 0; j < 1; ++j)
        {
            tree_node_t *root_node = generate_tree(counts[i], branching[j + 4]);

            // beg = microseconds_now();


            FILE *f = fopen(TREE_GRAPH_FILENAME, "w");
            

            export_to_dot(f, TREE_NAME, root_node, FALSE);

            fclose(f);

            system(MAKE_TREE_GRAPH_COMMAND);

            system(OPEN_TREE_PNG_COMMAND);

            // end = microseconds_now();

            
            apply(root_node, destroy_node, NULL, FALSE, FALSE);
        }

        ;
    }
    
    return SUCCESS;
}