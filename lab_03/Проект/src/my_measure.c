#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "../inc/my_operations.h"
#include "../inc/in_out.h"
#include "../inc/tools.h"
#include "../inc/w_w_mem.h"
#include "../inc/my_types.h"
#include "../inc/my_def.h"
#include "../inc/my_msgs.h"
#include "../inc/my_err.h"


unsigned long long microseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long) - 1;
    return val.tv_sec * 1000000ULL + val.tv_usec * 1ULL;
}


int get_measures(measurement_table table[])
{
    int filling[COUNT_MEAS] = { 1, 5, 10, 15, 20, 30, 50, 70, 90, 100 };
    int sizes[COUNT_SIZES] = { 5, 50, 100, 500 };

    spar_mtrx_t a_1;
    spar_mtrx_t a_2;

    a_1.a = NULL, a_2.a = NULL;
    a_1.ja = NULL, a_2.ja = NULL;
    a_1.ia = NULL, a_2.ia = NULL;

    int **p_mtrx_1 = NULL;
    int **p_mtrx_2 = NULL;
    int n_1 = 0, m_1 = 0;
    int n_2 = 0, m_2 = 0;

    int count_nonzero_1 = 0;
    int count_nonzero_2 = 0;

    long long unsigned beg, end, res, res_s;


    for (int i = 0; i < COUNT_MEAS; ++i)
        for (int j = 0; j < COUNT_SIZES; ++j)
        {
            char *f_str;


            asprintf(&f_str, "python3 generate_matrix.py m_1.txt %d %d %d m_2.txt %d %d %d",
                sizes[j], sizes[j], filling[i], sizes[j], sizes[j], filling[i]);

            printf("%s\n", f_str);
            system(f_str);

            FILE *f_1 = fopen(FIRST_FILE, "r");
            if (!f_1)
                return ERR_FILE;


            if (get_size(f_1, &n_1, &m_1))
            {
                fclose(f_1);
                return ERR_GET_SIZE;
            }

            p_mtrx_1 = allocate_matrix(n_1, m_1);
            
            if (!p_mtrx_1)
            {
                fclose(f_1);
                return ERR_ALLOC;
            }

            if (read_matrix(f_1, p_mtrx_1, n_1, m_1, &count_nonzero_1))
            {
                fclose(f_1);
                free_matrix(p_mtrx_1, 1);
                return ERR_READING;
            }

            if (allocate_spec_matrix(&a_1, n_1, count_nonzero_1))
            {
                fclose(f_1);
                free_matrix(p_mtrx_1, 1);
                return ERR_ALLOC;
            }

            a_1.count = count_nonzero_1;

            read_spec_matrix(p_mtrx_1, &a_1, n_1, m_1);

            FILE *f_2 = fopen(SECOND_FILE, "r");
            if (!f_2)
            {
                fclose(f_1);
                free_matrix(p_mtrx_1, 1);
                free_spec_matrix(&a_1);
                return ERR_FILE;
            }

            if (get_size(f_2, &n_2, &m_2))
            {
                fclose(f_1);
                fclose(f_2);
                free_matrix(p_mtrx_1, 1);
                free_spec_matrix(&a_1);
                return ERR_GET_SIZE;
            }

            p_mtrx_2 = allocate_matrix(n_2, m_2);

            if (!p_mtrx_2)
            {
                fclose(f_1);
                fclose(f_2);
                free_matrix(p_mtrx_1, 1);
                free_spec_matrix(&a_1);
                return ERR_ALLOC;
            }

            if (read_matrix(f_2, p_mtrx_2, n_2, m_2, &count_nonzero_2))
            {
                fclose(f_1);
                fclose(f_2);
                free_matrix(p_mtrx_1, 1);
                free_spec_matrix(&a_1);
                free_matrix(p_mtrx_2, 1);
                return ERR_DATA;
            }

            if (allocate_spec_matrix(&a_2, n_2, count_nonzero_2))
            {
                fclose(f_1);
                fclose(f_2);
                free_matrix(p_mtrx_1, 1);
                free_spec_matrix(&a_1);
                free_matrix(p_mtrx_2, 1);
                return ERR_ALLOC;
            }

            a_2.count = count_nonzero_2;

            read_spec_matrix(p_mtrx_2, &a_2, n_2, m_2);

            fclose(f_1);
            fclose(f_2);

            int **res_mtrx = allocate_matrix(n_1, m_1);


            if (!res_mtrx)
            {
                free_matrix(p_mtrx_1, 1);
                free_spec_matrix(&a_1);
                free_matrix(p_mtrx_2, 1);
                free_spec_matrix(&a_2);
                return ERR_ALLOC;
            }

            spar_mtrx_t res_spec_mtrx;
            res_spec_mtrx.a = NULL, res_spec_mtrx.ja = NULL, res_spec_mtrx.ia = NULL;


            if (allocate_spec_matrix(&res_spec_mtrx, n_1, a_1.count + a_2.count))
            {
                free_matrix(p_mtrx_1, 1);
                free_spec_matrix(&a_1);
                free_matrix(p_mtrx_2, 1);
                free_spec_matrix(&a_2);
                free_matrix(res_mtrx, 1);
                return ERR_ALLOC;
            }

            res = 0, res_s = 0;

            for (int k = 0; k < COUNT_MEAS; ++k)
            {
                beg = microseconds_now();
                matrix_addition(p_mtrx_1, p_mtrx_2, res_mtrx, n_1, m_1);
                end = microseconds_now();

                res += (end - beg);


                beg = microseconds_now();
                matrix_spec_addition(&a_1, &a_2, &res_spec_mtrx, n_1);
                end = microseconds_now();

                res_s += (end - beg);
            }
            
            free_matrix(p_mtrx_1, 1);
            free_spec_matrix(&a_1);
            free_matrix(p_mtrx_2, 1);
            free_spec_matrix(&a_2);
            free_matrix(res_mtrx, 1);
            free_spec_matrix(&res_spec_mtrx);

            table->mtrx_type = 'c';
            table->time = res / COUNT_MEAS;
            table->n = n_1, table->m = m_1;
            table->fill = filling[i];
            table->mem = 2 * (sizeof(int *) * n_1 + n_1 * m_1 * sizeof(int));

            table->mtrx_type = 's';
            table->time = res_s / COUNT_MEAS;
            table->n = n_1, table->m = m_1;
            table->fill = filling[i];
            table->mem = count_nonzero_1 * sizeof(int) * 2 +
                count_nonzero_2 * sizeof(int) * 2 + n_1 * sizeof(int) * 2;
        }
    
    return SUCCESS;
}