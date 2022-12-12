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
#include <string.h>

#include "my_types.h"
#include "my_def.h"
#include "my_msgs.h"
#include "my_err.h"
#include "balance_tree_funcs.h"
#include "graph.h"
#include "hash_table_funcs.h"
#include "tools.h"
#include "in_out.h"
#include "my_measure.h"


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

    int rc = create_hash_table(&hash_table, CPP_KEYWORDS, CPP_HELP, KEYWORDS_COUNT, KEYWORDS_COUNT, is_list_hash_table);
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
            b_apply(root_node, b_destroy_node, NULL, FALSE);
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
                b_apply(root_node, b_destroy_node, NULL, FALSE);
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
                clear_buf(stdin);

                char *word = NULL;


                printf(INPUT_FIND_WORD_MSG);

                if (get_in_elem(stdin, &word, MAX_KEYWORD_LEN))
                {
                    printf(ERR_READING_STDIN_MSG, RED, RESET);
                    break;
                }
                
                if (!is_list_hash_table)
                {
                    int cmp_count = 0;

                    int f_index = find_keyword(hash_table, word, &cmp_count);
                    if (f_index < 0)
                    {
                        printf(ERR_FINDIND_MSG, RED, RESET);
                        free(word);
                        break;
                    }

                    printf(HELP_MSG, GREEN, ((keyword_info_t **) hash_table->data)[f_index]->keyword, cmp_count,
                        PURPLE, ((keyword_info_t **) hash_table->data)[f_index]->help, RESET);
                }
                else
                {
                    int cmp_count = 0;


                    list_keyword_info_t *f_word = find_list_keyword(hash_table, word, &cmp_count);
                    if (!f_word)
                    {
                        printf(ERR_FINDIND_MSG, RED, RESET);
                        free(word);
                        break;
                    }

                    printf(HELP_MSG, GREEN, f_word->keyword, cmp_count,
                        PURPLE, f_word->help, RESET);
                }

                free(word);

                break;
            }
            case 4:
            {
                clear_buf(stdin);

                char *word = NULL;
                char *help = NULL;


                printf(INPUT_WORD_MSG);

                if (get_in_elem(stdin, &word, MAX_KEYWORD_LEN))
                {
                    printf(ERR_READING_STDIN_MSG, RED, RESET);
                    break;
                }

                printf(INPUT_HELP_MSG);

                if (get_in_elem(stdin, &help, MAX_HELP_LEN))
                {
                    printf(ERR_READING_STDIN_MSG, RED, RESET);
                    break;
                }

                strcpy(CPP_KEYWORDS[keywords_count], word);
                strcpy(CPP_HELP[keywords_count], help);

                ++keywords_count;

                if (is_list_hash_table)
                {
                    int rc = insert_in_list_hash_table(&hash_table, word, help, hash_table->size);
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
                else
                {
                    int rc = insert_in_hash_table(&hash_table, word, help, hash_table->size);
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

                break;
            }
            case 5:
            {
                measurement_table measures[MEAS_COUNT] = { 0 };


                if (get_measures(measures))
                {
                    printf(ERR_MEASURES_MSG, RED, RESET);
                    return ERR_ALLOC;
                }

                print_measures(measures, MEAS_COUNT);

                break;
            }
            case 6:
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
