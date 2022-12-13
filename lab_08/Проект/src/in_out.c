#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "my_err.h"


int get_size(FILE *f, int *n, int *m)
{
    char buf;


    if (fscanf(f, "%d%d%c", n, m, &buf) != 3 ||
        buf != '\n' || *n < 1 || *m < 1)
        return ERR_READING;

    return SUCCESS;
}


int get_in_file(FILE *f, char **word, int max_len)
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


int filling_matrix(FILE *f, int **ptrs, int n, int m)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            if (fscanf(f, "%d", &(ptrs[i][j])) != 1)
                return ERR_READING;
    }
    
    if ((feof(f) == 0 && fgetc(f) != '\n'))
        return ERR_READING;

    return SUCCESS;
}


void export_to_dot(FILE *f, const char *graph_name, int **graph_mtrx, int n, int m)
{
    fprintf(f, "graph %s {\n", graph_name);
    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m && j < i; ++j)
            if (graph_mtrx[i][j])
                fprintf(f, "%d -- %d;\n", i, j);

    fprintf(f, "}\n");
}
