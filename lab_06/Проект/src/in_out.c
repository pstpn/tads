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


void print_tree_node_info(void *tree, void *param)
{
    FILE *f = param;


    draw_line(TABLE_WIDTH);

    fprintf(f, NODE_INFO_MSG, BLUE, PURPLE, INDEX_WIDTH,
    ((tree_node_t *) tree)->index, RESET, BLUE, GREEN, VALUE_WIDTH,
    ((tree_node_t *) tree)->value, RESET, BLUE, RED, POINTER_WIDTH,
    tree, RESET, PURPLE, INDEX_WIDTH,
    (((tree_node_t *) tree)->left) ? ((tree_node_t *) ((tree_node_t *) tree)->left)->index : -1, RESET, GREEN,
    CHILD_WIDTH, (((tree_node_t *) tree)->left) ? ((tree_node_t *) ((tree_node_t *) tree)->left)->value : ' ',
    RESET,PURPLE, INDEX_WIDTH,
    (((tree_node_t *) tree)->right) ? ((tree_node_t *) ((tree_node_t *) tree)->right)->index : -1, RESET, GREEN,
    CHILD_WIDTH, (((tree_node_t *) tree)->right) ? ((tree_node_t *) ((tree_node_t *) tree)->right)->value : ' ', RESET);

    draw_line(TABLE_WIDTH);
    printf("\n");
}