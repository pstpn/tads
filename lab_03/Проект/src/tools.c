#include "../inc/my_types.h"
#include "../inc/my_def.h"


int is_new_str(spar_mtrx_t *mtrx, int ind, int ind_str, int n)
{
    int ja_c = 1;
    int ia_c = 1;


    for (int i = ind + 1; i < mtrx->count; ++i)
    {
        if (mtrx->ja[i] == mtrx->ja[ind])
            ++ja_c;
        else
            break;
    }

    for (int i = ind_str + 1; i < n; ++i)
    {
        if (mtrx->ia[i] == mtrx->ia[ind_str])
            ++ia_c;
        else
            break;
    }

    return (ja_c > ia_c) ? FALSE : TRUE;
}


void get_count_elems_in_str(spar_mtrx_t *mtrx, int ind_str, int *count, int prev_count, int n)
{
    if (mtrx->ia[ind_str] < 0)
        *count = 0;
    else
    {
        *count = 1;

        if (ind_str + 1 == n)
            for (int i = prev_count + 1; i < mtrx->count; ++i)
                ++(*count);
        else
        {
            int add = 1;


            while (add + ind_str < n && mtrx->ia[ind_str + add] == -1)
                ++add;

            for (int i = prev_count + 1; add + ind_str < n &&
                mtrx->ja[i] != mtrx->ia[ind_str + add]; ++i)
                ++(*count);

            if (!(add + ind_str == n - 1) &&
                !is_new_str(mtrx, prev_count + *count, ind_str + add, n))
                for (int i = prev_count + *count; mtrx->ja[i] != mtrx->ia[ind_str + add]; ++i)
                    ++(*count);
        }
    }
}