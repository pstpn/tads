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
#include "hash_table_funcs.h"
#include "tools.h"
#include "in_out.h"


int main(void)
{
    char CPP_KEYWORDS[MAX_KEYWORDS_COUNT][MAX_KEYWORD_LEN + 1] = 
        {
            "case", "bool", "break", "char", "continue", "delete",
            "default", "do", "else", "enum", "export", "extern",
            "true", "false", "for", "goto", "if", "static",
            "or", "typedef", "while", "return", "double"
        };

    char CPP_HELP[MAX_KEYWORDS_COUNT][MAX_HELP_LEN + 1] = 
        {
            "Switch statement: as the declaration of the case labels",
            "Bool type: as the declaration of the type",
            "Break statement: as the declaration of the statement",
            "Char type: as the declaration of the type",
            "Continue statement: as the declaration of the statement",
            "Deallocation functions as the name of operator-like functions",
            "Switch statement: as the declaration of the default case label",
            "Do-while loop: as the declaration of the loop",
            "If statement: as the declaration of the alternative branch",
            "Declaration of an enumeration type",
            "Used to mark a template definition exported, which allows the same \
template to be declared, but not defined, in other translation units.",
            "Static storage duration with external linkage specifier",
            "True: boolean literal",
            "False: boolean literal",
            "For loop: as the declaration of the loop",
            "Goto statement: as the declaration of the statement",
            "If statement: as the declaration of the if statement",
            "Declarations of namespace members with static storage duration and internal linkage",
            "Alternative operators: as an alternative for ||",
            "Typedef declaration",
            "While loop: as the declaration of the loop",
            "Return statement: as the declaration of the statement",
            "Double type: as the declaration of the type"
        };

    hash_table_t *hash_table = NULL;

    int is_list_hash_table = FALSE;

    int rc = create_hash_table(&hash_table, CPP_KEYWORDS, CPP_HELP, KEYWORDS_COUNT, KEYWORDS_COUNT, FALSE);
    if (rc == ERR_ALLOC)
    {
        printf(ERR_ALLOC_MSG, RED, RESET);
        return ERR_ALLOC;
    }
    

    while (rc == NEED_RESTRUCT)
    {
        int tmp_size = get_new_table_size(hash_table->size);
        

        free_hash_table(hash_table);

        rc = create_hash_table(&hash_table, CPP_KEYWORDS, CPP_HELP, KEYWORDS_COUNT, tmp_size, FALSE);
        if (rc == ERR_ALLOC)
        {
            printf(ERR_ALLOC_MSG, RED, RESET);
            return ERR_ALLOC;
        }
    }

    int key = -1;
    int keywords_count = KEYWORDS_COUNT;

    balance_tree_node_t *root_node = create_keywords_balance_tree(CPP_KEYWORDS, KEYWORDS_COUNT);
    if (!root_node)
    {
        printf(ERR_ALLOC_MSG, RED, RESET);
        return ERR_ALLOC;
    }


    printf(INFO_MSG);
    
    while (key != 0)
    {
        printf(MENU_MSG, (is_list_hash_table) ? OPENED_TABLE_MSG : CLOSED_TABLE_MSG);

        if (fscanf(stdin, "%d", &key) != 1 ||
        key < 0 || key > MENU_LEN)
        {
            printf(ERR_CODE_MSG, RED, RESET);
            apply(root_node, destroy_node, NULL, FALSE);
            if (is_list_hash_table)
                free_list_hash_table(hash_table);
            else
                free_hash_table(hash_table);
            return ERR_CODE;
        }

        switch (key)
        {
            case 0:
            {
                apply(root_node, destroy_node, NULL, FALSE);
                if (is_list_hash_table)
                    free_list_hash_table(hash_table);
                else
                    free_hash_table(hash_table);
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
                if (!is_list_hash_table)
                    print_hash_table(hash_table);
                else
                    print_list_hash_table(hash_table);

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
            case 8:
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
            case 7:
            {
                if (is_list_hash_table)
                {
                    free_list_hash_table(hash_table);

                    int rc = create_hash_table(&hash_table, CPP_KEYWORDS, CPP_HELP, keywords_count, KEYWORDS_COUNT, FALSE);
                    if (rc == ERR_ALLOC)
                    {
                        printf(ERR_ALLOC_MSG, RED, RESET);
                        return ERR_ALLOC;
                    }
                    

                    while (rc == NEED_RESTRUCT)
                    {
                        int tmp_size = get_new_table_size(hash_table->size);
                        

                        free_hash_table(hash_table);

                        rc = create_hash_table(&hash_table, CPP_KEYWORDS, CPP_HELP, keywords_count, tmp_size, FALSE);
                        if (rc == ERR_ALLOC)
                        {
                            printf(ERR_ALLOC_MSG, RED, RESET);
                            return ERR_ALLOC;
                        }
                    }
                }
                else
                {
                    free_hash_table(hash_table);

                    int rc = create_hash_table(&hash_table, CPP_KEYWORDS, CPP_HELP, keywords_count, KEYWORDS_COUNT, TRUE);
                    if (rc == ERR_ALLOC)
                    {
                        printf(ERR_ALLOC_MSG, RED, RESET);
                        return ERR_ALLOC;
                    }
                    

                    while (rc == NEED_RESTRUCT)
                    {
                        int tmp_size = get_new_table_size(hash_table->size);
                        

                        free_list_hash_table(hash_table);

                        rc = create_hash_table(&hash_table, CPP_KEYWORDS, CPP_HELP, keywords_count, tmp_size, TRUE);
                        if (rc == ERR_ALLOC)
                        {
                            printf(ERR_ALLOC_MSG, RED, RESET);
                            return ERR_ALLOC;
                        }
                    }
                }

                is_list_hash_table = (is_list_hash_table) ? FALSE : TRUE;

                printf(CHANGE_HASH_MSG, GREEN, (is_list_hash_table) ? OPENED_TABLE_MSG : CLOSED_TABLE_MSG, RESET);

                break;
            }
        }
    }
    
    return SUCCESS;
}
