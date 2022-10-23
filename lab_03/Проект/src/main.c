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

#define SUCCESS 0
#define ERR_FILE 1
#define ERR_DATA 2
#define ERR_GET_SIZE 3
#define ERR_READING 4
#define ERR_ALLOC 5
#define ERR_CODE 6

#define FILENAME_LEN 20
#define MENU_LEN 5
#define INDENT 2
#define BIG_INDENT 5
#define MAX_P_LEN 20
#define TRUE 1
#define FALSE 0
#define FIELD_WIDTH 8

#define INFO_MSG "\n- Формат входных данных: 2 целочисленные матрицы одинакового размера, \
содержащиеся в файлах в простом виде\n\n- Операция, производимая программой: сложение матриц\n\n\
- Формат выходных данных: матрица или файл с матрицей\n\n"
#define FILE_1_INPUT_MSG "\nВведите имя входного файла с первой матрицей: "
#define FILE_2_INPUT_MSG "\nВведите имя входного файла со второй матрицей: "
#define UNKNOWN_FILE_MSG "\nУказанный файл не найден. Желаете ли Вы создать пустую матрицу? ('y' to continue): "
#define ERR_CREATE_MSG "\nНе удалось создать файл с таким именем. Попробуйте снова.\n\n"
#define ERR_OPEN_MSG "\nНе удалось открыть файл. Попробуйте снова.\n\n"
#define ERR_READING_MSG "\nНе удалось прочитать файл с данными. Попробуйте снова.\n\n"
#define ERR_ALLOC_MSG "\nНе удалось выделить память. Попробуйте снова.\n\n"
#define ERR_GET_SIZES_MSG "\nНе удалось получить корректную размерность. Попробуйте снова.\n\n"
#define ERR_CODE_MSG "\nНекорректный код. Попробуйте снова.\n\n"
#define ERR_READING_STDIN_MSG "\nНе удалось прочитать данные. Попробуйте снова.\n\n"
#define ERR_SIZES_MSG "\nРазмеры матриц не равны. Попробуйте снова.\n\n"
#define MENU_MSG  "\n\
1  --  Вывести матрицу\n\
2  --  Заполнить пустую матрицу\n\
3  --  Выполнить сложение матриц, хранящихся в виде трех векторов, и вывести\n\
4  --  Выполнить сложение матриц, применяя стандартный алгоритм работы, и вывести\n\
5  --  Сравнить время выполнения операция и объем памяти при использовании двух алгоритмов\n\
0  --  Выход\n: "
#define PRINT_MATRIX_MSG "\nВыберите матрицу для вывода:\n1 -- Первая матрица\n2 -- Вторая матрица\n: "
#define EMPTY_MATRIX_MSG "\nМатрица пустая. Заполните матрицу и попробуйте снова.\n\n"
#define FILLED_MATRIX_MSG "\nМатрица непустая.\n\n"
#define ENTER_SIZES_MSG "\nВведите размерность новой матрицы (в виде \"n m\"): "
#define FILLING_MATRIX_MSG "\nВыберите матрицу для заполнения:\n1 -- Первая матрица\n2 -- Вторая матрица\n: "
#define INPUT_ELEMS_MSG "\nВведите элементы матрицы, разделяя их пробелом:\n\n"
#define SPEC_TABLE_MSG "\n|   A   |   JA   |   IA   |\n"


typedef struct
{
    int *a;
    int *ja;
    int *ia;
    int count;
} spar_mtrx_t;


int get_size(FILE *f, int *n, int *m)
{
    char buf;


    if (fscanf(f, "%d%d%c", n, m, &buf) != 3 ||
        buf != '\n' || *n < 1 || *m < 1)
        return ERR_GET_SIZE;

    return SUCCESS;
}


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


void read_spec_matrix(int **p_mtrx, spar_mtrx_t *mtrx, int n, int m)
{
    int ind = 0;


    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (p_mtrx[i][j])
            {
                mtrx->a[ind] = p_mtrx[i][j];
                mtrx->ja[ind++] = j;
                mtrx->ia[i] = (mtrx->ia[i] == -1) ? j : mtrx->ia[i];
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
                *(++count_nonzero);
        }
    }

    return SUCCESS;
}


void matrix_addition(int **mtrx_1, int **mtrx_2, int **res_mtrx, int n, int m)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            res_mtrx[i][j] = mtrx_1[i][j] + mtrx_2[i][j];
}


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
    if (mtrx->ia < 0)
        *count = 0;
    else
    {
        *count = 1;

        if (ind_str + 1 == n)
            for (int i = prev_count + 1; i < mtrx->count; ++i)
                ++(*count);
        else
        {
            for (int i = prev_count + 1; mtrx->ja[i] != mtrx->ia[ind_str + 1]; ++i)
                ++(*count);

            if (!is_new_str(mtrx, prev_count + *count, mtrx->ia[ind_str + 1], n))
                for (int i = prev_count + *count; mtrx->ja[i] != mtrx->ia[ind_str + 1]; ++i)
                    ++(*count);
        }
    }
}


void matrix_spec_addition(spar_mtrx_t *mtrx_1, spar_mtrx_t *mtrx_2, spar_mtrx_t *res_mtrx, int n, int m)
{
    int ind = 0;
    int m_1_c, prev_1_c = 0;
    int m_2_c, prev_2_c = 0;


    for (int i = 0; i < n; ++i)
    {
        get_count_elems_in_str(mtrx_1, i, &m_1_c, prev_1_c, n);

        get_count_elems_in_str(mtrx_2, i, &m_2_c, prev_2_c, n);

        if (m_1_c && !m_2_c)
        {
            res_mtrx->ia[i] = mtrx_1->ia[i];

            for (int j = prev_1_c; j < prev_1_c + m_1_c; ++j)
            {
                res_mtrx->a[ind] = mtrx_1->a[j];
                res_mtrx->ja[ind++] = mtrx_1->ja[j];
            }
        }
        else if (!m_1_c && m_2_c)
        {
            res_mtrx->ia[i] = mtrx_2->ia[i];

            for (int j = prev_2_c; j < prev_2_c + m_2_c; ++j)
            {
                res_mtrx->a[ind] = mtrx_2->a[j];
                res_mtrx->ja[ind++] = mtrx_2->ja[j];
            }
        }
        else if (m_1_c && m_2_c)
        {
            int ind_1 = prev_1_c;
            int ind_2 = prev_2_c;


            res_mtrx->ia[i] = (mtrx_1->ia[i] < mtrx_2->ia[i]) ? mtrx_1->ia[i] : mtrx_2->ia[i];

            while (ind_1 < m_1_c && ind_2 < m_2_c)
            {
                if (mtrx_1->ja[prev_1_c + ind_1] < mtrx_2->ja[prev_2_c + ind_2])
                {
                    res_mtrx->ja[ind] = mtrx_1->ja[prev_1_c + ind_1];
                    res_mtrx->ja[ind++] = mtrx_1->a[prev_1_c + ind_1++];
                }
                else if (mtrx_1->ja[prev_1_c + ind_1] > mtrx_2->ja[prev_2_c + ind_2])
                {
                    res_mtrx->ja[ind] = mtrx_2->ja[prev_2_c + ind_2];
                    res_mtrx->ja[ind++] = mtrx_2->a[prev_2_c + ind_2++];
                }
                else
                {
                    res_mtrx->ja[ind] = mtrx_2->ja[prev_2_c + ind_2] + mtrx_1->ja[prev_1_c + ind_1++];
                    res_mtrx->ja[ind++] = mtrx_2->a[prev_2_c + ind_2++];
                }
            }
        }
        else
            res_mtrx->ia[i] = -1;

        prev_1_c += m_1_c;
        prev_2_c += m_2_c;
    }

    res_mtrx->count = ind;
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


void print_spec_matrix(spar_mtrx_t *mtrx, int n)
{
    printf(SPEC_TABLE_MSG);
    
    for (int i = 0; i < (mtrx->count < n) ? n : mtrx->count; ++i)
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
            printf("\n");
    }
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
                        printf(ENTER_SIZES_MSG);
                        if (get_size(stdin, &n_1, &m_1))
                        {
                            printf(ERR_GET_SIZES_MSG);
                            break;
                        }

                        p_mtrx_1 = allocate_matrix(n_1, m_1);
                        
                        if (!p_mtrx_1)
                        {
                            printf(ERR_ALLOC_MSG);
                            break;
                        }

                        printf(INPUT_ELEMS_MSG);

                        if (read_matrix(stdin, p_mtrx_1, n_1, m_1, &count_nonzero_1))
                        {
                            printf(ERR_READING_STDIN_MSG);
                            break;
                        }

                        if (allocate_spec_matrix(&a_1, n_1, count_nonzero_1))
                        {
                            printf(ERR_ALLOC_MSG);
                            break;
                        }

                        a_1.count = count_nonzero_1;

                        read_spec_matrix(p_mtrx_1, &a_1, n_1, m_1);
                    }
                    else
                        printf(FILLED_MATRIX_MSG);
                }
                else if (ans == '2')
                {
                    if (!n_2)
                    {
                        printf(ENTER_SIZES_MSG);
                        if (get_size(stdin, &n_2, &m_2))
                        {
                            printf(ERR_GET_SIZES_MSG);
                            break;
                        }

                        p_mtrx_2 = allocate_matrix(n_2, m_2);
                        
                        if (!p_mtrx_2)
                        {
                            printf(ERR_ALLOC_MSG);
                            break;
                        }

                        printf(INPUT_ELEMS_MSG);

                        if (read_matrix(stdin, p_mtrx_2, n_2, m_2, &count_nonzero_2))
                        {
                            printf(ERR_READING_STDIN_MSG);
                            break;
                        }

                        if (allocate_spec_matrix(&a_2, n_2, count_nonzero_2))
                        {
                            printf(ERR_ALLOC_MSG);
                            break;
                        }

                        a_2.count = count_nonzero_2;

                        read_spec_matrix(p_mtrx_2, &a_2, n_2, m_2);                                                
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

                matrix_spec_addition(&a_1, &a_2, &res_spec_mtrx, n_1, m_1);

                print_spec_matrix(&res_spec_mtrx, n_1);

                free_spec_matrix(&res_spec_mtrx);
                
                break;
            }
            case 5:
            {
                break;
            }
        }
    }
    
    return SUCCESS;
}
