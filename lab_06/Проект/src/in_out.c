#include <stdio.h>

#include "../inc/my_types.h"
#include "../inc/my_def.h"
#include "../inc/my_msgs.h"
#include "../inc/my_err.h"


int get_in_elem(FILE *f, char *elem)
{
    char buf;


    if (fscanf(f, "%c%c", elem, &buf) != 2)
        return ERR_READING;
    if (buf != '\n')
        return ERR_READING;

    return SUCCESS;
}


void clear_buf(FILE *f)
{
    char buf = '\0';

    
    while (buf != '\n')
        buf = fgetc(f);
}


void draw_line(int len)
{
    for (int i = 0; i < len; ++i)
        printf("-");

    printf("\n");
}


void print_node_info(tree_node_t *tree, void *param)
{
    FILE *f = param;


    draw_line(TABLE_WIDTH);

    fprintf(f, NODE_INFO_MSG, BLUE, PURPLE, INDEX_WIDTH,
    tree->index, RESET, BLUE, GREEN, VALUE_WIDTH,
    tree->value, RESET, BLUE, RED, POINTER_WIDTH,
    (void *) &tree, RESET, PURPLE, INDEX_WIDTH,
    (tree->left) ? tree->left->index : -1, RESET, GREEN,
    CHILD_WIDTH, (tree->left) ? tree->left->value : ' ',
    RESET,PURPLE, INDEX_WIDTH,
    (tree->right) ? tree->right->index : -1, RESET, GREEN,
    CHILD_WIDTH, (tree->right) ? tree->right->value : ' ', RESET);

    draw_line(TABLE_WIDTH);
    printf("\n");
}