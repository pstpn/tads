#include <stdio.h>
#include <stdlib.h>


int **allocate_matrix(int n, int m)
{
    int **ptrs, *data;


    ptrs = calloc(n, sizeof(int *));
    if (!ptrs)
        return NULL;

    data = calloc(n * m, sizeof(int));

    if (!data)
    {
        free(ptrs);
        return NULL;
    }

    for (int i = 0; i < n; i++)
        ptrs[i] = data + i * m;

    return ptrs;
}


void free_matrix(int **data, int n)
{
    for (int i = 0; i < n; i++)
        free(data[i]);

    free(data);
}