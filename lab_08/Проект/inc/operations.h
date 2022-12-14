#ifndef ___MY_OPERATIONS___
#define ___MY_OPERATIONS___


int is_num_in_arr(int *arr, int len, int num);
void get_cur_max_road(int **graph_mtrx, int n, int m, int *max_road,
    int *cur_road, int cur_i, int *out_arr, int arr_len, int *max_road_graph);

#endif // ___MY_OPERATIONS___