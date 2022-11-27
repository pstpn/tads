#ifndef ___MY_GRAPH___
#define ___MY_GRAPH___

#include <stdio.h>

#include "my_types.h"


void tree_to_dot(tree_node_t *tree, void *param);
void export_to_dot(FILE *f, const char *tree_name, void *root_node, int is_file_tree);

#endif // ___MY_GRAPH___