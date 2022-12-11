#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "my_types.h"
#include "my_def.h"
#include "my_msgs.h"
#include "my_err.h"


int get_in_elem(FILE *f, char **word, int max_len)
{
    size_t init_size = max_len + 1;

    int count = getline(word, &init_size, f);
    if ((*word)[strlen(*word) - 1] == '\n')
        (*word)[strlen(*word) - 1] = '\0';

    if (count < 0 || count - 1 > max_len)
    {
        free(*word);
        return ERR_READING;
    }

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


void print_hash_table(hash_table_t *hash_table)
{
    draw_line(TABLE_WIDTH);

    for (int i = 0; i < hash_table->size; ++i)
        if (((keyword_info_t **) hash_table->data)[i]->keyword)
        {
            fprintf(stdout, HASH_TABLE_INFO_MSG, BLUE, PURPLE, INDEX_WIDTH,
            i, RESET, BLUE, GREEN, KEYWORD_WIDTH,
            ((keyword_info_t **) hash_table->data)[i]->keyword, RESET, BLUE, RED, POINTER_WIDTH,
            (void *) ((keyword_info_t **) hash_table->data)[i], RESET);

            draw_line(TABLE_WIDTH);
        }
}


void print_list_hash_table(hash_table_t *hash_table)
{
    draw_line(TABLE_WIDTH);

    for (int i = 0; i < hash_table->size; ++i)
    {
        list_keyword_info_t *cur_keyword = ((list_keyword_info_t **) hash_table->data)[i];


        if (cur_keyword)
        {
            fprintf(stdout, HASH_TABLE_INFO_MSG, BLUE, PURPLE, INDEX_WIDTH,
            i, RESET, BLUE, GREEN, KEYWORD_WIDTH,
            cur_keyword->keyword, RESET, BLUE, RED, POINTER_WIDTH,
            (void *) cur_keyword, RESET);

            draw_line(TABLE_WIDTH);

            cur_keyword =  cur_keyword->next;
        }

        while (cur_keyword)
        {
            fprintf(stdout, CHILDS_HASH_TABLE_INFO_MSG, BLUE, PURPLE, INDEX_WIDTH - 7,
            i, RESET, BLUE, GREEN, KEYWORD_WIDTH,
            cur_keyword->keyword, RESET, BLUE, RED, POINTER_WIDTH,
            (void *) cur_keyword, RESET);

            draw_line(TABLE_WIDTH);
            cur_keyword = cur_keyword->next;
        }
    }
}


void print_measures(measurement_table *table, int len)
{
    draw_line(MEAS_TABLE_WIDTH);
    printf(MEASURE_TABLE_MSG, BLUE, RESET);
    draw_line(MEAS_TABLE_WIDTH);

    for (int i = 0; i < len; i += 3)
        printf("|%*c|%*llu     / %*d |%*llu     / %*d |%*llu     / %*d |\n",
            FIRST_FIELD_WIDTH, table[i].type, SECOND_FIELD_WIDTH / 2, table[i].time,
            SECOND_FIELD_WIDTH / 2, table[i].mem, SECOND_FIELD_WIDTH / 2, table[i + 1].time,
            SECOND_FIELD_WIDTH / 2, table[i + 1].mem, SECOND_FIELD_WIDTH / 2, table[i + 2].time,
            SECOND_FIELD_WIDTH / 2, table[i + 2].mem);
    
    draw_line(MEAS_TABLE_WIDTH);
}