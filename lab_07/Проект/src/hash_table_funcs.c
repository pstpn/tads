#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "my_types.h"
#include "my_def.h"
#include "my_err.h"


unsigned int hash_func(const char *str, unsigned int table_len)
{
    unsigned int hash = 0;


    for(; *str; ++str)
    {
        hash += (unsigned char) (*str);
        hash -= (hash << 13) | (hash >> 19);
    }

    return hash % table_len;
}


void free_hash_table(hash_table_t *hash_table)
{
    for (int i = 0; i < hash_table->size; ++i)
        if (hash_table->data[i]->keyword)
            free(hash_table->data[i]);

    free(hash_table->data);
    free(hash_table);
}


int fix_collision(hash_table_t **hash_table, keyword_info_t *keyword, int cur_index, int k_count)
{
    for (int i = 0, step = 1; i < 4; ++i)
    {
        if (cur_index + step >= k_count)
        {
            cur_index = -1;
            step = 1;
        }

        if ((*hash_table)->data[cur_index + step]->keyword)
        {
            ++step;
            step *= step;
        }
        else
        {
            (*hash_table)->data[cur_index + step] = keyword;
            return SUCCESS;
        }
    }

    return NEED_RESTRUCT;
}


int insert_in_hash_table(hash_table_t **hash_table, char *keyword, char *help, int k_count, int table_size)
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

    if (!(*hash_table)->data[cur_index]->keyword)
        (*hash_table)->data[cur_index] = cur_keyword_info;
    else
        if (fix_collision(hash_table, cur_keyword_info, cur_index, k_count) == NEED_RESTRUCT)
            return NEED_RESTRUCT;
        
    return SUCCESS;
}


int create_hash_table(hash_table_t **hash_table, char (*keywords)[MAX_KEYWORD_LEN + 1], char (*help)[MAX_HELP_LEN + 1], int k_count, int table_size)
{
    *hash_table = malloc(sizeof(hash_table_t));
    if (!(*hash_table))
        return ERR_ALLOC;


    (*hash_table)->data = calloc(table_size, sizeof(keyword_info_t *));
    if (!(*hash_table)->data)
    {
        free(hash_table);
        return ERR_ALLOC;
    }


    (*hash_table)->size = table_size;

    for (int i = 0; i < k_count; ++i)
    {
        int rc = insert_in_hash_table(hash_table, keywords[i], help[i], k_count, table_size);


        if (rc == ERR_ALLOC)
            return ERR_ALLOC;
        else if (rc == NEED_RESTRUCT)
            return NEED_RESTRUCT;
    }

    return SUCCESS;
}