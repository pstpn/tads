int get_new_table_size(int cur_size)
{
    for (int i = 0; i < 4; ++i)
    {
        ++cur_size;
        
        for (int k = 2; k < cur_size; ++k)
            if (!(cur_size % k))
            {
                k = 2;
                ++cur_size;
            }
    }

    return cur_size;
}