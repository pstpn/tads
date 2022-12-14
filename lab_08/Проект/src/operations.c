#include <string.h>

#include "my_def.h"


int is_num_in_arr(int *arr, int len, int num)
{
    for (int i = 0; i < len; ++i)
        if (arr[i] == num)
            return TRUE;

    return FALSE;
}


void get_cur_max_road(int **graph_mtrx, int n, int m, int *max_road,
int *cur_road, int cur_i, int *uniq_arr, int arr_len, int *max_road_graph)
{
    for (int j = 0; j < m; ++j)
        if (graph_mtrx[cur_i][j] && !is_num_in_arr(uniq_arr, arr_len, j))
        {
            uniq_arr[arr_len++] = j;

            ++(*cur_road);

            get_cur_max_road(graph_mtrx, n, m, max_road, cur_road, j, uniq_arr, arr_len, max_road_graph);

            if (*cur_road > *max_road)
            {
                *max_road = *cur_road;

                memcpy(max_road_graph, uniq_arr, MAX_OUT_ROAD);
            }
            
            --arr_len;
            --(*cur_road);
        }
}