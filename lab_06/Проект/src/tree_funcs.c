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


void apply(void *tree, void (*f)(void *, void *), void *arg, int is_pre, int is_file_tree)
{
    if (tree == NULL)
        return;

    if (is_pre)
        f(tree, arg);

    apply((is_file_tree) ? (void *) ((file_tree_node_t *) tree)->left: (void *) ((tree_node_t *) tree)->left, f, arg, is_pre, is_file_tree);
    apply((is_file_tree) ? (void *) ((file_tree_node_t *) tree)->right : (void *) ((tree_node_t *) tree)->right, f, arg, is_pre, is_file_tree);

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


void find_tree(void *tree, void *ind)
{
    tree_node_t *cur_tree = tree;

    int del_ind = *((int *) ind);


    if (cur_tree->index == del_ind)
        ind = NULL;
}


tree_node_t *find_right_min_tree(tree_node_t *tree)
{
    if (!(tree->left->left))
    {
        tree_node_t *tmp_tree = tree->left;


        tree->left = NULL;

        return tmp_tree;
    }

    tree_node_t *new_tree = find_right_min_tree(tree->left);


    return new_tree;
}


void destroy_node(void *node, void *trash)
{
    if (!trash)
        free(node);
}


tree_node_t *del_tree_node(tree_node_t *tree, int *ind)
{
    if (!tree)
        return NULL;

    if (tree->index == *ind)
    {
        *ind = -1;

        if (!(tree->left) && !(tree->right))
        {
            destroy_node((void *) tree, NULL);
            return NULL;
        }

        if (tree->left && !(tree->right))
        {
            tree_node_t *tmp_node = tree->left;


            destroy_node((void *) tree, NULL);
            return tmp_node;
        }

        if (tree->right && !(tree->left))
        {
            tree_node_t *tmp_node = tree->right;


            destroy_node((void *) tree, NULL);
            return tmp_node;
        }

        if (!(tree->right->left))
        {
            tree_node_t *tmp_node = tree->right;


            tree->right->left = tree->left;
            destroy_node((void *) tree, NULL);
            return tmp_node;
        }

        tree_node_t *new_tree = find_right_min_tree(tree->right);


        new_tree->left = tree->left;
        new_tree->right = tree->right;
        destroy_node((void *) tree, NULL);
        return new_tree;
    }

    if (tree->left && *ind > 0)
        tree->left = del_tree_node(tree->left, ind);
    if (tree->right && *ind > 0)
        tree->right = del_tree_node(tree->right, ind);

    return tree;
}