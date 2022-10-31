/**
 * @file main.c
 * @author Stepan Postnov ICS7-31B
 * @brief 
 * 
 *                     TASK:
 * 
 *                    Вариант 1
 * 
 * Разреженная (содержащая много нулей) матрица хранится в форме 3-х объектов:
 * 
 * - вектор A содержит значения ненулевых элементов;
 * - вектор JA содержит номера столбцов для элементов вектора A;
 * - связный список IA, в элементе Nk которого находится номер компонент
 * в A и JA, с которых начинается описание строки Nk матрицы A.
 * 
 * 1. Смоделировать операцию сложения двух матриц, хранящихся в этой форме,
 * с получением результата в той же форме.
 * 2. Произвести операцию сложения, применяя стандартный алгоритм работы с
 * матрицами.
 * 3. Сравнить время выполнения операций и объем памяти при использовании
 * этих 2-х алгоритмов при различном проценте заполнения матриц.
 * 
 * @version 0.1
 * @date 2022-10-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>

#include "../inc/my_measure.h"
#include "../inc/w_w_mem.h"
#include "../inc/my_operations.h"
#include "../inc/my_types.h"
#include "../inc/my_def.h"
#include "../inc/my_err.h"
#include "../inc/my_msgs.h"
#include "../inc/in_out.h"


int main(void)
{
    int key = -1;

    char filename_1[FILENAME_LEN + 1] = { 0 };
    char filename_2[FILENAME_LEN + 1] = { 0 };

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


    printf(INFO_MSG);
    printf(FILE_1_INPUT_MSG);
    fscanf(stdin, "%s", filename_1);

    FILE *f_1 = fopen(filename_1, "r+");

    char ans;


    if (f_1 == NULL)
    {
        printf(UNKNOWN_FILE_MSG);

        fscanf(stdin, "\n%c", &ans);
        if (ans != 'y')
        {
            printf(ERR_OPEN_MSG);
            return ERR_FILE;
        }
        printf("\n");
    }
    else
    {
        if (get_size(f_1, &n_1, &m_1))
        {
            printf(ERR_READING_MSG);
            fclose(f_1);
            return ERR_DATA;
        }

        p_mtrx_1 = allocate_matrix(n_1, m_1);

        if (!p_mtrx_1)
        {
            printf(ERR_ALLOC_MSG);
            fclose(f_1);
            return ERR_ALLOC;
        }

        if (read_matrix(f_1, p_mtrx_1, n_1, m_1, &count_nonzero_1))
        {
            printf(ERR_READING_MSG);
            fclose(f_1);
            free_matrix(p_mtrx_1, 1);
            return ERR_DATA;
        }

        if (allocate_spec_matrix(&a_1, n_1, count_nonzero_1))
        {
            printf(ERR_ALLOC_MSG);
            fclose(f_1);
            free_matrix(p_mtrx_1, 1);
            return ERR_ALLOC;
        }

        a_1.count = count_nonzero_1;

        read_spec_matrix(p_mtrx_1, &a_1, n_1, m_1);
    }
    
    printf(FILE_2_INPUT_MSG);
    fscanf(stdin, "%s", filename_2);

    FILE *f_2 = fopen(filename_2, "r+");


    if (f_2 == NULL)
    {
        printf(UNKNOWN_FILE_MSG);

        fscanf(stdin, "\n%c", &ans);
        if (ans != 'y')
        {
            printf(ERR_OPEN_MSG);
            return ERR_FILE;
        }
        printf("\n");
    }
    else
    {
        if (get_size(f_2, &n_2, &m_2))
        {
            printf(ERR_READING_MSG);
            fclose(f_1);
            fclose(f_2);
            free_spec_matrix(&a_1);
            free_matrix(p_mtrx_1, 1);
            return ERR_DATA;
        }

        p_mtrx_2 = allocate_matrix(n_2, m_2);

        if (!p_mtrx_2)
        {
            printf(ERR_ALLOC_MSG);
            fclose(f_1);
            fclose(f_2);
            free_spec_matrix(&a_1);
            free_matrix(p_mtrx_1, 1);
            return ERR_ALLOC;
        }

        if (read_matrix(f_2, p_mtrx_2, n_2, m_2, &count_nonzero_2))
        {
            printf(ERR_READING_MSG);
            fclose(f_1);
            fclose(f_2);
            free_spec_matrix(&a_1);
            free_matrix(p_mtrx_1, 1);
            free_matrix(p_mtrx_2, 1);
            return ERR_DATA;
        }

        if (allocate_spec_matrix(&a_2, n_2, count_nonzero_2))
        {
            printf(ERR_ALLOC_MSG);
            fclose(f_1);
            fclose(f_2);
            free_spec_matrix(&a_1);
            free_matrix(p_mtrx_1, 1);
            free_matrix(p_mtrx_2, 1);
            return ERR_ALLOC;
        }

        a_2.count = count_nonzero_2;

        read_spec_matrix(p_mtrx_2, &a_2, n_2, m_2);
    }

    if (f_1)
        fclose(f_1);
    if (f_2)
        fclose(f_2);
    
    while (key != 0)
    {
        printf(MENU_MSG);

        if (fscanf(stdin, "%d", &key) != 1 ||
        key < 0 || key > MENU_LEN)
        {
            printf(ERR_CODE_MSG);
            free_spec_matrix(&a_1);
            free_spec_matrix(&a_2);
            if (p_mtrx_1)
                free_matrix(p_mtrx_1, 1);
            if (p_mtrx_2)
                free_matrix(p_mtrx_2, 1);
            return ERR_CODE;
        }

        switch (key)
        {
            case 0:
            {
                free_spec_matrix(&a_1);
                free_spec_matrix(&a_2);
                if (p_mtrx_1)
                    free_matrix(p_mtrx_1, 1);
                if (p_mtrx_2)
                    free_matrix(p_mtrx_2, 1);
                return SUCCESS;
            }
            case 1:
            {
                printf(PRINT_MATRIX_MSG);
                fscanf(stdin, "\n%c", &ans);
                if (ans == '1')
                {
                    if (!n_1)
                        printf(EMPTY_MATRIX_MSG);
                    else
                        print_matrix(p_mtrx_1, n_1, m_1);
                }
                else if (ans == '2')
                {
                    if (!n_2)
                        printf(EMPTY_MATRIX_MSG);
                    else
                        print_matrix(p_mtrx_2, n_2, m_2);
                }
                else
                    printf(ERR_CODE_MSG);
                
                printf("\n");
                
                break;
            }
            case 2:
            {                
                printf(FILLING_MATRIX_MSG);
                fscanf(stdin, "\n%c", &ans);
                if (ans == '1')
                {
                    if (!n_1)
                    {
                        printf(ENTER_TYPE_INPUT_MSG);
                        fscanf(stdin, "\n%c", &ans);
                        if (ans == '1')
                        {
                            printf(ENTER_SIZES_MSG);
                            if (get_size(stdin, &n_1, &m_1))
                            {
                                printf(ERR_GET_SIZES_MSG);
                                return ERR_GET_SIZE;
                            }

                            if (n_2 && m_2 && (n_1 != n_2 || m_1 != m_2))
                            {
                                printf(ERR_GET_SIZES_MSG);
                                return ERR_GET_SIZE;
                            }

                            p_mtrx_1 = allocate_matrix(n_1, m_1);
                            
                            if (!p_mtrx_1)
                            {
                                printf(ERR_ALLOC_MSG);
                                return ERR_ALLOC;
                            }

                            printf(INPUT_ELEMS_MSG);

                            if (read_matrix(stdin, p_mtrx_1, n_1, m_1, &count_nonzero_1))
                            {
                                printf(ERR_READING_STDIN_MSG);
                                return ERR_DATA;
                            }

                            if (allocate_spec_matrix(&a_1, n_1, count_nonzero_1))
                            {
                                printf(ERR_ALLOC_MSG);
                                return ERR_ALLOC;
                            }

                            a_1.count = count_nonzero_1;

                            read_spec_matrix(p_mtrx_1, &a_1, n_1, m_1);
                        }
                        else if (ans == '2')
                        {
                            printf(ENTER_SIZES_MSG);
                            if (get_size(stdin, &n_1, &m_1))
                            {
                                printf(ERR_GET_SIZES_MSG);
                                return ERR_GET_SIZE;
                            }

                            if (n_1 && m_1 && (n_1 != n_2 || m_1 != m_2))
                            {
                                printf(ERR_GET_SIZES_MSG);
                                return ERR_GET_SIZE;
                            }

                            p_mtrx_1 = allocate_matrix(n_1, m_1);
                            
                            if (!p_mtrx_1)
                            {
                                printf(ERR_ALLOC_MSG);
                                return ERR_ALLOC;
                            }

                            if (coord_read_matrix(stdin, p_mtrx_1, n_1, m_1, &count_nonzero_1))
                            {
                                printf(ERR_READING_STDIN_MSG);
                                return ERR_DATA;
                            }

                            if (allocate_spec_matrix(&a_1, n_1, count_nonzero_1))
                            {
                                printf(ERR_ALLOC_MSG);
                                return ERR_ALLOC;
                            }

                            a_1.count = count_nonzero_1;

                            read_spec_matrix(p_mtrx_1, &a_1, n_1, m_1);  
                        }
                        else
                            printf(ERR_CODE_MSG);
                    }
                    else
                        printf(FILLED_MATRIX_MSG);
                }
                else if (ans == '2')
                {
                    if (!n_2)
                    {
                        printf(ENTER_TYPE_INPUT_MSG);
                        fscanf(stdin, "\n%c", &ans);
                        if (ans == '1')
                        {
                            printf(ENTER_SIZES_MSG);
                            if (get_size(stdin, &n_2, &m_2))
                            {
                                printf(ERR_GET_SIZES_MSG);
                                return ERR_GET_SIZE;
                            }

                            p_mtrx_2 = allocate_matrix(n_2, m_2);
                            
                            if (!p_mtrx_2)
                            {
                                printf(ERR_ALLOC_MSG);
                                return ERR_ALLOC;
                            }

                            printf(INPUT_ELEMS_MSG);

                            if (read_matrix(stdin, p_mtrx_2, n_2, m_2, &count_nonzero_2))
                            {
                                printf(ERR_READING_STDIN_MSG);
                                return ERR_DATA;
                            }

                            if (allocate_spec_matrix(&a_2, n_2, count_nonzero_2))
                            {
                                printf(ERR_ALLOC_MSG);
                                return ERR_ALLOC;
                            }

                            a_2.count = count_nonzero_2;

                            read_spec_matrix(p_mtrx_2, &a_2, n_2, m_2);                                                
                        }
                        else if (ans == '2')
                        {
                            printf(ENTER_SIZES_MSG);
                            if (get_size(stdin, &n_2, &m_2))
                            {
                                printf(ERR_GET_SIZES_MSG);
                                return ERR_GET_SIZE;
                            }

                            p_mtrx_2 = allocate_matrix(n_2, m_2);
                            
                            if (!p_mtrx_2)
                            {
                                printf(ERR_ALLOC_MSG);
                                return ERR_ALLOC;
                            }

                            if (coord_read_matrix(stdin, p_mtrx_2, n_2, m_2, &count_nonzero_2))
                            {
                                printf(ERR_READING_STDIN_MSG);
                                return ERR_DATA;
                            }

                            if (allocate_spec_matrix(&a_2, n_2, count_nonzero_2))
                            {
                                printf(ERR_ALLOC_MSG);
                                return ERR_ALLOC;
                            }

                            a_2.count = count_nonzero_2;

                            read_spec_matrix(p_mtrx_2, &a_2, n_2, m_2);  
                        }
                        else
                            printf(ERR_CODE_MSG);
                    }
                    else
                        printf(FILLED_MATRIX_MSG);
                    }
                else
                    printf(ERR_CODE_MSG);
                    
                printf("\n");
                
                break;
            }
            case 3:
            {
                if (!n_1 || !n_2 || !m_1 || !m_2)
                {
                    printf(EMPTY_MATRIX_MSG);
                    break;
                }
                
                if (n_1 != n_2 || m_1 != m_2)
                {
                    printf(ERR_SIZES_MSG);
                    break;
                }

                int **res_mtrx = allocate_matrix(n_1, m_1);


                if (!res_mtrx)
                {
                    printf(ERR_ALLOC_MSG);
                    break;
                }

                matrix_addition(p_mtrx_1, p_mtrx_2, res_mtrx, n_1, m_1);

                print_matrix(res_mtrx, n_1, m_1);

                free_matrix(res_mtrx, 1);
                
                break;
            }
            case 4:
            {
                if (!n_1 || !n_2 || !m_1 || !m_2)
                {
                    printf(EMPTY_MATRIX_MSG);
                    break;
                }
                
                if (n_1 != n_2 || m_1 != m_2)
                {
                    printf(ERR_SIZES_MSG);
                    break;
                }

                spar_mtrx_t res_spec_mtrx;
                res_spec_mtrx.a = NULL, res_spec_mtrx.ja = NULL, res_spec_mtrx.ia = NULL;


                if (allocate_spec_matrix(&res_spec_mtrx, n_1, a_1.count + a_2.count))
                {
                    printf(ERR_ALLOC_MSG);
                    break;
                }

                matrix_spec_addition(&a_1, &a_2, &res_spec_mtrx, n_1);

                print_spec_matrix(&res_spec_mtrx, n_1);

                free_spec_matrix(&res_spec_mtrx);
                
                break;
            }
            case 5:
            {
                measurement_table measures[MEAS_LEN] = { 0 };


                if (get_measures(measures))
                {
                    printf(ERR_MEASURES_MSG);
                    break;
                }

                print_measures(measures, MEAS_LEN);

                break;
            }
        }
    }
    
    return SUCCESS;
}
