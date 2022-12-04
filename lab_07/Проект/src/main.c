/*

Построить хеш-таблицу для зарезервированных слов языка С++ (не
менее 20 слов), содержащую HELP для каждого слова. Выдать на экран
подсказку по введенному слову. Выполнить программу для различных
размерностей таблицы и сравнить время поиска и количество сравнений. Для
указанных данных создать сбалансированное дерево. Добавить подсказку по
вновь введенному слову, используя при необходимости реструктуризацию
таблицы. Сравнить эффективность добавления ключа в таблицу или ее
реструктуризацию для различной степени заполненности таблицы.


*/
#include <stdio.h>
#include <stdlib.h>

#include "my_types.h"
#include "my_def.h"
#include "my_msgs.h"
#include "my_err.h"
#include "balance_tree_funcs.h"
#include "graph.h"


int main(void)
{
    char CPP_KEYWORDS[KEYWORDS_COUNT][MAX_KEYWORD_LEN + 1] = 
        { "case", "bool", "break", "char", "continue", "delete",
        "default", "do", "else", "enum", "export", "extern",
        "true", "false", "for", "goto", "if", "static",
        "or", "typedef" };

    int key = -1;

    balance_tree_node_t *root_node = create_keywords_balance_tree(CPP_KEYWORDS, KEYWORDS_COUNT);
    if (!root_node)
    {
        printf(ERR_ALLOC_MSG, RED, RESET);
        return ERR_ALLOC;
    }


    printf(INFO_MSG);
    
    while (key != 0)
    {
        printf(MENU_MSG);

        if (fscanf(stdin, "%d", &key) != 1 ||
        key < 0 || key > MENU_LEN)
        {
            printf(ERR_CODE_MSG, RED, RESET);
            apply(root_node, destroy_node, NULL, FALSE);
            return ERR_CODE;
        }

        switch (key)
        {
            case 0:
            {
                apply(root_node, destroy_node, NULL, FALSE);
                return SUCCESS;
            }
            case 1:
            {
                FILE *f = fopen(TREE_GRAPH_FILENAME, "w");
                

                export_to_dot(f, TREE_NAME, root_node, FALSE);

                fclose(f);

                system(MAKE_TREE_GRAPH_COMMAND);

                system(OPEN_TREE_PNG_COMMAND);

                break;
            }
            case 2:
            {
                // int type;
                
                // char buf;


                // printf(INPUT_DETOUR_TYPE_MSG);
                // if (fscanf(stdin, "%d%c", &type, &buf) != 2 || buf != '\n')
                // {
                //     printf(ERR_READING_STDIN_MSG, RED, RESET);
                //     clear_buf(stdin);
                //     break;
                // }
                // if (type < 1 || type > 3)
                // {
                //     printf(ERR_READING_STDIN_MSG, RED, RESET);
                //     break;
                // }

                // if (type == 1)
                //     apply(root_node, print_tree_node_info, stdout, TRUE, FALSE);
                // if (type == 2)
                //     inf_apply(root_node, print_tree_node_info, stdout);
                // if (type == 3)
                //     apply(root_node, print_tree_node_info, stdout, FALSE, FALSE);

                break;
            }
            case 3:
            {
                // clear_buf(stdin);

                // char elem;


                // printf(INPUT_ELEM_MSG);

                // if (get_in_elem(stdin, &elem))
                // {
                //     printf(ERR_READING_STDIN_MSG, RED, RESET);
                //     clear_buf(stdin);
                //     break;
                // }
                
                // tree_node_t *new_node = create_node(count++, elem);
                // if (!new_node)
                // {
                //     printf(ERR_ALLOC_MSG, RED, RESET);
                //     apply(root_node, destroy_node, NULL, FALSE, FALSE);
                //     return ERR_ALLOC;
                // }

                // root_node = insert(root_node, new_node);

                // printf(SUCCESSFULLY_ADD_MSG, GREEN, RESET);

                break;
            }
            case 4:
            {
                // if (!root_node)
                //     printf(EMPTY_TREE_MSG, RED, RESET);
                // else
                // {
                //     int del_index;


                //     printf(INPUT_DEL_INDEX_MSG);
                //     if (fscanf(stdin, "%d", &del_index) != 1 || del_index < 0)
                //     {
                //         printf(ERR_READING_STDIN_MSG, RED, RESET);
                //         clear_buf(stdin);
                //         break;
                //     }

                //     root_node = del_tree_node(root_node, &del_index);

                //     if (del_index > 0)
                //         printf(ELEM_NOT_FOUND_MSG, RED, RESET);
                //     else
                //         printf(DEL_ELEM_MSG, GREEN, RESET);
                // }

                break;
            }
            case 5:
            {
                // if (!root_node)
                //     printf(EMPTY_TREE_MSG, RED, RESET);
                // else
                // {
                //     int f_index;


                //     printf(INPUT_FIND_INDEX_MSG);
                //     if (fscanf(stdin, "%d", &f_index) != 1 || f_index < 0)
                //     {
                //         printf(ERR_READING_STDIN_MSG, RED, RESET);
                //         clear_buf(stdin);
                //         break;
                //     }

                //     tree_node_t *f_tree_node = find_tree_node(root_node, &f_index);


                //     if (f_index > 0)
                //         printf(ELEM_NOT_FOUND_MSG, RED, RESET);
                //     else
                //         print_tree_node_info((void *) f_tree_node, stdout);
                // }

                break;
            }
            case 6:
            {
                // int count;

                // char buf;


                // printf(INPUT_FILE_TREE_NODES_COUNT_MSG);
                // if (fscanf(stdin, "%d%c", &count, &buf) != 2 || buf != '\n'
                // || count < 1)
                // {
                //     printf(ERR_FILE_TREE_NODES_COUNT_MSG, RED, RESET);
                //     clear_buf(stdin);
                //     break;
                // }

                // file_tree_node_t *root_file_node = generate_file_tree(count);
                // if (!root_file_node)
                // {
                //     printf(ERR_ALLOC_MSG, RED, RESET);
                //     apply(root_node, destroy_node, NULL, FALSE, FALSE);
                //     return ERR_ALLOC;
                // }

                // FILE *f = fopen(IN_FILE_TREE_GRAPH_FILENAME, "w");
                

                // export_to_dot(f, IN_FILE_TREE_NAME, root_file_node, TRUE);

                // fclose(f);

                // system(MAKE_IN_FILE_TREE_GRAPH_COMMAND);

                // system(OPEN_IN_FILE_TREE_PNG_COMMAND);

                // int del_num, del_month, del_year;


                // printf(INPUT_DATE_FILE_TREE_MSG);
                // if (fscanf(stdin, "%d.%d.%d", &del_num, &del_month, &del_year) != 3 ||
                //     del_num < 1 || del_month < 1 || del_month > 12 || del_year < 1 ||
                //     del_num > 31)
                // {
                //     printf(ERR_GET_DATE_MSG, RED, RESET);
                //     clear_buf(stdin);
                //     break;
                // }

                // root_file_node = del_file_tree_nodes(root_file_node, del_num, del_month, del_year);            

                // FILE *g = fopen(OUT_FILE_TREE_GRAPH_FILENAME, "w");
                

                // export_to_dot(g, OUT_FILE_TREE_NAME, root_file_node, TRUE);

                // fclose(g);

                // system(MAKE_OUT_FILE_TREE_GRAPH_COMMAND);

                // system(OPEN_OUT_FILE_TREE_PNG_COMMAND);

                // apply(root_file_node, destroy_node, NULL, FALSE, TRUE);

                break;
            }
            case 7:
            {
                // measurement_table measures[MEAS_COUNT] = { 0 };


                // if (get_measures(measures))
                // {
                //     printf(ERR_MEASURES_MSG, RED, RESET);
                //     return ERR_ALLOC;
                // }

                // print_measures(measures, MEAS_COUNT);

                break;
            }
        }
    }
    
    return SUCCESS;
}
