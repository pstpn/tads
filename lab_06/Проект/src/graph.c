#include <stdio.h>

#include "../inc/my_types.h"
#include "../inc/tree_funcs.h"
#include "../inc/my_def.h"


void to_dot(tree_node_t *tree, void *param)
{
    FILE *f = param;


    fprintf(f, "%c%d [label=\"%d | %c\"]\n", tree->value, tree->index, tree->index, tree->value);

    if (tree->left)
        fprintf(f, "%c%d -> %c%d;\n", tree->value, tree->index, tree->left->value, tree->left->index);
    else
        fprintf(f, "%c%d -> \"%d | %s\";\n", tree->value, tree->index, tree->index, NULL_STR);

    if (tree->right)
        fprintf(f, "%c%d -> %c%d;\n", tree->value, tree->index, tree->right->value, tree->right->index);
    else
        fprintf(f, "%c%d -> \"%d | %s\";\n", tree->value, tree->index, tree->index, NULL_STR);
}


void export_to_dot(FILE *f, const char *tree_name, tree_node_t *root_node)
{
    fprintf(f, "digraph %s {\n", tree_name);

    apply(root_node, to_dot, f, TRUE);

    fprintf(f, "}\n");
}
