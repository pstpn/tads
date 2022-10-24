#include <stdio.h>

#include "../inc/my_types.h"
#include "../inc/my_err.h"
#include "../inc/my_def.h"
#include "../inc/my_msgs.h"


int get_size(FILE *f, int *n, int *m)
{
    char buf;


    if (fscanf(f, "%d%d%c", n, m, &buf) != 3 ||
        buf != '\n' || *n < 1 || *m < 1)
        return ERR_GET_SIZE;

    return SUCCESS;
}


void read_spec_matrix(int **p_mtrx, spar_mtrx_t *mtrx, int n, int m)
{
    int ind = 0;


    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (p_mtrx[i][j])
            {
                mtrx->a[ind] = p_mtrx[i][j];
                mtrx->ja[ind] = j;
                mtrx->ia[i] = (mtrx->ia[i] == -1) ? ind : mtrx->ia[i];
                ++ind;
            }
}


int read_matrix(FILE *f, int **p_mtrx, int n, int m, int *count_nonzero)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (fscanf(f, "%d", &(p_mtrx[i][j])) != 1)
                return ERR_READING;

            if (p_mtrx[i][j])
                ++(*count_nonzero);
        }
    }

    return SUCCESS;
}


void print_matrix(int **p_mtrx, int n, int m)
{
    printf("\n");

    for (int i = 0; i < n; ++i)
    {
        if (!(n > MAX_P_LEN || m > MAX_P_LEN))
            printf("%*d:", INDENT, i + 1);

        for (int j = 0; j < m; ++j)
            (n > MAX_P_LEN || m > MAX_P_LEN) ? printf("%-*d %-*d: %d\n",\
                BIG_INDENT, i + 1, BIG_INDENT, j + 1, p_mtrx[i][j]) :
                printf("%*d|", BIG_INDENT + 2, p_mtrx[i][j]);

        if (!(n > MAX_P_LEN || m > MAX_P_LEN))
            printf("\n");
    }
}


void draw_line(int len)
{
    for (int i = 0; i < len; ++i)
        printf("-");
    printf("\n");
}


void print_spec_matrix(spar_mtrx_t *mtrx, int n)
{
    draw_line(OUT_TABLE_WIDTH);
    printf(SPEC_TABLE_MSG);
    draw_line(OUT_TABLE_WIDTH);

    int max = (mtrx->count < n) ? n : mtrx->count;
    

    for (int i = 0; i < max; ++i)
    {
        if (i < mtrx->count)
            printf("|%*d|%*d|", FIELD_WIDTH - 1, mtrx->a[i], FIELD_WIDTH,
                mtrx->ja[i]);
        if (i < n && i >= mtrx->count)
            printf("|%*c|%*c|%*d|\n", FIELD_WIDTH - 1, ' ',
                FIELD_WIDTH, ' ', FIELD_WIDTH, mtrx->ia[i]);
        else if (i < n)
            printf("%*d|\n", FIELD_WIDTH, mtrx->ia[i]);
        else
            printf("%*c|\n", FIELD_WIDTH, ' ');
    }
    draw_line(OUT_TABLE_WIDTH);
}


void print_measures(measurement_table table[], int count)
{
    draw_line(MEAS_TABLE_WIDTH);
    printf(MEASURE_TABLE_MSG);
    draw_line(MEAS_TABLE_WIDTH);

    for (int i = 0; i < count; ++i)
        printf("|%-*s|%-*d|%-*d|%-*d|%-*lld|\n", TYPE_LEN,
            (table[i].mtrx_type == 'c') ? COMMON_TYPE : SPEC_TYPE,
            SIZE_LEN, table[i].m * table[i].n, FILL_LEN, table[i].fill,
            MEMORY_LEN, table[i].mem, TIME_LEN, table[i].time);
    
    draw_line(MEAS_TABLE_WIDTH);
}