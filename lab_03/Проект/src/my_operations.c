#include "../inc/my_types.h"
#include "../inc/tools.h"

#include <stdio.h>


void matrix_addition(int **mtrx_1, int **mtrx_2, int **res_mtrx, int n, int m)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            res_mtrx[i][j] = mtrx_1[i][j] + mtrx_2[i][j];
}


void matrix_spec_addition(spar_mtrx_t *mtrx_1, spar_mtrx_t *mtrx_2, spar_mtrx_t *res_mtrx, int n)
{
    int ind = 0;
    int m_1_c;
    int m_2_c;


    for (int i = 0; i < n; ++i)
    {
        get_count_elems_in_str(mtrx_1, i, &m_1_c, res_mtrx->count, n);

        get_count_elems_in_str(mtrx_2, i, &m_2_c, res_mtrx->count, n);

        if (m_1_c && !m_2_c)
        {
            res_mtrx->ia[i] = ind;

            for (int j = mtrx_1->ia[i]; j < mtrx_1->ia[i] + m_1_c; ++j)
            {
                res_mtrx->a[ind] = mtrx_1->a[j];
                res_mtrx->ja[ind++] = mtrx_1->ja[j];
            }
        }
        else if (!m_1_c && m_2_c)
        {
            res_mtrx->ia[i] = ind;

            for (int j = mtrx_2->ia[i]; j < mtrx_1->ia[i] + m_2_c; ++j)
            {
                res_mtrx->a[ind] = mtrx_2->a[j];
                res_mtrx->ja[ind++] = mtrx_2->ja[j];
            }
        }
        else if (m_1_c && m_2_c)
        {
            int ind_1 = mtrx_1->ia[i];
            int ind_2 = mtrx_2->ia[i];


            res_mtrx->ia[i] = ind;

            while (ind_1 < m_1_c + mtrx_1->ia[i] || ind_2 < m_2_c + mtrx_2->ia[i])
            {
                if (ind_2 >= m_2_c + mtrx_2->ia[i] ||
                    (mtrx_1->ja[ind_1] < mtrx_2->ja[ind_2] &&
                    ind_1 < m_1_c + mtrx_1->ia[i] && ind_2 < m_2_c + mtrx_2->ia[i]))
                {
                    res_mtrx->ja[ind] = mtrx_1->ja[ind_1];
                    res_mtrx->a[ind++] = mtrx_1->a[ind_1++];
                }
                else if (ind_1 >= m_1_c + mtrx_1->ia[i] ||
                    (mtrx_1->ja[ind_1] > mtrx_2->ja[ind_2] &&
                    ind_1 < m_1_c + mtrx_1->ia[i] && ind_2 < m_2_c + mtrx_2->ia[i]))
                {
                    res_mtrx->ja[ind] = mtrx_2->ja[ind_2];
                    res_mtrx->a[ind++] = mtrx_2->a[ind_2++];
                }
                else
                {
                    res_mtrx->ja[ind] = mtrx_2->ja[ind_2];
                    res_mtrx->a[ind++] = mtrx_2->a[ind_2++] + mtrx_1->a[ind_1++];
                }
            }
        }
        else
            res_mtrx->ia[i] = -1;
    }

    res_mtrx->count = ind;
}