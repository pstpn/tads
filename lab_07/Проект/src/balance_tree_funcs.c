#include <stdlib.h>
#include <string.h>

#include "my_types.h"
#include "my_def.h"
#include "my_err.h"


balance_tree_node_t *create_node(char *keyword)
{
    balance_tree_node_t *node = malloc(sizeof(balance_tree_node_t));


    if (node)
    {
        node->height = 0;
        node->keyword = keyword;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}


int get_height(balance_tree_node_t *node)
{
    if (!node->right && !node->left)
        return 0;
    else if (!node->right && node->left)
        return node->left->height + 1;
    else if (node->right && !node->left)
        return node->right->height + 1;
    else
        return (node->right->height > node->left->height) ?
            node->right->height + 1 : node->left->height + 1;
}


int get_balance(balance_tree_node_t *node)
{
    if (!node->right && !node->left)
        return 0;
    else if (!node->right && node->left)
        return (node->left->height >= 2) ? 2 : node->left->height;
    else if (node->right && !node->left)
        return (node->right->height >= 2) ? -2 : -(node->right->height);
    else
        return node->left->height - node->right->height;
}


balance_tree_node_t *left_rotate(balance_tree_node_t *node)
{
	balance_tree_node_t *new_node = node->right;


    node->right = new_node->left;
    new_node->left = node;
    
    new_node->height = get_height(new_node);
    node->height = get_height(node);

	return new_node;
}


balance_tree_node_t *right_rotate(balance_tree_node_t *node)
{
	balance_tree_node_t *new_node = node->left;
    

    node->left = new_node->right;
    new_node->right = node;
    
    new_node->height = get_height(new_node);
    node->height = get_height(node);

	return new_node;
}


balance_tree_node_t *balance_tree(balance_tree_node_t *tree)
{
    tree->height = get_height(tree);

	if(get_balance(tree) == -2)
	{
		if(get_balance(tree->right) > 0)
			tree->right = right_rotate(tree->right);

		return left_rotate(tree);
	}
	if(get_balance(tree) == 2)
	{
		if(get_balance(tree->left) < 0)
			tree->left = left_rotate(tree->left);

		return right_rotate(tree);
	}

	return tree;
}


balance_tree_node_t *insert(balance_tree_node_t *tree, balance_tree_node_t *node)
{
    if (tree == NULL)
        return node;

    int cmp = strcmp(tree->keyword, node->keyword);


    if (cmp > 0)
    {
        tree->left = insert(tree->left, node);

        tree = balance_tree(tree);
    }
    else if (cmp < 0)
    {
        tree->right = insert(tree->right, node);

        tree = balance_tree(tree);
    }
    else
    {
        node->keyword = NULL;
        return NULL;
    }

    return tree;
}


void apply(void *tree, void (*f)(void *, void *), void *arg, int is_pre)
{
    if (tree == NULL)
        return;

    if (is_pre)
        f(tree, arg);

    apply((void *) ((balance_tree_node_t *) tree)->left, f, arg, is_pre);
    apply((void *) ((balance_tree_node_t *) tree)->right, f, arg, is_pre);

    if (!is_pre)
        f(tree, arg);
}


void destroy_node(void *node, void *trash)
{
    if (!trash)
        free(node);
}


balance_tree_node_t *create_keywords_balance_tree(char (*keywords)[MAX_KEYWORD_LEN + 1], int count)
{
    balance_tree_node_t *root_node = NULL;


    for (int i = 0; i < count; ++i)
    {
        balance_tree_node_t *cur_node = create_node(keywords[i]);
        if (!cur_node)
        {
            apply(root_node, destroy_node, NULL, FALSE);
            return NULL;
        }


        root_node = insert(root_node, cur_node);
    }

    return root_node;
}