#include <stdlib.h>


int get_random_int(int min, int max)
{
    return (rand() % (max - min)) + min;
}
