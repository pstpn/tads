#include <stdio.h>

#include "my_types.h"
#include "my_def.h"
#include "balance_tree_funcs.h"


void tree_to_dot(void *tree, void *param)
{
    FILE *f = param;

    balance_tree_node_t *balance_tree = (balance_tree_node_t *) tree;


    if (balance_tree->left)
        fprintf(f, "%s -> %s;\n", balance_tree->keyword, balance_tree->left->keyword);
    else
        fprintf(f, "%s\n", balance_tree->keyword);

    if (balance_tree->right)
        fprintf(f, "%s -> %s;\n", balance_tree->keyword, balance_tree->right->keyword);
    else
        fprintf(f, "%s\n", balance_tree->keyword);
}


void export_to_dot(FILE *f, const char *tree_name, void *root_node)
{
    fprintf(f, "digraph %s {\n", tree_name);

    apply(root_node, tree_to_dot, f, TRUE);

    fprintf(f, "}\n");
}
