#include <stdlib.h>

#include "../inc/my_types.h"


tree_node_t *create_node(int index, char value)
{
    tree_node_t *node = malloc(sizeof(tree_node_t));
    if (node)
    {
        node->index = index;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }


    return node;
}


void apply(tree_node_t *tree, void (*f)(tree_node_t *, void *), void *arg, int is_pre)
{
    if (tree == NULL)
        return;

    if (is_pre)
        f(tree, arg);

    apply(tree->left, f, arg, is_pre);
    apply(tree->right, f, arg, is_pre);

    if (!is_pre)
        f(tree, arg);
}


tree_node_t *insert(tree_node_t *tree, tree_node_t *node)
{
    if (tree == NULL)
        return node;

    if (node->value < tree->value)
        tree->left = insert(tree->left, node);
    else
        tree->right = insert(tree->right, node);

    return tree;
}


void destroy_node(tree_node_t *node, void *trash)
{
    if (!trash)
        free(node);
}