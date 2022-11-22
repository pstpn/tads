#ifndef ___MY_TREE_FUNCS___
#define ___MY_TREE_FUNCS___

#include "my_types.h"


tree_node_t *create_node(int index, char value);
void apply(tree_node_t *tree, void (*f)(tree_node_t *, void *), void *arg, int is_pre);
tree_node_t *insert(tree_node_t *tree, tree_node_t *node);
void destroy_node(tree_node_t *node, void *trash);

#endif // ___MY_TREE_FUNCS___