#include "../inc/my_types.h"
#include "../inc/my_def.h"


void get_count_elems_in_str(spar_mtrx_t *mtrx, int ind_str, int *count, int prev, int n)
{
    if (mtrx->ia[ind_str] < 0)
        *count = 0;
    else
    {
        *count = 1;

        if (ind_str + 1 == n)
            for (int i = mtrx->ia[ind_str] + 1; i < mtrx->count; ++i)
                ++(*count);
        else
        {
            int add = 1;


            while (add + ind_str < n && mtrx->ia[ind_str + add] == -1)
                ++add;

            if (add + ind_str == n && mtrx->ia[ind_str + add - 1] == -1)
                *count = mtrx->count - prev;
            else
                for (int i = mtrx->ia[ind_str] + 1; add + ind_str < n &&
                    i != mtrx->ia[ind_str + add]; ++i)
                    ++(*count);
        }
    }
}