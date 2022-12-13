/*


Найти самый длинный простой путь в графе. 


*/
#include <stdio.h>
#include <stdlib.h>

#include "my_def.h"
#include "my_msgs.h"
#include "my_err.h"
#include "in_out.h"
#include "w_w_mem.h"
#include "operations.h"


int main(void)
{
    int key = -1;

    char *graph_filename = NULL;


    printf(INPUT_GRAPH_FILENAME_MSG);  
    if (get_in_file(stdin, &graph_filename, MAX_GRAPH_FILENAME_LEN + 1))
    {
        printf(ERR_READING_FILENAME_MSG, RED, RESET);
        return ERR_READING;
    }

    FILE *in_graph_file = fopen(graph_filename, "r");
    if (!in_graph_file)
    {
        printf(ERR_FILE_MSG, RED, RESET);
        free(graph_filename);
        return ERR_OPEN_FILE;
    }


    free(graph_filename);

    int n, m;


    if (get_size(in_graph_file, &n, &m))
    {
        printf(ERR_FILE_MSG, RED, RESET);
        fclose(in_graph_file);
        return ERR_READING;
    }

    int **graph_mtrx = allocate_matrix(n, m);
    if (graph_mtrx == NULL)
    {
        printf(ERR_ALLOC_MSG, RED, RESET);
        fclose(in_graph_file);
        return ERR_ALLOC;
    }


    if (filling_matrix(in_graph_file, graph_mtrx, n, m))
    {
        printf(ERR_FILE_MSG, RED, RESET);
        fclose(in_graph_file);
        free_matrix(graph_mtrx, 1);
        return ERR_READING;
    }

    fclose(in_graph_file);

    printf(INFO_MSG);
    
    while (key != 0)
    {
        printf(MENU_MSG);

        if (fscanf(stdin, "%d", &key) != 1 ||
        key < 0 || key > MENU_LEN)
        {
            printf(ERR_CODE_MSG, RED, RESET);
            free_matrix(graph_mtrx, 1);
            return ERR_CODE;
        }

        switch (key)
        {
            case 0:
            {
                free_matrix(graph_mtrx, 1);
                return SUCCESS;
            }
            case 1:
            {
                FILE *f = fopen(GRAPH_FILENAME, "w");
                

                export_to_dot(f, GRAPH_NAME, graph_mtrx, n, m);

                fclose(f);

                system(MAKE_GRAPH_COMMAND);

                system(OPEN_GRAPH_PNG_COMMAND);

                break;
            }
            case 2:
            {
                int max_road = 0,
                    cur_road = 0;


                for (int i = 0; i < n; ++i)
                {
                    get_cur_max_road(graph_mtrx, n, m, &max_road, &cur_road, i, 0, -1);

                    cur_road = 0;
                }

                printf("MAX_ROAD: %d\n", max_road);

                break;
            }
        }
    }
    
    return SUCCESS;
}
