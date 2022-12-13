void get_cur_max_road(int **graph_mtrx, int n, int m, int *max_road,
int *cur_road, int cur_i, int start, int ban_ind)
{
    start += (cur_i == start && ban_ind != -1) ? 1 : 0;

    for (int j = (start == ban_ind) ? start + 1 : start;
        j < m; j += (j + 1 == ban_ind) ? 2 : 1)
        if (graph_mtrx[cur_i][j])
        {
            ++(*cur_road);

            get_cur_max_road(graph_mtrx, n, m, max_road, cur_road, j, ++start, cur_i);

            if (*cur_road > *max_road)
                *max_road = *cur_road;
            
            --(*cur_road);
        }
}