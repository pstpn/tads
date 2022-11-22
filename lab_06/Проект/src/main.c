/*


Построить дерево в соответствии со своим вариантом задания. Вывести
его на экран в виде дерева. Реализовать основные операции работы с
деревом: обход дерева, включение, исключение и поиск узлов. Сравнить
эффективность алгоритмов сортировки и поиска в зависимости от высоты
деревьев и степени их ветвления.

В файловой системе каталог файлов организован в виде бинарного дерева.
Каждый узел обозначает файл, содержащий имя и атрибуты файла, в том числе и
дату последнего обращения к файлу. Написать программу, которая обходит дерево
и удаляет из него все файлы, последнее обращение к которым происходило до
определенной даты. Вывести исходное и измененное деревья в виде дерева.


*/
#include <stdio.h>
#include <stdlib.h>

#include "../inc/my_msgs.h"
#include "../inc/my_def.h"
#include "../inc/my_err.h"
#include "../inc/tree_funcs.h"
#include "../inc/graph.h"
#include "../inc/in_out.h"


int main(void)
{
    int key = -1;
    int count = 0;

    tree_node_t *root_node = NULL;


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
                FILE *f = fopen(GRAPH_FILENAME, "w");
                

                export_to_dot(f, TREE_NAME, root_node);

                fclose(f);

                system(MAKE_GRAPH_COMMAND);

                system(OPEN_PNG_COMMAND);

                break;
            }
            case 2:
            {
                apply(root_node, print_node_info, stdout, TRUE);

                break;
            }
            case 3:
            {
                clear_buf(stdin);

                char elem;


                printf(INPUT_ELEM_MSG);

                if (get_in_elem(stdin, &elem))
                {
                    printf(ERR_READING_STDIN_MSG, RED, RESET);
                    clear_buf(stdin);
                    break;
                }
                
                tree_node_t *new_node = create_node(count++, elem);
                if (!new_node)
                {
                    printf(ERR_ALLOC_MSG, RED, RESET);
                    apply(root_node, destroy_node, NULL, FALSE);
                    return ERR_ALLOC;
                }

                root_node = insert(root_node, new_node);

                printf(SUCCESSFULLY_ADD_MSG, GREEN, RESET);

                break;
            }
        }
    }
//             case 4:
//             {
//                 if (!list_queue->len || !arr_queue->len)
//                 {
//                     printf(ERR_QUEUE_IS_EMPTY_MSG, RED, RESET);
//                     clear_buf(stdin);
//                     break;
//                 }

//                 double pop_elem;


//                 print_del_ptrs(&(arr_queue->content[arr_queue->len - 1]), list_queue->top);

//                 p_nodes.p_nodes[(p_nodes.len)++] = list_queue->top;
                
//                 pop_list_queue(list_queue, &pop_elem);
//                 pop_arr_queue(arr_queue, &pop_elem);

//                 break;
//             }
//             case 4:
//             {
//                 clear_buf(stdin);

//                 char ans;


//                 printf(INPUT_QUEUE_TYPE);
//                 fscanf(stdin, "\n%c", &ans);
//                 if (ans == '1')
//                 {
//                     clear_buf(stdin);

//                     if (arr_modeling())
//                     {
//                         printf(ERR_ALLOC_MSG, RED, RESET);
//                         return ERR_ALLOC;
//                     }
//                 }
//                 else if (ans == '2')
//                 {
//                     clear_buf(stdin);

//                     if (list_modeling())
//                     {
//                         printf(ERR_ALLOC_MSG, RED, RESET);
//                         return ERR_ALLOC;
//                     }
//                 }
//                 else
//                 {
//                     printf(ERR_CODE_MSG, RED, RESET);
//                     clear_buf(stdin);
//                 }

//                 break;
//             }
//             case 5:
//             {
//                 measurement_table measures[MEAS_COUNT] = { 0 };


//                 if (get_measures(measures))
//                 {
//                     printf(ERR_MEASURES_MSG, RED, RESET);
//                     return ERR_ALLOC;
//                 }

//                 print_measures(measures, MEAS_COUNT);

//                 break;
//             }
//         }
//     }
    
    return SUCCESS;
}
