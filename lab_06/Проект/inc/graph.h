#ifndef ___MY_GRAPH___
#define ___MY_GRAPH___

#include <stdio.h>

#include "my_types.h"


void to_dot(tree_node_t *tree, FILE *f);
void export_to_dot(FILE *f, const char *tree_name, tree_node_t *root_node);

#endif // ___MY_GRAPH___