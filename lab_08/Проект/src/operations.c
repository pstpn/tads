void get_max_road(int **graph_mtrx, int n, int m)
{
    int max_road = 0;


    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m && i < j; ++j)
        {
            int cur_road = 0;


            if (graph_mtrx[i][j])
            {
                ++cur_road;

                
            }
        }
}