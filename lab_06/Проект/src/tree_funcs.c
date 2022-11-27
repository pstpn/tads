#include <stdlib.h>

#include "../inc/my_types.h"
#include "../inc/my_err.h"
#include "../inc/tools.h"


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


file_tree_node_t *find_right_min_file_tree(file_tree_node_t *tree)
{
    if (!(tree->left->left))
    {
        file_tree_node_t *tmp_tree = tree->left;


        tree->left = NULL;

        return tmp_tree;
    }

    file_tree_node_t *new_tree = find_right_min_file_tree(tree->left);


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


tree_node_t *find_tree_node(tree_node_t *tree, int *ind)
{
    if (!tree)
        return NULL;

    if (tree->index == *ind)
    {
        *ind = -1;
        return tree;
    }

    tree_node_t *f_tree_node = NULL;


    if (tree->left && *ind > 0)
        f_tree_node = find_tree_node(tree->left, ind);
    if (tree->right && *ind > 0)
        f_tree_node = find_tree_node(tree->right, ind);

    return f_tree_node;
}


file_tree_node_t *random_insert(file_tree_node_t *file_tree, file_tree_node_t *cur_node)
{
    if (!file_tree)
        return cur_node;

    int is_left_branch = rand() % 2;


    if (is_left_branch)
        file_tree->left = random_insert(file_tree->left, cur_node);
    else
        file_tree->right = random_insert(file_tree->right, cur_node);

    return file_tree;
}


file_tree_node_t *generate_file_tree(int count)
{
    file_tree_node_t *root_file_tree = NULL;


    for (int i = 0; i < count; ++i)
    {
        file_tree_node_t *cur_node = calloc(1, sizeof(file_tree_node_t));
        if (!cur_node)
        {
            destroy_node((void *) root_file_tree, NULL);
            return NULL;
        }


        int filename_len = get_random_int(1, MAX_FILENAME_LEN - 20);


        for (int k = 0; k < filename_len; ++k)
            cur_node->filename[k] = get_random_int(MIN_ASCII, MAX_ASCII);

        cur_node->date.num = get_random_int(1, 28);
        cur_node->date.month = get_random_int(1, 12);
        cur_node->date.year = get_random_int(1993, 2022);

        root_file_tree = random_insert(root_file_tree, cur_node);
    }

    return root_file_tree;
}


file_tree_node_t *del_file_tree_nodes(file_tree_node_t *tree, int num, int month, int year)
{
    if (!tree)
        return NULL;  

    if (tree->left)
        tree->left = del_file_tree_nodes(tree->left, num, month, year);

    if (tree->right)
        tree->right = del_file_tree_nodes(tree->right, num, month, year);
        
    if (tree->date.year < year || (tree->date.year == year && tree->date.month < month)
    || (tree->date.year == year && tree->date.month == month && tree->date.num < num))
    {
        if (!(tree->left) && !(tree->right))
        {
            destroy_node((void *) tree, NULL);
            return NULL;
        }

        if (tree->left && !(tree->right))
        {
            file_tree_node_t *tmp_node = tree->left;


            destroy_node((void *) tree, NULL);
            return tmp_node;
        }

        if (tree->right && !(tree->left))
        {
            file_tree_node_t *tmp_node = tree->right;


            destroy_node((void *) tree, NULL);
            return tmp_node;
        }

        if (!(tree->right->left))
        {
            file_tree_node_t *tmp_node = tree->right;


            tree->right->left = tree->left;
            destroy_node((void *) tree, NULL);
            return tmp_node;
        }

        file_tree_node_t *new_tree = find_right_min_file_tree(tree->right);


        new_tree->left = tree->left;
        new_tree->right = tree->right;
        destroy_node((void *) tree, NULL);
        return new_tree;
    }

    return tree;
}