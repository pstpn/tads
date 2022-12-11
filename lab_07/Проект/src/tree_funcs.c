#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_types.h"
#include "my_err.h"


tree_node_t *create_node(char *value)
{
    tree_node_t *node = malloc(sizeof(tree_node_t));
    if (node)
    {
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}


void apply(void *tree, void (*f)(void *, void *), void *arg)
{
    if (tree == NULL)
        return;

    apply((void *) ((tree_node_t *) tree)->left, f, arg);
    apply((void *) ((tree_node_t *) tree)->right, f, arg);

    f(tree, arg);
}


tree_node_t *insert(tree_node_t *tree, tree_node_t *node)
{
    if (tree == NULL)
        return node;

    int cmp = strcmp(tree->value, node->value);


    if (cmp > 0)
        tree->left = insert(tree->left, node);
    else
        tree->right = insert(tree->right, node);

    return tree;
}


tree_node_t *find_tree_node(tree_node_t *tree, char *cur_word, int *stop_finding)
{
    if (!tree)
        return NULL;

    int cmp = strcmp(tree->value, cur_word);

    tree_node_t *f_tree_node = NULL;


    if (!cmp)
    {
        *stop_finding = TRUE;
        return tree;
    }
    else if (cmp > 0 && tree->left && !(*stop_finding))
        f_tree_node = find_tree_node(tree->left, cur_word, stop_finding);
    else if (tree->right && !(*stop_finding))
        f_tree_node = find_tree_node(tree->right, cur_word, stop_finding);

    return f_tree_node;
}


void destroy_node(void *node, void *trash)
{
    if (!trash)
        free(node);
}


void tree_to_dot_2(void *tree, void *param)
{
    FILE *f = param;

    tree_node_t *cur_tree = (tree_node_t *) tree;


    if (cur_tree->left)
        fprintf(f, "%s -> %s;\n", cur_tree->value, cur_tree->left->value);
    else
        fprintf(f, "%s\n", cur_tree->value);

    if (cur_tree->right)
        fprintf(f, "%s -> %s;\n", cur_tree->value, cur_tree->right->value);
    else
        fprintf(f, "%s\n", cur_tree->value);
}


void export_to_dot_2(FILE *f, const char *tree_name, void *root_node)
{
    fprintf(f, "digraph %s {\n", tree_name);

    apply(root_node, tree_to_dot_2, f);

    fprintf(f, "}\n");
}
