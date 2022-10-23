#include <stdlib.h>

#include "../inc/my_types.h"
#include "../inc/my_err.h"


int allocate_spec_matrix(spar_mtrx_t *mtrx, int n, int count_nonzero)
{
    mtrx->a = calloc(count_nonzero, sizeof(int));
    if (!mtrx->a)
        return ERR_ALLOC;

    mtrx->ja = calloc(count_nonzero, sizeof(int));

    if (!mtrx->ja)
    {
        free(mtrx->a);
        return ERR_ALLOC;
    }

    mtrx->ia = calloc(n, sizeof(int));

    if (!mtrx->ia)
    {
        free(mtrx->a);
        free(mtrx->ja);
        return ERR_ALLOC;
    }

    for (int i = 0; i < n; ++i)
        mtrx->ia[i] = -1;

    return SUCCESS;
}


int **allocate_matrix(int n, int m)
{
    int **p_mtrx, *mtrx;


    p_mtrx = calloc(n, sizeof(int *));
    if (!p_mtrx)
        return NULL;

    mtrx = calloc(n * m, sizeof(int));

    if (!mtrx)
    {
        free(p_mtrx);
        return NULL;
    }

    for (int i = 0; i < n; i++)
        p_mtrx[i] = mtrx + i * m;

    return p_mtrx;
}


void free_matrix(int **data, int n)
{
    for (int i = 0; i < n; i++)
        free(data[i]);

    free(data);
}


void free_spec_matrix(spar_mtrx_t *mtrx)
{
    free(mtrx->a);
    free(mtrx->ja);
    free(mtrx->ia);
}