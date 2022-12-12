#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "my_types.h"
#include "my_def.h"
#include "my_err.h"


unsigned int hash_func(const char *str, unsigned int table_len)
{
    unsigned long hash = 5381;
    // unsigned long hash = 0;
    int c;

    while (*str)
    {
        c = *(str++);
        hash = hash * 33 + c;
    }

	// return hash;

    // for(; *str; ++str)
    // {
    //     hash += (unsigned char) (*str);
    //     hash -= (hash << 13) | (hash >> 19);
    // }

    // for (int i = 0; str[i] != '\0'; ++i)
    //     hash += str[i];

    return (hash) % table_len;
}


void free_hash_table(hash_table_t *hash_table)
{
    for (int i = 0; i < hash_table->size; ++i)
        if (((keyword_info_t **) hash_table->data)[i]->keyword)
            free(((keyword_info_t **) hash_table->data)[i]);

    free(hash_table->data);
    free(hash_table);
}


void free_list_hash_table(hash_table_t *hash_table)
{
    for (int i = 0; i < hash_table->size; ++i)
    {
        list_keyword_info_t *cur_keyword = ((list_keyword_info_t **) hash_table->data)[i];


        while (cur_keyword)
        {
            free(cur_keyword);
            cur_keyword = cur_keyword->next;
        }
    }

    free(hash_table->data);
    free(hash_table);
}


int fix_collision(hash_table_t **hash_table, keyword_info_t *keyword, int cur_index, int table_size)
{
    for (int i = 0, step = 1; i < 3; ++i)
    {
        if (cur_index + step * step >= table_size)
        {
            cur_index = -1;
            step = 1;
        }

        if (((keyword_info_t **) (*hash_table)->data)[cur_index + step * step]->keyword)
            ++step;
        else
        {
            ((keyword_info_t **) (*hash_table)->data)[cur_index + step * step] = keyword;
            return SUCCESS;
        }
    }

    return NEED_RESTRUCT;
}


int fix_list_collision(hash_table_t **hash_table, list_keyword_info_t *keyword, int cur_index)
{
    list_keyword_info_t *cur_keyword = ((list_keyword_info_t **) (*hash_table)->data)[cur_index];


    for (int i = 0; i < 2; ++i, cur_keyword = cur_keyword->next)
        if (!cur_keyword->next)
        {
            cur_keyword->next = keyword;
            return SUCCESS;
        }

    return NEED_RESTRUCT;
}


int insert_in_hash_table(hash_table_t **hash_table, char *keyword, char *help, int table_size)
{
    keyword_info_t *cur_keyword_info = malloc(sizeof(keyword_info_t));
    if (!cur_keyword_info)
    {
        free_hash_table(*hash_table);
        return ERR_ALLOC;
    }

    unsigned int cur_index = hash_func(keyword, table_size);

    
    strcpy(cur_keyword_info->keyword, keyword);
    strcpy(cur_keyword_info->help, help);

    if (!((keyword_info_t **) (*hash_table)->data)[cur_index]->keyword)
        ((keyword_info_t **) (*hash_table)->data)[cur_index] = cur_keyword_info;
    else
        if (fix_collision(hash_table, cur_keyword_info, cur_index, table_size) == NEED_RESTRUCT)
            return NEED_RESTRUCT;
        
    return SUCCESS;
}


int insert_in_list_hash_table(hash_table_t **hash_table, char *keyword, char *help, int table_size)
{
    list_keyword_info_t *cur_keyword_info = malloc(sizeof(list_keyword_info_t));
    if (!cur_keyword_info)
    {
        free_list_hash_table(*hash_table);
        return ERR_ALLOC;
    }

    unsigned int cur_index = hash_func(keyword, table_size);

    
    cur_keyword_info->next = NULL;

    strcpy(cur_keyword_info->keyword, keyword);
    strcpy(cur_keyword_info->help, help);

    if (!((list_keyword_info_t **) (*hash_table)->data)[cur_index]->keyword)
        ((list_keyword_info_t **) (*hash_table)->data)[cur_index] = cur_keyword_info;
    else
        if (fix_list_collision(hash_table, cur_keyword_info, cur_index) == NEED_RESTRUCT)
            return NEED_RESTRUCT;
        
    return SUCCESS;
}


int create_hash_table(hash_table_t **hash_table, char (*keywords)[MAX_KEYWORD_LEN + 1],
char (*help)[MAX_HELP_LEN + 1], int k_count, int table_size, int is_list_table)
{
    *hash_table = malloc(sizeof(hash_table_t));
    if (!(*hash_table))
        return ERR_ALLOC;


    (*hash_table)->data = calloc(table_size, (is_list_table) ? sizeof(list_keyword_info_t *) : sizeof(keyword_info_t *));
    if (!(*hash_table)->data)
    {
        free(hash_table);
        return ERR_ALLOC;
    }


    (*hash_table)->size = table_size;

    for (int i = 0; i < k_count; ++i)
    {
        int rc;


        if (is_list_table)
            rc = insert_in_list_hash_table(hash_table, keywords[i], help[i], table_size);
        else
            rc = insert_in_hash_table(hash_table, keywords[i], help[i], table_size);

        if (rc == ERR_ALLOC)
            return ERR_ALLOC;
        else if (rc == NEED_RESTRUCT)
            return NEED_RESTRUCT;
    }

    return SUCCESS;
}


int find_keyword(hash_table_t *hash_table, char *keyword, int *cmp_count)
{
    unsigned int cur_index = hash_func(keyword, hash_table->size);


    for (int i = 0, step = 0; i < 4; ++i)
    {
        ++(*cmp_count);

        if ((int) cur_index + step * step >= hash_table->size)
        {
            cur_index = -1;
            step = 1;
        }

        if (((keyword_info_t **) hash_table->data)[cur_index + step * step]->keyword &&
            strcmp(((keyword_info_t **) hash_table->data)[cur_index + step * step]->keyword, keyword))
            ++step;
        else if (((keyword_info_t **) hash_table->data)[cur_index + step * step]->keyword)
            return (int) cur_index + step * step;
    }

    return -1;
}


list_keyword_info_t *find_list_keyword(hash_table_t *hash_table, char *keyword, int *cmp_count)
{
    unsigned int cur_index = hash_func(keyword, hash_table->size);

    list_keyword_info_t *cur_keyword = ((list_keyword_info_t **) hash_table->data)[cur_index];


    for (int i = 0; i < 4 && cur_keyword; ++i, cur_keyword = cur_keyword->next)
    {
        ++(*cmp_count);

        if (!strcmp(cur_keyword->keyword, keyword))
            return cur_keyword;
    }

    return NULL;
}