#ifndef ___MY_TREE_FUNCS___
#define ___MY_TREE_FUNCS___

#include "my_types.h"


tree_node_t *create_node(int index, char value);
void apply(void *tree, void (*f)(void *, void *), void *arg, int is_pre, int is_file_tree);
tree_node_t *insert(tree_node_t *tree, tree_node_t *node);
void find_tree(void *tree, void *ind);
tree_node_t *find_right_min_tree(tree_node_t *tree);
tree_node_t *del_tree_node(tree_node_t *tree, int *ind);
void destroy_node(void *node, void *trash);

#endif // ___MY_TREE_FUNCS___