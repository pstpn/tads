#include <stdio.h>

#include "my_types.h"
#include "my_def.h"
#include "my_msgs.h"
#include "my_err.h"


// int get_in_elem(FILE *f, char *elem)
// {
//     char buf;


//     if (fscanf(f, "%c%c", elem, &buf) != 2)
//         return ERR_READING;
//     if (buf != '\n')
//         return ERR_READING;

//     return SUCCESS;
// }


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
        if (hash_table->data[i]->keyword)
        {
            fprintf(stdout, HASH_TABLE_INFO_MSG, BLUE, PURPLE, INDEX_WIDTH,
            i, RESET, BLUE, GREEN, KEYWORD_WIDTH,
            hash_table->data[i]->keyword, RESET, BLUE, RED, POINTER_WIDTH,
            (void *) hash_table->data[i], RESET);

            draw_line(TABLE_WIDTH);
        }
}


// void print_measures(measurement_table *table, int len)
// {
//     draw_line(MEAS_TABLE_WIDTH);
//     printf(MEASURE_TABLE_MSG, BLUE, RESET);
//     draw_line(MEAS_TABLE_WIDTH);

//     for (int i = 0; i < len; i += 5)
//         printf("|%*d|%*llu     / %*d |%*llu     / %*d |%*llu     / %*d |%*llu     / %*d |%*llu     / %*d |\n",
//             FIRST_FIELD_WIDTH, table[i].branching, SECOND_FIELD_WIDTH / 2, table[i].time,
//             SECOND_FIELD_WIDTH / 2, table[i].mem, SECOND_FIELD_WIDTH / 2, table[i + 1].time,
//             SECOND_FIELD_WIDTH / 2 + 1, table[i + 1].mem, SECOND_FIELD_WIDTH / 2, table[i + 2].time,
//             SECOND_FIELD_WIDTH / 2 + 1, table[i + 2].mem, SECOND_FIELD_WIDTH / 2, table[i + 3].time,
//             SECOND_FIELD_WIDTH / 2 + 1, table[i + 3].mem, SECOND_FIELD_WIDTH / 2 + 1, table[i + 4].time,
//             SECOND_FIELD_WIDTH / 2 + 1, table[i + 4].mem);
    
//     draw_line(MEAS_TABLE_WIDTH);
// }