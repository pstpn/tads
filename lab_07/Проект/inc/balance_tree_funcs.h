#ifndef ___MY_B_TREE_FUNCS___
#define ___MY_B_TREE_FUNCS___

#include "my_types.h"
#include "my_def.h"


balance_tree_node_t *b_create_node(char *keyword);
int get_height(balance_tree_node_t *node);
int get_balance(balance_tree_node_t *node);
balance_tree_node_t *left_rotate(balance_tree_node_t *node);
balance_tree_node_t *right_rotate(balance_tree_node_t *node);
balance_tree_node_t *balance_tree(balance_tree_node_t *tree);
balance_tree_node_t *b_insert(balance_tree_node_t *tree, balance_tree_node_t *node);
void b_apply(void *tree, void (*f)(void *, void *), void *arg, int is_pre);
void b_destroy_node(void *node, void *trash);
balance_tree_node_t *create_keywords_balance_tree(char (*keywords)[MAX_KEYWORD_LEN + 1], int count);
balance_tree_node_t *b_find_tree_node(balance_tree_node_t *tree, char *cur_word, int *stop_finding, int *cmp_count);

#endif // ___MY_B_TREE_FUNCS___