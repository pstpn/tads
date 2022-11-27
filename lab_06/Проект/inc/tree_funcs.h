#ifndef ___MY_TREE_FUNCS___
#define ___MY_TREE_FUNCS___

#include "my_types.h"


tree_node_t *create_node(int index, char value);
void apply(void *tree, void (*f)(void *, void *), void *arg, int is_pre, int is_file_tree);
tree_node_t *insert(tree_node_t *tree, tree_node_t *node);
tree_node_t *find_right_min_tree(tree_node_t *tree);
file_tree_node_t *find_right_min_file_tree(file_tree_node_t *tree);
void destroy_node(void *node, void *trash);
tree_node_t *del_tree_node(tree_node_t *tree, int *ind);
tree_node_t *find_tree_node(tree_node_t *tree, int *ind);
file_tree_node_t *generate_file_tree(int count);
file_tree_node_t *del_file_tree_nodes(file_tree_node_t *tree, int num, int month, int year);

#endif // ___MY_TREE_FUNCS___