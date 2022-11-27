#include <stdio.h>

#include "../inc/my_types.h"
#include "../inc/tree_funcs.h"
#include "../inc/my_def.h"


void tree_to_dot(void *tree, void *param)
{
    FILE *f = param;


    fprintf(f, "%c%d [label=\"%d | %c\"]\n", ((tree_node_t *) tree)->value, ((tree_node_t *) tree)->index,
        ((tree_node_t *) tree)->index, ((tree_node_t *) tree)->value);

    if (((tree_node_t *) tree)->left)
        fprintf(f, "%c%d -> %c%d;\n", ((tree_node_t *) tree)->value, ((tree_node_t *) tree)->index,
            ((tree_node_t *) tree)->left->value, ((tree_node_t *) tree)->left->index);
    else
        fprintf(f, "%c%d -> \"%d | %s\";\n", ((tree_node_t *) tree)->value, ((tree_node_t *) tree)->index,
            ((tree_node_t *) tree)->index, NULL_STR);

    if (((tree_node_t *) tree)->right)
        fprintf(f, "%c%d -> %c%d;\n", ((tree_node_t *) tree)->value, ((tree_node_t *) tree)->index,
            ((tree_node_t *) tree)->right->value, ((tree_node_t *) tree)->right->index);
    else
        fprintf(f, "%c%d -> \"%d | %s\";\n", ((tree_node_t *) tree)->value, ((tree_node_t *) tree)->index,
            ((tree_node_t *) tree)->index, NULL_STR);
}


void file_tree_to_dot(void *tree, void *param)
{
    FILE *f = param;


    fprintf(f, "%s%d [label=\"FILENAME: %s\nDATE: %d.%d.%d\"]\n", ((file_tree_node_t *) tree)->filename, ((file_tree_node_t *) tree)->date.num,
        ((file_tree_node_t *) tree)->filename, ((file_tree_node_t *) tree)->date.num,
        ((file_tree_node_t *) tree)->date.month, ((file_tree_node_t *) tree)->date.year);

    if (((file_tree_node_t *) tree)->left)
        fprintf(f, "%s%d -> %s%d;\n", ((file_tree_node_t *) tree)->filename, ((file_tree_node_t *) tree)->date.num,
            ((file_tree_node_t *) tree)->left->filename, ((file_tree_node_t *) tree)->left->date.num);

    if (((file_tree_node_t *) tree)->right)
        fprintf(f, "%s%d -> %s%d;\n", ((file_tree_node_t *) tree)->filename, ((file_tree_node_t *) tree)->date.num,
            ((file_tree_node_t *) tree)->right->filename, ((file_tree_node_t *) tree)->right->date.num);
}


void export_to_dot(FILE *f, const char *tree_name, void *root_node, int is_file_tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    if (!is_file_tree)
        apply(root_node, tree_to_dot, f, TRUE, is_file_tree);
    else
        apply(root_node, file_tree_to_dot, f, TRUE, is_file_tree);

    fprintf(f, "}\n");
}
