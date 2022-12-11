#ifndef ___MY_TREE_FUNCS___
#define ___MY_TREE_FUNCS___

#include "my_types.h"


tree_node_t *create_node(char *value);
void apply(void *tree, void (*f)(void *, void *), void *arg);
tree_node_t *insert(tree_node_t *tree, tree_node_t *node);
tree_node_t *find_tree_node(tree_node_t *tree, char *cur_word, int *stop_finding);
void destroy_node(void *node, void *trash);
void tree_to_dot_2(void *tree, void *param);
void export_to_dot_2(FILE *f, const char *tree_name, void *root_node);

#endif // ___MY_TREE_FUNCS___